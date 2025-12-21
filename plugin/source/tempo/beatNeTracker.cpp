
#include "AudioProjectWorkgroup/tempo/beatNeTracker.h"

#define MIN_BPM 24.0    // slowest considered tempo
#define MAX_BPM 220.0   // fastest considered tempo
#define MIN_INTERVAL_MS (int)(60000.0 / MAX_BPM)  // ~273 ms
#define MAX_INTERVAL_MS (int)(60000.0 / MIN_BPM)  // ~2500 ms

BeatneTracker::BeatneTracker()
	: tempoEstimate(0.0f)
	, predictions(preOutShape) {}

BeatneTracker::~BeatneTracker() = default;

void BeatneTracker::setup(double sampleRate, int samplesPerBlock) {
	SR = sampleRate;
	bufferSize = samplesPerBlock;
	monoBuffer.resize(bufferSize);
	myBeatNet.setup(sampleRate, samplesPerBlock);

	lastBeaTime = std::chrono::steady_clock::now();
}

bool BeatneTracker::operate(float** data, int inputChannels){
	
	// // transform data to mono
	for (int j = 0; j< bufferSize; ++j){

		monoBuffer[j] = data[0][j];

		for (int i=1; i<inputChannels; ++i){
			monoBuffer[j] += data[i][j];
		}
		monoBuffer[j] /= inputChannels;
	}
	if(myBeatNet.process(monoBuffer, predictions)){
		return compute_tempo();
	}
	return false;
}

double BeatneTracker::get_tempo(){
	return tempoEstimate;
}

int BeatneTracker::argmax() {
    return static_cast<int>(
        std::distance(predictions.begin(), std::max_element(predictions.begin(), predictions.end()))
    );
}

double BeatneTracker::rollingAvgSmoothing(double recentTempo ) {
	rollingAvg.push_back(recentTempo);

	if (rollingAvg.size() > MAX_RECENT_TEMPOS) {
		rollingAvg.erase(rollingAvg.begin());
	}

	// calculate average ..
	double sum = 0;
	for (double tempo : rollingAvg) {
		sum += tempo;
	}
	return (sum / rollingAvg.size());
}

bool BeatneTracker::compute_tempo()
{
    int output = argmax();
    if (output == 2) return false;        // non-beat
    // if (predictions[output] < 0.5f) return false; // filter out low confident predictions..

    auto currentTime = std::chrono::steady_clock::now();

    // interval in ms
    auto intervalMs = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastBeaTime).count();

    if (intervalMs < MIN_INTERVAL_MS || intervalMs > MAX_INTERVAL_MS) // avoid out-of-range tempos
    {
        lastBeaTime = currentTime;
        return false;
    }

	double bpm = 60000.0 / intervalMs;	    // compute tempo 
    tempoEstimate = rollingAvgSmoothing(bpm); // smooth tempo

    lastBeaTime = currentTime;
    return true;
}
