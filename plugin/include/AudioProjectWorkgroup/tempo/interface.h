
#pragma once

#include "tracker.h"

enum TrackerList{
	BTRACK,
	ONNXTRACK,
	NUM_TRACKERS
};

class Interface{
public:
	Interface(TrackerList tracker=BTRACK); // default is the BTrack
	Tracker& getTracker();
private:
	Tracker* tempoTracker;
};