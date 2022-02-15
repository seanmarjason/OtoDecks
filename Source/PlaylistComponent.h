/*
  ==============================================================================

    PlaylistComponent.h
    Created: 2 Feb 2022 2:25:05pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DeckGUI.h"

//==============================================================================
/*
*/
class PlaylistComponent  :  public juce::Component,
                            public juce::TableListBoxModel,
                            public juce::Button::Listener
{
public:
    PlaylistComponent(DeckGUI* deckGUI1, DeckGUI* deckGUI2);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;
    void paintRowBackground(juce::Graphics &, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    
    juce::Component* refreshComponentForCell (  int rowNumber,
                                                int columnId,
                                                bool isRowSelected,
                                                Component *existingComponentToUpdate
                                             ) override;
    
    void buttonClicked(juce::Button* button) override;
    
    void addTrack(juce::String trackName, juce::URL trackURL);

private:
    
    juce::TableListBox tableComponent;
    std::vector<std::pair<std::string, juce::URL>> trackTitles;
    
    juce::XmlElement tracks{"Tracks"};
    
    juce::TextButton loadButton{"Add Track"};
    
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
