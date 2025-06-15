
#pragma once

#include "AudioProjectWorkgroup/tempo/beatrack.h"

BeaTrack::BeaTrack() : rollingAvg(MAX_RECENT_TEMPOS){
	SR = 0; 
	bufferSize = 0;
	
}

BeaTrack::~BeaTrack() = default;

void BeaTrack::setup(double sampleRate, int samplesPerBlock) {
	
	// this somehow have to define a downsampling/oversampling ratio; Because BTrack operates at 44100 default samplerate.
	// https://github.com/adamstark/BTrack/issues/12
	
	SR = sampleRate; 
	bufferSize = samplesPerBlock;
	BeaTracker.setSampleRate(SR);
	helperBuffer.resize(bufferSize);
	BeaTracker.updateHopAndFrameSize(bufferSize,bufferSize);
}

bool BeaTrack::operate(float** data, int inputChannels){
	
	// transform data to double
	// transform data to mono
	for (int j = 0; j< bufferSize; ++j){

		helperBuffer[j] = static_cast<double>(data[0][j]);

		for (int i=1; i<inputChannels; ++i){
			helperBuffer[j] += static_cast<double>(data[i][j]);
		}
		helperBuffer[j] /= static_cast<double>(inputChannels);
	}
	BeaTracker.processAudioFrame(helperBuffer.data());
	
	return getAccurateCurrentTempoEstimate();
}

double BeaTrack::get_tempo(){
	// return BeaTracker.getCurrentTempoEstimate();
	return calculatedTempo;
}

bool BeaTrack::getAccurateCurrentTempoEstimate(){
	if (BeaTracker.beatDueInCurrentFrame()){

		auto currenTime = std::chrono::steady_clock::now();
		
		{
			auto interval = currenTime - lastBeaTime;
			auto intervalMs = std::chrono::duration_cast<std::chrono::milliseconds>(interval).count();
			// raw bpm calculation : 60000 (ms) /  interval(ms)
			calculatedTempo = 60000.0 / intervalMs;
			findClosestTempo(calculatedTempo);	

			calculatedTempo = rollingAvgSmoothing(calculatedTempo);
		}
		lastBeaTime = currenTime;

		return true;
	}

	return false;
}

// Find closest multiple/subdivision (half, same, double, and x4). 
void BeaTrack::findClosestTempo(double &bpm) {
	
	double reference = BeaTracker.getCurrentTempoEstimate();
	double bestTempo = bpm;
	double minDifference = std::abs(bpm - reference);
	
	for (double candidate : candidates) {
		candidate*=bpm;
		double difference = std::abs(candidate - reference);
		if (difference < minDifference) {
			minDifference = difference;
			bestTempo = candidate;
		}
	}
	bpm = bestTempo;
}


double BeaTrack::rollingAvgSmoothing(double recentTempo ) {
	rollingAvg.push_back(recentTempo);
	if (rollingAvg.size() > MAX_RECENT_TEMPOS) {
		rollingAvg.erase(rollingAvg.begin());
	}
	
	// Calculate average
	double sum = 0;
	for (double tempo : rollingAvg) {
		sum += tempo;
	}
	return (sum / rollingAvg.size());
}