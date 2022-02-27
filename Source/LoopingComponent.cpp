#include <JuceHeader.h>
#include "LoopingComponent.h"
#include "ColourScheme.h"


LoopingComponent::LoopingComponent(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(jogWheel);

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
    loop2.setColour(juce::ComboBox::outlineColourId, ColourScheme::backgroundColour);

    loop4.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    loop4.setColour(juce::ComboBox::outlineColourId, ColourScheme::backgroundColour);

    loop8.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    loop8.setColour(juce::ComboBox::outlineColourId, ColourScheme::backgroundColour);

    loopManual.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    loopManual.setColour(juce::ComboBox::outlineColourId, ColourScheme::backgroundColour);
}


void LoopingComponent::resized()
{
    double colW = getWidth() / 4;
    double rowH = getHeight() / 4;
    
    jogWheel.setBounds(0, 0, getWidth(), rowH * 3);

    loop2.setBounds(     colW * 0, rowH * 3, colW, rowH * 1);
    loop4.setBounds(     colW * 1, rowH * 3, colW, rowH * 1);
    loop8.setBounds(     colW * 2, rowH * 3, colW, rowH * 1);
    loopManual.setBounds(colW * 3, rowH * 3, colW, rowH * 1);
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
