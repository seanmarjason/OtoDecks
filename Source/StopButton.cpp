#include <JuceHeader.h>
#include "StopButton.h"
#include "ColourScheme.h"


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
    double margin = 5;
    stopButton.setBounds(margin, margin, getWidth() - (margin * 2), getHeight() - (margin * 2));
}


void StopButton::buttonClicked(juce::Button* button)
{
    if (button == &stopButton)
    {
        player->pause();
    }
}
