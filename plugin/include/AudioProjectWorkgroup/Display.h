/*
  ==============================================================================

    Display.h

  ==============================================================================
*/
#pragma once
#include <JuceHeader.h>

class Display  : public juce::Component
{
public:
    Display();
    ~Display() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    juce::String tempo;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Display)
};
