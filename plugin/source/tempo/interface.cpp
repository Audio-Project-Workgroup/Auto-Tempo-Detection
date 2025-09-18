// #include <filesystem>
// #include <iostream>
#include <stdexcept>
#include "AudioProjectWorkgroup/tempo/interface.h"

Interface::Interface(TrackerList tracker) : selectedTracker(tracker), tempoTracker(nullptr)
{
	assignTracker();
	// std::filesystem::path cwd = std::filesystem::current_path();	
	// std::cout<<"Current Working Directory: " << cwd << std::endl;
	// std::cerr<<"Current Working Directory: " << cwd << std::endl;
}

Interface::~Interface() = default;

void Interface::assignTracker()
{
	if (selectedTracker == BTRACK){
		tempoTracker = &mbeatrack;
	} else if (selectedTracker == BEATNET){
		tempoTracker = &mbeatnet;
	}
	else {
		std::runtime_error("Unsupported tracker type: only BTRACK and BEATNET are supported.");
	}
}

void Interface::switchTracker(TrackerList tracker)
{
	if (tracker == selectedTracker)
		return;
	
	selectedTracker = tracker;
	assignTracker();
}

void Interface::setup(double sampleRate, int samplesPerBlock)
{
	if (tempoTracker)
	{
		tempoTracker->setup(sampleRate,samplesPerBlock);
	}	
	
}

bool Interface::operate(float** data, int inputChannels) 
{
	return tempoTracker->operate(data,inputChannels);
}

double Interface::get_tempo()
{
	return tempoTracker->get_tempo();
}