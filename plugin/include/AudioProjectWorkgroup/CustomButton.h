/*
  ==============================================================================

    CustomButton.h
    
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ButtonLookAndFeel.h"

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
    ButtonLookAndFeel laf;
    void resetState();
    bool resetFlag;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomButton)
};
