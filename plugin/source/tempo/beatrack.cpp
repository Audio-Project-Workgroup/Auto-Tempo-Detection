
#pragma once

#include "AudioProjectWorkgroup/tempo/beatrack.h"

BeaTrack::BeaTrack(){
	SR = 0; 
	bufferSize = 0;
}

BeaTrack::~BeaTrack() = default;

void BeaTrack::setup(double sampleRate, int samplesPerBlock) {
	
	// this somehow have to define a downsampling/oversampling ratio; Because BTrack operates at 44100 default samplerate.
	// https://github.com/adamstark/BTrack/issues/12
	
	SR = sampleRate; 
	bufferSize = samplesPerBlock;
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
	return BeaTracker.beatDueInCurrentFrame();
}

double BeaTrack::get_tempo(){
	return BeaTracker.getCurrentTempoEstimate();
}