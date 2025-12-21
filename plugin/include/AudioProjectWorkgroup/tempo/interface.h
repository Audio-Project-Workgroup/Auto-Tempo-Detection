
#pragma once

#include "AudioProjectWorkgroup/tempo/beatrack.h"
#include "AudioProjectWorkgroup/tempo/beatNeTracker.h"


enum TrackerList{
	BTRACK,
	BEATNET,
	NUM_TRACKERS
};

inline std::string TrackerListToString(TrackerList t)
{
    switch (t)
    {
        case BTRACK:   return "BTrack";
        case BEATNET:   return "BeatNet";
    }
}

class Interface final: public Tracker{
public:

	Interface(TrackerList tracker=BEATNET); // now default is the BeatNet
	~Interface() override;
	// delete copy and move to comply with the rule of 5
	Interface(const Interface&) = delete;
	Interface(Interface&&) = delete;
	Interface& operator=(const Interface&) = delete;
	Interface& operator=(Interface &&) = delete;

	void setup(double sampleRate, int samplesPerBlock) override; // function to run in the prepareToPlay
	bool operate(float** data, int inputChannels) override;	// function to run in the processBlock
	double get_tempo() override;

	void switchTracker(TrackerList);

private:

	Tracker *tempoTracker;
	TrackerList selectedTracker;
	void assignTracker();

	// available Trackers 
	BeaTrack mbeatrack;
	BeatneTracker mbeatnet;
};