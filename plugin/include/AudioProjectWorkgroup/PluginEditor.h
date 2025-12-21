#pragma once

#include "PluginProcessor.h"
#include "Display.h"
#include "CustomButton.h"
#include "CustomLookAndFeel.h"
#include "BeatLedOut.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor, juce::Timer
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    double canvasWidth;
    double canvasHeight;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;
    CustomLookAndFeel customLNF;
    Display display;
    CustomButton resetBtn;
    BeatLed beatLed;

    // The tracker option dropdown
    juce::ComboBox trackerOption;
    juce::Label trackerOptionLabel;
    void setupTrackeroptionComboBox();

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
