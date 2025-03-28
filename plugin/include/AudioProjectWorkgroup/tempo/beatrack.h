#pragma once

#include "tracker.h"
#include "BTrack.h"

class BeaTrack final: public Tracker{

public:
	BeaTrack();

	~BeaTrack() override;

	void setup(double sampleRate, int samplesPerBlock) override; // function to run in the prepareToPlay

	bool operate(float** data, int inputChannels) override;	// function to run in the processBlock

	double get_tempo() override;

private:
	BTrack BeaTracker;
	double tempHelper[1000];
};