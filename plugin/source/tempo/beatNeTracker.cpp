
#include "AudioProjectWorkgroup/tempo/beatNeTracker.h"

BeatneTracker::BeatneTracker()
	: tempoEstimate(0.0f)
	, predictions(preOutShape) {}

BeatneTracker::~BeatneTracker() = default;

void BeatneTracker::setup(double sampleRate, int samplesPerBlock) {
	SR = sampleRate;
	bufferSize = samplesPerBlock;
	monoBuffer.resize(bufferSize);
	myBeatNet.setup(sampleRate, samplesPerBlock);
}

bool BeatneTracker::operate(float** data, int inputChannels){
	
	// // transform data to mono
	for (int j = 0; j< bufferSize; ++j){

		monoBuffer[j] = static_cast<double>(data[0][j]);

		for (int i=1; i<inputChannels; ++i){
			monoBuffer[j] += data[i][j];
		}
		monoBuffer[j] /= inputChannels;
	}
	if(myBeatNet.process(monoBuffer, predictions)){
		compute_tempo();
	}
	return false;
}

double BeatneTracker::get_tempo(){
	return tempoEstimate;
}

void BeatneTracker::compute_tempo()
{
	float beatProb = predictions[0]; // the beat...
	
	// implementation here..
	
	tempoEstimate=0;
}