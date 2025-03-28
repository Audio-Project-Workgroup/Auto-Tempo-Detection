#include "cassert"
#include "AudioProjectWorkgroup/tempo/interface.h"
#include "AudioProjectWorkgroup/tempo/beatrack.h"

Interface::Interface(TrackerList trackerItem){
	if (trackerItem == BTRACK){
		tempoTracker = new BeaTrack();
	} else {
		assert(false); // other trackers are not supported.
	}
}

Tracker& Interface::getTracker(){
	return *tempoTracker;
}
