#include "AudioProjectWorkgroup/BeatLedOut.h"

void BeatLed::Blink()
{
    isOn = !isOn;
    repaint();
}

void BeatLed::paint(juce::Graphics& g)
{
    g.fillAll( isOn ? juce::Colours::red : juce::Colours::darkgrey);
}