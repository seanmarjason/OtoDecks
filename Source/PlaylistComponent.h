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

//==============================================================================
/*
*/
class PlaylistComponent  :  public juce::Component,
                            public juce::TableListBoxModel,
                            public juce::Button::Listener
{
public:
    PlaylistComponent();
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
    
    juce::TextButton loadButton{"Add Track"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
