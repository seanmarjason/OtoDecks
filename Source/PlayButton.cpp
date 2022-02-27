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
    playButton.setBounds(0, 0, getWidth(), getHeight());
}


void PlayButton::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        player->start();
    }
}
