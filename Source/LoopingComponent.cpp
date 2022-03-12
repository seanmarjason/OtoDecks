#include <JuceHeader.h>
#include "LoopingComponent.h"
#include "ColourScheme.h"


LoopingComponent::LoopingComponent(DJAudioPlayer* _player) : player(_player)
{
    addAndMakeVisible(jogWheel);

    addAndMakeVisible(loop1);
    addAndMakeVisible(loop2);
    addAndMakeVisible(loop4);
    addAndMakeVisible(loop8);
    
    loop1.setClickingTogglesState(true);
    loop2.setClickingTogglesState(true);
    loop4.setClickingTogglesState(true);
    loop8.setClickingTogglesState(true);
    
    loop1.addListener(this);
    loop2.addListener(this);
    loop4.addListener(this);
    loop8.addListener(this);
}


LoopingComponent::~LoopingComponent()
{
}


void LoopingComponent::paint (juce::Graphics& g)
{
    g.fillAll(ColourScheme::backgroundColour);
    g.setColour (ColourScheme::primaryFont);
    g.setFont (14.0f);

    loop1.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    loop1.setColour(juce::TextButton::buttonOnColourId, ColourScheme::greenAscent);
    loop1.setColour(juce::ComboBox::outlineColourId, ColourScheme::backgroundColour);
    
    loop2.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    loop2.setColour(juce::TextButton::buttonOnColourId, ColourScheme::greenAscent);
    loop2.setColour(juce::ComboBox::outlineColourId, ColourScheme::backgroundColour);

    loop4.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    loop4.setColour(juce::TextButton::buttonOnColourId, ColourScheme::greenAscent);
    loop4.setColour(juce::ComboBox::outlineColourId, ColourScheme::backgroundColour);

    loop8.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    loop8.setColour(juce::TextButton::buttonOnColourId, ColourScheme::greenAscent);
    loop8.setColour(juce::ComboBox::outlineColourId, ColourScheme::backgroundColour);
}


void LoopingComponent::resized()
{
    double colW = getWidth() / 4;
    double rowH = getHeight() / 4;
    
    jogWheel.setBounds(0, 0, getWidth(), rowH * 3);

    loop1.setBounds(colW * 0, rowH * 3, colW, rowH * 1);
    loop2.setBounds(colW * 1, rowH * 3, colW, rowH * 1);
    loop4.setBounds(colW * 2, rowH * 3, colW, rowH * 1);
    loop8.setBounds(colW * 3, rowH * 3, colW, rowH * 1);
}


void LoopingComponent::buttonClicked(juce::Button* button)
{
    double currentPosition = player->getCurrentPosition();
    
    if (button->getToggleState() == false)
    {
        player->endAudioLoop();
    }
    else {
        
        if (button == &loop1)
        {
            player->startAudioLoop(currentPosition - 1.0, currentPosition);
            loop2.setToggleState(false, juce::NotificationType::dontSendNotification);
            loop4.setToggleState(false, juce::NotificationType::dontSendNotification);
            loop8.setToggleState(false, juce::NotificationType::dontSendNotification);
        }
        
        if (button == &loop2)
        {
            player->startAudioLoop(currentPosition - 2.0, currentPosition);
            loop1.setToggleState(false, juce::NotificationType::dontSendNotification);
            loop4.setToggleState(false, juce::NotificationType::dontSendNotification);
            loop8.setToggleState(false, juce::NotificationType::dontSendNotification);
        }
        
        if (button == &loop4)
        {
            player->startAudioLoop(currentPosition - 4.0, currentPosition);
            loop1.setToggleState(false, juce::NotificationType::dontSendNotification);
            loop2.setToggleState(false, juce::NotificationType::dontSendNotification);
            loop8.setToggleState(false, juce::NotificationType::dontSendNotification);
        }
        
        if (button == &loop8)
        {
            player->startAudioLoop(currentPosition - 8.0, currentPosition);
            loop1.setToggleState(false, juce::NotificationType::dontSendNotification);
            loop2.setToggleState(false, juce::NotificationType::dontSendNotification);
            loop4.setToggleState(false, juce::NotificationType::dontSendNotification);
        }
    }
}
