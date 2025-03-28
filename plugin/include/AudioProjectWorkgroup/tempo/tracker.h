
#pragma once

class Tracker{

	protected:
		
		double SR;
		int bufferSize;

	public:
		
		Tracker() : SR(0.f), bufferSize(0) {};

		virtual void setup(double sampleRate, int samplesPerBlock) = 0; // function to run in the prepareToPlay

		virtual bool operate(float** data, int inputChannels) = 0;	// function to run in the processBlock

		virtual double get_tempo() = 0; // function to return the current tempo

		virtual ~Tracker() = default;
};
