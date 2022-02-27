#include <JuceHeader.h>
#include "LoopingComponent.h"
#include "ColourScheme.h"


LoopingComponent::LoopingComponent(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(loop2);
    addAndMakeVisible(loop4);
    addAndMakeVisible(loop8);
    addAndMakeVisible(loopManual);
    
    loopManual.setClickingTogglesState(true);
    
    loop2.addListener(this);
    loop4.addListener(this);
    loop8.addListener(this);
    loopManual.addListener(this);
}


LoopingComponent::~LoopingComponent()
{
}


void LoopingComponent::paint (juce::Graphics& g)
{
    g.fillAll(ColourScheme::backgroundColour);
    g.setColour (ColourScheme::primaryFont);
    g.setFont (14.0f);
    
    loop2.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    loop4.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    loop8.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    loopManual.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
}


void LoopingComponent::resized()
{
    double colW = getWidth() / 4;
    
    loop2.setBounds(colW * 0, 0, colW, getHeight());
    loop4.setBounds(colW * 1, 0, colW, getHeight());
    loop8.setBounds(colW * 2, 0, colW, getHeight());
    loopManual.setBounds(colW * 3, 0, colW, getHeight());
}


void LoopingComponent::buttonClicked(juce::Button* button)
{
    double currentPosition = player->getCurrentPosition();

    if (button == &loop2)
    {
        player->startAudioLoop(currentPosition - 2.0, currentPosition);
    }
    if (button == &loop4)
    {
        player->startAudioLoop(currentPosition - 4.0, currentPosition);
    }
    if (button == &loop8)
    {
        player->startAudioLoop(currentPosition - 8.0, currentPosition);
    }
    if (button == &loopManual)
    {
        if (loopManual.getToggleState() == true)
        {
            manualLoopStart = currentPosition;
        }
        else
        {
            manualLoopEnd = currentPosition;
        }
        player->startAudioLoop(manualLoopStart, manualLoopEnd);
    }
}
