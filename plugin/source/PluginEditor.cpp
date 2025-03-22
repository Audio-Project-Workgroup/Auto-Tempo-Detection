#include "AudioProjectWorkgroup/PluginProcessor.h"
#include "AudioProjectWorkgroup/PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), canvasHeight(250), canvasWidth(400)
{
    juce::ignoreUnused (processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    startTimer(100);
    juce::LookAndFeel::setDefaultLookAndFeel(&customLNF);
    addAndMakeVisible(&display);
    addAndMakeVisible(&resetBtn);
    setSize (canvasWidth, canvasHeight);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds(); // get the bounds of the UI

    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();

    // display width is 50% of canvas and height is 30% of canvas
    double dispWidth = 0.5 * canvasWidth;
    double dispHeight = 0.3 * canvasWidth;
    display.setBounds(bounds.getCentreX() - (dispWidth/2.0), 
    bounds.getCentreY() - (dispHeight/2.0) - 20, (int)dispWidth, (int)dispHeight);

    // set bounds for reset button
    double btnWidth = 0.5*dispWidth;
    double btnHeight = 0.4 * dispHeight;
    resetBtn.setBounds(display.getBounds().getCentreX() - (btnWidth / 2),
        display.getBounds().getCentreY() - (btnHeight / 2.0) + 3*dispHeight/4,
        (int)btnWidth, (int)btnHeight);
}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    // Get the current tempo
    int tempo = processorRef.currTempo;

    // Store the current tempo in a string
    display.tempo = juce::String::formatted("%d", tempo);
    display.repaint();
}