/*
  ==============================================================================

    VolumeAdjuster.cpp
    Created: 23 Feb 2022 10:24:05pm
    Author:  Sean Marjason

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VolumeAdjuster.h"
#include "ColourScheme.h"

//==============================================================================
VolumeAdjuster::VolumeAdjuster(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(volSlider);
    volSlider.addListener(this);
    
    volSlider.setRange(0.0, 2.0, 0.01);
    volSlider.setValue(1.0);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    volSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 25);
    volSlider.setDoubleClickReturnValue(true, 1.0);
    volSlider.setTextValueSuffix(" v");
}

VolumeAdjuster::~VolumeAdjuster()
{
}

void VolumeAdjuster::paint (juce::Graphics& g)
{
    volSlider.setColour(juce::Slider::rotarySliderOutlineColourId, ColourScheme::greyAscent);
    volSlider.setColour(juce::Slider::rotarySliderFillColourId, ColourScheme::primaryAscent);
    volSlider.setColour(juce::Slider::textBoxOutlineColourId, ColourScheme::backgroundColour);
}

void VolumeAdjuster::resized()
{
    volSlider.setBounds(0, 0, getWidth(), getHeight());
}

void VolumeAdjuster::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
}
