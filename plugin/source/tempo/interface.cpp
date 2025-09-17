// #include <filesystem>
// #include <iostream>
#include <stdexcept>
#include "AudioProjectWorkgroup/tempo/interface.h"
#include "AudioProjectWorkgroup/tempo/beatrack.h"
#include "AudioProjectWorkgroup/tempo/beatneTracker.h"

Interface::Interface(TrackerList selectedTracker): tempoTracker(nullptr)
{
	setTracker(selectedTracker);
}

Interface::~Interface() {
    delete tempoTracker;
}

void Interface::setTracker(TrackerList tracker)
{
	if (tracker == BTRACK){
		tempoTracker = new BeaTrack();
	} else if (tracker == BEATNET){
		tempoTracker = new BeatneTracker();
	}
	else {
		std::runtime_error("Unsupported tracker type: only BTRACK and BEATNET are supported.");
	}

}

Tracker& Interface::getTracker(){
	// std::filesystem::path cwd = std::filesystem::current_path();	
	// std::cout<<"Current Working Directory: " << cwd << std::endl;
	// std::cerr<<"Current Working Directory: " << cwd << std::endl;
	return *tempoTracker;
}
