/*
  ==============================================================================

    TempoAdjuster.cpp
    Created: 23 Feb 2022 10:45:18pm
    Author:  Sean Marjason

  ==============================================================================
*/

#include <JuceHeader.h>
#include "TempoAdjuster.h"
#include "ColourScheme.h"

//==============================================================================
TempoAdjuster::TempoAdjuster(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(tempoSlider);
    tempoSlider.addListener(this);
    
    tempoSlider.setRange(0.0, 2.0, 0.01);
    tempoSlider.setValue(1.0);
    tempoSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    tempoSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 25);
    tempoSlider.setDoubleClickReturnValue(true, 1.0);
    tempoSlider.setTextValueSuffix("x");
}

TempoAdjuster::~TempoAdjuster()
{
}

void TempoAdjuster::paint (juce::Graphics& g)
{
    tempoSlider.setColour(juce::Slider::rotarySliderOutlineColourId, ColourScheme::greyAscent);
    tempoSlider.setColour(juce::Slider::rotarySliderFillColourId, ColourScheme::primaryAscent);
    tempoSlider.setColour(juce::Slider::textBoxOutlineColourId, ColourScheme::backgroundColour);
}

void TempoAdjuster::resized()
{
    tempoSlider.setBounds(0, 0, getWidth(), getHeight());
}

void TempoAdjuster::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &tempoSlider)
    {
        player->setSpeed(slider->getValue());
    }
}
