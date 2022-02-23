/*
  ==============================================================================

    TrackNavigator.cpp
    Created: 23 Feb 2022 11:14:48pm
    Author:  Sean Marjason

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TrackNavigator.h"
#include "ColourScheme.h"

//==============================================================================
TrackNavigator::TrackNavigator(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(trackSlider);
    trackSlider.addListener(this);
    
    trackSlider.setRange(0.0, 1.0);
    trackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
}

TrackNavigator::~TrackNavigator()
{
}

void TrackNavigator::paint (juce::Graphics& g)
{
    trackSlider.setColour(juce::Slider::backgroundColourId, ColourScheme::greyAscent);
    trackSlider.setColour(juce::Slider::trackColourId , ColourScheme::greenAscent);
    trackSlider.setColour(juce::Slider::thumbColourId , ColourScheme::greenAscent);
    trackSlider.setColour(juce::Slider::textBoxOutlineColourId, ColourScheme::backgroundColour);
}

void TrackNavigator::resized()
{
    trackSlider.setBounds(0, 0, getWidth(), getHeight());
}

void TrackNavigator::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &trackSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
}

void TrackNavigator::setValue(double value) {
    trackSlider.setValue(value);
}
