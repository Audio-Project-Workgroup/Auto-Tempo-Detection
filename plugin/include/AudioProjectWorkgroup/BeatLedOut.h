#ifndef BEATLEDOUT_H
#define BEATLEDOUT_H

#include <JuceHeader.h>
#define BLINK_TIME_IN_FRAMES 1

class BeatLed
    : public juce::Component
{
public:

    void Blink();
    void paint(juce::Graphics&) override;

private:
    int isOn{0};
};

#endif