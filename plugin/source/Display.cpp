/*
  ==============================================================================

    Display.cpp

  ==============================================================================
*/

#include "AudioProjectWorkgroup/Display.h"

//==============================================================================
Display::Display()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    tempo = "";
}

Display::~Display()
{
}

void Display::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    auto bounds = getLocalBounds();

    g.setColour(juce::Colour(160, 179, 175));
    juce::Rectangle<int> roundRect = bounds.reduced(5);
    g.drawRoundedRectangle(roundRect.toFloat(), 3, 3);
    g.fillRect(roundRect);

    // Draw the Tempo
    //g.setColour (juce::Colours::lawngreen);
    g.setColour(juce::Colours::black);
    g.setFont (bounds.getWidth()*0.25); // colour of tempo to 25% of display width
    g.drawText(tempo, getLocalBounds(),
        juce::Justification::centred, true);

    // Type BPM at bottom right of the display
    // We multiply by 3 because this reps size of sq for bpm
    float sq = bounds.getWidth() * 0.10 * 3; 
    g.setFont(sq/3.0); // Our text will fill the sq so we divide by 3
    g.drawText("BPM", (int)(bounds.getBottomRight().getX() - sq),
        (int)(bounds.getBottomRight().getY() - sq * (2.5/3.0)), sq, 
        sq, juce::Justification::centred);

    // Create light reflection on screen
    juce::Point<float> newPoint = roundRect.toFloat().getTopLeft();
    juce::Rectangle<float> ref (newPoint, newPoint.translated(0.2*bounds.getWidth(), 
        0.2*bounds.getWidth()));
    juce::ColourGradient grad(juce::Colours::antiquewhite,
        juce::Point<float>(ref.getCentreX() - ref.getWidth(), ref.getCentreY()), 
        juce::Colour(160, 179, 175),
        ref.getBottomLeft(), false);
    g.setGradientFill(grad);
    g.fillRect(ref);
}

void Display::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}