/*
  ==============================================================================

    DeckGUI.cpp
    Created: 31 Jan 2022 8:16:11pm
    Author:  Sean Marjason

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ColourScheme.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager & formatManagerToUse,
                 juce::AudioThumbnailCache & cacheToUse
                 ) : player(_player), waveformDisplay(formatManagerToUse, cacheToUse) // initialisation list
{
    
    trackTitle.setText("---", juce::dontSendNotification);
    trackTitle.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    trackTitle.setJustificationType (juce::Justification::centred);
    
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(tempoSlider);
    addAndMakeVisible(trackNavigator);
    addAndMakeVisible(loopingComponent);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(trackTitle);
    
    stopButton.addListener(this);
    
    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    g.fillAll(ColourScheme::backgroundColour);
    g.setColour (ColourScheme::borderColour);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    
    stopButton.setColour(juce::TextButton::buttonColourId, ColourScheme::redAscent);
    
}

void DeckGUI::resized()
{
    double rowH = getHeight();
    double colW = getWidth() / 10;
    
    trackTitle.setBounds(   colW * 0, rowH / 4 * 0, colW * 3, rowH / 4 * 2);
    
    volSlider.setBounds(    colW * 3 / 2 * 0, rowH / 4 * 2, colW * 3 / 2 * 1, rowH / 4 * 2);
    tempoSlider.setBounds(  colW * 3 / 2 * 1, rowH / 4 * 2, colW * 3 / 2 * 1, rowH / 4 * 2);

    waveformDisplay.setBounds(  colW * 3, rowH / 4 * 0, colW * 5, rowH / 4 * 3);
    trackNavigator.setBounds(        colW * 3, rowH / 4 * 3, colW * 5, rowH / 4 * 1);
    
    playButton.setBounds(       colW * 8, rowH / 4 * 0, colW * 1, rowH / 4 * 2);
    stopButton.setBounds(       colW * 9, rowH / 4 * 0, colW * 1, rowH / 4 * 2);
    loopingComponent.setBounds( colW * 8, rowH / 4 * 2, colW * 2, rowH / 4 * 1);
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &stopButton)
    {
        player->stop();
    }
}

void DeckGUI::loadTrack(juce::String trackName, juce::URL trackURL){
    player->loadURL(trackURL);
    waveformDisplay.loadURL(trackURL);
    trackTitle.setText(trackName, juce::dontSendNotification);
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files){
    return true;
}

void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y){
    if (files.size() == 1) {
        juce::URL file = juce::URL{juce::File{files[0]}};
        loadTrack(file.getFileName(), file);
    }
}

void DeckGUI::timerCallback() {
    waveformDisplay.setPositionRelative(player->getPositionRelative());
    trackNavigator.setValue(player->getPositionRelative());
}
