#pragma once

#include "tracker.h"
#include "BTrack.h"
#include <vector>
#include <chrono>

class BeaTrack final: public Tracker{

public:
	BeaTrack();

	~BeaTrack() override;

	void setup(double sampleRate, int samplesPerBlock) override; // function to run in the prepareToPlay

	bool operate(float** data, int inputChannels) override;	// function to run in the processBlock

	double get_tempo() override;


private:
	BTrack BeaTracker;
	std::vector<double> helperBuffer;
	
	std::chrono::steady_clock::time_point lastBeaTime;
	double calculatedTempo = 0.0;
	double candidates[4] {0.5, 1.0, 2.0, 4.0};
	static const int MAX_RECENT_TEMPOS=10;
	std::vector<double> rollingAvg;
	void findClosestTempo(double&);
	bool getAccurateCurrentTempoEstimate();
	double rollingAvgSmoothing(double);
};