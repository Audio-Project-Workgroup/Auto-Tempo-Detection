/*
  ==============================================================================

    CustomButton.h
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomButton  : public juce::Component
{
public:
    CustomButton();
    ~CustomButton() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    juce::TextButton reset;
    juce::Label resetLabel;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomButton)
};
