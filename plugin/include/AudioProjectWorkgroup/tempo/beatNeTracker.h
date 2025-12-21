#ifndef BEATNETRACKER_H
#define BEATNETRACKER_H

#include "tracker.h"
#include "BeatNet.h"

#include <chrono>

class BeatneTracker final: public Tracker{

public:
	BeatneTracker();

	~BeatneTracker() override;

	void setup(double sampleRate, int samplesPerBlock) override; // function to run in the prepareToPlay

	bool operate(float** data, int inputChannels) override;	// function to run in the processBlock

	double get_tempo() override;

private:

	const int preOutShape {3};
	BeatNet myBeatNet;

	std::vector<float> monoBuffer, predictions;
	float tempoEstimate;
	bool compute_tempo();
	
	double rollingAvgSmoothing(double);
	int argmax();
	std::chrono::steady_clock::time_point lastBeaTime;
	// double candidates[4] {0.5, 1.0, 2.0, 4.0};
	static const int MAX_RECENT_TEMPOS=10;
	std::vector<double> rollingAvg{MAX_RECENT_TEMPOS};	// fifo
};

#endif