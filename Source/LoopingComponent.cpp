/*
  ==============================================================================

    LoopingComponent.cpp
    Created: 17 Feb 2022 10:44:44pm
    Author:  Sean Marjason

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LoopingComponent.h"

//==============================================================================
LoopingComponent::LoopingComponent(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(loop2);
    addAndMakeVisible(loop4);
    addAndMakeVisible(loop8);
    addAndMakeVisible(loop16);
    addAndMakeVisible(loopManual);
    
    loopManual.setClickingTogglesState(true);
    
    loop2.addListener(this);
    loop4.addListener(this);
    loop8.addListener(this);
    loop16.addListener(this);
    loopManual.addListener(this);

}

LoopingComponent::~LoopingComponent()
{
}

void LoopingComponent::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    
}

void LoopingComponent::resized()
{
    double colW = getWidth() / 5;
    
    loop2.setBounds(colW * 0, 0, colW, getHeight());
    loop4.setBounds(colW * 1, 0, colW, getHeight());
    loop8.setBounds(colW * 2, 0, colW, getHeight());
    loop16.setBounds(colW * 3, 0, colW, getHeight());
    loopManual.setBounds(colW * 4, 0, colW, getHeight());
}

void LoopingComponent::buttonClicked(juce::Button* button)
{
    double currentPosition = player->getCurrentPosition();

    if (button == &loop2) {
        player->startAudioLoop(currentPosition - 2.0, currentPosition);
    }
    if (button == &loop4) {
        player->startAudioLoop(currentPosition - 4.0, currentPosition);
    }
    if (button == &loop8) {
        player->startAudioLoop(currentPosition - 8.0, currentPosition);
    }
    if (button == &loop16) {
        player->startAudioLoop(currentPosition - 16.0, currentPosition);
    }
    if (button == &loopManual) {
        if (loopManual.getToggleState() == true) {
            manualLoopStart = currentPosition;
        }
        else {
            manualLoopEnd = currentPosition;
        }
        player->startAudioLoop(manualLoopStart, manualLoopEnd);
    }
}
