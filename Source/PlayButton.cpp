#include <JuceHeader.h>
#include "PlayButton.h"
#include "ColourScheme.h"


PlayButton::PlayButton(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(playButton);
    playButton.addListener(this);
}


PlayButton::~PlayButton()
{
}


void PlayButton::paint (juce::Graphics& g)
{
    playButton.setColour(juce::TextButton::buttonColourId, ColourScheme::greenAscent);
}


void PlayButton::resized()
{
    double margin = 5;
    playButton.setBounds(margin, margin, getWidth() - (margin * 2), getHeight() - (margin * 2));
}


void PlayButton::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        player->start();
    }
}
