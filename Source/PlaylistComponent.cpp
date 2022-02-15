/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 2 Feb 2022 2:25:05pm
    Author:  Sean Marjason

  ==============================================================================
*/

#include <JuceHeader.h>
#include <regex>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(   DeckGUI* _deckGUI1,
                                        DeckGUI* _deckGUI2
                                     ) : deckGUI1(_deckGUI1), deckGUI2(_deckGUI2)
{
    tableComponent.getHeader().addColumn("Track title", 1, 475);
    tableComponent.getHeader().addColumn("", 2, 150);
    tableComponent.getHeader().addColumn("", 3, 150);
    
    tableComponent.setModel(this);
    
    addAndMakeVisible(tableComponent);
    
    loadButton.addListener(this);
    addAndMakeVisible(loadButton);

}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    double rowH = getHeight() / 10;
    tableComponent.setBounds(0, 0, getWidth(), rowH * 9);
    loadButton.setBounds(0, rowH * 9, getWidth(), rowH);
}

int PlaylistComponent::getNumRows(){
    return tracks.getNumChildElements();
};

void PlaylistComponent::paintRowBackground(juce::Graphics & g, int rowNumber, int width, int height, bool rowIsSelected){
    if (rowIsSelected) {
        g.fillAll(juce::Colours::orange);
    }
    else {
        g.fillAll(juce::Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(juce::Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) {
    g.drawText(tracks.getChildElement(rowNumber)->getStringAttribute("name"), 2, 0, width-4, height, juce::Justification::centredLeft, true);
}


juce::Component* PlaylistComponent::refreshComponentForCell ( int rowNumber, int columnId, bool isRowSelected,
                                                             juce::Component *existingComponentToUpdate) {
    if (columnId == 2) {
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* btn = new juce::TextButton{"Load Disk 1"};
            juce::String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    if (columnId == 3) {
        if (existingComponentToUpdate == nullptr) {
            juce::TextButton* btn = new juce::TextButton{"Load Disk 2"};
            juce::String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
}


void PlaylistComponent::buttonClicked(juce::Button* button){
    if (button == &loadButton) {
        std::cout << "Load button was clicked" << std::endl;
        
        juce::FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen()){
            juce::String trackName = juce::URL{chooser.getResult()}.getFileName();
            juce::URL trackURL = juce::URL{chooser.getResult()};
            addTrack(trackName, trackURL);
        }
    }
    else {
        int id = std::stoi(button->getComponentID().toStdString());
        std::string action = button->getName().toStdString();
        juce::String trackName = tracks.getChildElement(id)->getStringAttribute("name");
        juce::URL trackURL = tracks.getChildElement(id)->getStringAttribute("url");
        if (action == "Load Disk 1") {
            std::cout << "Load to track 1: " << trackName << " : " << trackURL.toString(false).toStdString() << std::endl;
            deckGUI1->loadTrack(trackName, trackURL);
        }
        else if (action == "Load Disk 2") {
            std::cout << "Load to track 2: " << trackName << " : " << trackURL.toString(false).toStdString() << std::endl;
            deckGUI2->loadTrack(trackName, trackURL);
        }
        else {
            std::cout << "buttonClicked: '" << action << "' but no action." << std::endl;
        }
    }
}

void PlaylistComponent::addTrack(juce::String trackName, juce::URL trackURL) {
    juce::String trackIdentifier = std::regex_replace(trackName.toStdString(), std::regex("\%20"),"_");
    juce::String trackDisplayName = std::regex_replace(trackName.toStdString(), std::regex("\%20")," ");
    juce::String trackUrlString = trackURL.toString(false).toStdString();
    
    juce::XmlElement* newTrack = new juce::XmlElement (trackIdentifier);
    newTrack->setAttribute("name", trackDisplayName);
    newTrack->setAttribute("url", trackUrlString);
    tracks.addChildElement(newTrack);
    
    std::cout << tracks.toString() << std::endl;
        
    tableComponent.updateContent();
    repaint();
}
