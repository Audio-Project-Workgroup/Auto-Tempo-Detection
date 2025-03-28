/*
  ==============================================================================

    CustomButton.cpp
  ==============================================================================
*/

#include <JuceHeader.h>
#include "AudioProjectWorkgroup/CustomButton.h"

//==============================================================================
CustomButton::CustomButton()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(&reset);
    addAndMakeVisible(&resetLabel);

    // Init button settings
    reset.setColour(juce::TextButton::buttonColourId, juce::Colour(74, 76, 84));
    reset.setColour(juce::ComboBox::outlineColourId, juce::Colour(74, 76, 84));
    reset.setButtonText("");

    // Init label button settings
    resetLabel.setFont(juce::Font(14.0f));
    resetLabel.setText("RESET", juce::dontSendNotification);
    resetLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    resetLabel.setJustificationType(juce::Justification::centred);
}

CustomButton::~CustomButton()
{
}

void CustomButton::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void CustomButton::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds = getLocalBounds();

    // 50% for the reset and 40% for label display, 10% for gap
    reset.setBounds(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight()/2);
    auto resetBounds = reset.getBounds();
    resetLabel.setBounds(bounds.getX(), resetBounds.getBottom() + 5,
        bounds.getWidth(), bounds.getHeight() * 0.4);
}
