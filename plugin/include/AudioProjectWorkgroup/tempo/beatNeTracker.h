#ifndef BEATNETRACKER_H
#define BEATNETRACKER_H

#include "tracker.h"
#include "BeatNet.h"

class BeatneTracker final: public Tracker{

public:
	BeatneTracker();

	~BeatneTracker() override;

	void setup(double sampleRate, int samplesPerBlock) override; // function to run in the prepareToPlay

	bool operate(float** data, int inputChannels) override;	// function to run in the processBlock

	double get_tempo() override;

private:

	const std::string modelPath{ "beatnet_bda.onnx" }; // TODO fix hardcoded path.
	const int preOutShape {3};
	BeatNet myBeatNet;

	std::vector<float> monoBuffer, predictions;
	float tempoEstimate;
	void compute_tempo();
};

#endif