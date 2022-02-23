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
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(loopingComponent);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(trackTitle);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);
    
    volSlider.setRange(0.0, 2.0, 0.01);
    volSlider.setValue(1.0);
    volSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    volSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 25);
    volSlider.setTextValueSuffix(" v");
    
    speedSlider.setRange(0.0, 2.0, 0.01);
    speedSlider.setValue(1.0);
    speedSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    speedSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 25);
    speedSlider.setTextValueSuffix("x");

    posSlider.setRange(0.0, 1.0);
    posSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    
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
    playButton.setColour(juce::TextButton::buttonColourId, ColourScheme::greenAscent);
    
    volSlider.setColour(juce::Slider::rotarySliderOutlineColourId, ColourScheme::greyAscent);
    volSlider.setColour(juce::Slider::rotarySliderFillColourId, ColourScheme::primaryAscent);
    volSlider.setColour(juce::Slider::textBoxOutlineColourId, ColourScheme::backgroundColour);
    
    speedSlider.setColour(juce::Slider::rotarySliderOutlineColourId, ColourScheme::greyAscent);
    speedSlider.setColour(juce::Slider::rotarySliderFillColourId, ColourScheme::primaryAscent);
    speedSlider.setColour(juce::Slider::textBoxOutlineColourId, ColourScheme::backgroundColour);
    
    posSlider.setColour(juce::Slider::backgroundColourId, ColourScheme::greyAscent);
    posSlider.setColour(juce::Slider::trackColourId , ColourScheme::greenAscent);
    posSlider.setColour(juce::Slider::thumbColourId , ColourScheme::greenAscent);
    posSlider.setColour(juce::Slider::textBoxOutlineColourId, ColourScheme::backgroundColour);
    
}

void DeckGUI::resized()
{
    double rowH = getHeight();
    double colW = getWidth() / 10;
    
    trackTitle.setBounds(   colW * 0, rowH / 4 * 0, colW * 3, rowH / 4 * 2);
    
    volSlider.setBounds(    colW * 3 / 2 * 0, rowH / 4 * 2, colW * 3 / 2 * 1, rowH / 4 * 2);
    speedSlider.setBounds(  colW * 3 / 2 * 1, rowH / 4 * 2, colW * 3 / 2 * 1, rowH / 4 * 2);

    waveformDisplay.setBounds(  colW * 3, rowH / 4 * 0, colW * 5, rowH / 4 * 3);
    posSlider.setBounds(        colW * 3, rowH / 4 * 3, colW * 5, rowH / 4 * 1);
    
    playButton.setBounds(       colW * 8, rowH / 4 * 0, colW * 1, rowH / 4 * 2);
    stopButton.setBounds(       colW * 9, rowH / 4 * 0, colW * 1, rowH / 4 * 2);
    loopingComponent.setBounds( colW * 8, rowH / 4 * 2, colW * 2, rowH / 4 * 1);
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked" << std::endl;
        player->start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked" << std::endl;
        player->stop();
    }
}

void DeckGUI::loadTrack(juce::String trackName, juce::URL trackURL){
    player->loadURL(trackURL);
    waveformDisplay.loadURL(trackURL);
    trackTitle.setText(trackName, juce::dontSendNotification);
}

void DeckGUI::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        std::string positionValue = juce::String(slider->getValue(), 2).toStdString();
        std::cout << "positionValue: " << positionValue << std::endl;
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files){
    std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
    return true;
}

void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y){
    std::cout << "DeckGUI::filesDropped" << std::endl;
    if (files.size() == 1) {
        juce::URL file = juce::URL{juce::File{files[0]}};
        loadTrack(file.getFileName(), file);
    }
}

void DeckGUI::timerCallback() {
    waveformDisplay.setPositionRelative(player->getPositionRelative());
    posSlider.setValue(player->getPositionRelative());
}
