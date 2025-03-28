
#pragma once

#include "AudioProjectWorkgroup/tempo/beatrack.h"

BeaTrack::BeaTrack(){
	SR = 44100; 
	bufferSize = 512;
	BeaTracker.updateHopAndFrameSize(bufferSize,bufferSize);
}

BeaTrack::~BeaTrack() = default;

void BeaTrack::setup(double sampleRate, int samplesPerBlock) {
	
	// this somehow have to define a downsampling/oversampling ratio; Because BTrack operates at 44100 default samplerate.
	// https://github.com/adamstark/BTrack/issues/12
	
	SR = sampleRate; 
	bufferSize = samplesPerBlock;
	BeaTracker.updateHopAndFrameSize(bufferSize,bufferSize);
}

bool BeaTrack::operate(float** data, int inputChannels){
	// transform data to double
	// transform data to mono
	
	for (int i=0; i<inputChannels; ++i){
		for (int j = 0; j< bufferSize; ++j){
			
			double val = static_cast<double>(data[i][j]);

			if (i==0)	
				tempHelper[j] = val;
			else{
				tempHelper[j] += val;
				tempHelper[j] /= 2.f;
			}
		}
	}

	BeaTracker.processAudioFrame(tempHelper);
	bool isBeat = BeaTracker.beatDueInCurrentFrame();

	// if(isBeat)
	// 	printf("Tick\n");

	return isBeat;
}

double BeaTrack::get_tempo(){
	return BeaTracker.getCurrentTempoEstimate();
}

