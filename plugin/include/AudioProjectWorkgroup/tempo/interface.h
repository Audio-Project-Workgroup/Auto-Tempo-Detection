
#pragma once

#include "tracker.h"

enum TrackerList{
	BTRACK,
	BEATNET,
	NUM_TRACKERS
};

class Interface{
public:

	Interface(TrackerList tracker=BEATNET); // now default is the BeatNet
	~Interface();
	// delete copy and move to comply with the rule of 5
	Interface(const Interface&) = delete;
	Interface(Interface&&) = delete;
	Interface& operator=(const Interface&) = delete;
	Interface& operator=(Interface &&) = delete;

	Tracker& getTracker();
	void setTracker(TrackerList);

private:

	Tracker* tempoTracker;
	
};