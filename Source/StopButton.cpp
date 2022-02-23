/*
  ==============================================================================

    StopButton.cpp
    Created: 23 Feb 2022 11:49:29pm
    Author:  Sean Marjason

  ==============================================================================
*/

#include <JuceHeader.h>
#include "StopButton.h"
#include "ColourScheme.h"

//==============================================================================
StopButton::StopButton(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(stopButton);
    stopButton.addListener(this);
}

StopButton::~StopButton()
{
}

void StopButton::paint (juce::Graphics& g)
{
    stopButton.setColour(juce::TextButton::buttonColourId, ColourScheme::redAscent);
}

void StopButton::resized()
{
    stopButton.setBounds(0, 0, getWidth(), getHeight());
}

void StopButton::buttonClicked(juce::Button* button)
{
    if (button == &stopButton)
    {
        player->stop();
    }
}
