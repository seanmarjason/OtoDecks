#include <JuceHeader.h>
#include "DeckGUI.h"
#include "ColourScheme.h"


DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager & formatManagerToUse,
                 juce::AudioThumbnailCache & cacheToUse
                 ) : player(_player), waveformDisplay(formatManagerToUse, cacheToUse)
{
    trackTitle.setText("---", juce::dontSendNotification);
    trackTitle.setColour (juce::Label::textColourId, ColourScheme::greenAscent);
    trackTitle.setJustificationType (juce::Justification::centred);
    
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(tempoSlider);
    addAndMakeVisible(trackNavigator);
    addAndMakeVisible(loopingComponent);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(trackTitle);
            
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

    g.setColour (ColourScheme::primaryFont);
    g.setFont (14.0f);
        
}


void DeckGUI::resized()
{
    double rowH = getHeight();
    double colW = getWidth() / 12;
    
    trackTitle.setBounds(   colW * 0, rowH / 4 * 0, colW * 3, rowH / 4 * 2);
    
    volSlider.setBounds(    colW * 3 / 2 * 0, rowH / 4 * 2, colW * 3 / 2 * 1, rowH / 4 * 2);
    tempoSlider.setBounds(  colW * 3 / 2 * 1, rowH / 4 * 2, colW * 3 / 2 * 1, rowH / 4 * 2);

    waveformDisplay.setBounds(  colW * 3, rowH / 4 * 0, colW * 5, rowH / 4 * 3);
    trackNavigator.setBounds(        colW * 3, rowH / 4 * 3, colW * 5, rowH / 4 * 1);
    
    loopingComponent.setBounds( colW * 8, rowH * 0, colW * 3, rowH * 1);
    
    playButton.setBounds(       colW * 11, rowH / 2 * 0, colW * 1, rowH / 2 * 1);
    stopButton.setBounds(       colW * 11, rowH / 2 * 1, colW * 1, rowH / 2 * 1);

}


void DeckGUI::loadTrack(juce::String trackName, juce::URL trackURL)
{
    player->loadURL(trackURL);
    waveformDisplay.loadURL(trackURL);
    trackTitle.setText(trackName, juce::dontSendNotification);
}


bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
    return true;
}


void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y)
{
    if (files.size() == 1)
    {
        juce::URL file = juce::URL{juce::File{files[0]}};
        loadTrack(file.getFileName(), file);
    }
}


void DeckGUI::timerCallback()
{
    waveformDisplay.setPositionRelative(player->getPositionRelative());
    trackNavigator.setValue(player->getPositionRelative());
}
