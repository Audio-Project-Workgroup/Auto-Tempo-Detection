/*
  ==============================================================================

    LookAndFeel.h

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
    CustomLookAndFeel();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomLookAndFeel)
};