/*
  ==============================================================================

    ButtonLookAndFeel.h

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class ButtonLookAndFeel : public juce::LookAndFeel_V4 {
public:
    ButtonLookAndFeel();

private:
    void drawButtonBackground(juce::Graphics& g,
        juce::Button& button,
        const juce::Colour& backgroundColour,
        bool shouldDrawButtonAsHighlighted,
        bool shouldDrawButtonAsDown) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonLookAndFeel)
};