#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DeckGUI.h"

class PlaylistComponent  :  public juce::Component,
                            public juce::TableListBoxModel,
                            public juce::Button::Listener,
                            public juce::TextEditor::Listener
{
    public:
        PlaylistComponent(DeckGUI* deckGUI1, DeckGUI* deckGUI2, DeckGUI* deckGUI3, DeckGUI* deckGUI4);
        ~PlaylistComponent() override;

    
        /** Callback called by the operating system to render component on screen
         * @param g graphics context used for drawing a component or image
         */
        void paint (juce::Graphics& g) override;
        
        /** Callback called when this component's size has been changed
         */
        void resized() override;
        
        /** Get the number of rows currently in the playlist table
         * @return integer representing number of rows in the table
         */
        int getNumRows() override;
        
        /** Draw the background behind one of the rows in the table based on row state
         * @param g graphics context used for drawing the table row
         * @param rowNumber the index of the row
         * @param width width of the row
         * @param height height of the row
         * @param rowIsSelected boolean reflecting if the row is selected
         */
        void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
        
        /** Draw the content of one of the cells in the table row
         * @param g graphics context used for drawing the table row
         * @param rowNumber the index of the row
         * @param columnId the index of the column
         * @param width width of the row
         * @param height height of the row
         * @param rowIsSelected boolean reflecting if the row is selected
         */
        void paintCell(juce::Graphics &, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
        
        /** Create or update a custom component to go in a cell
         * Will be called whenever a custom component should be updated, such as when the table is changed
         * @param rowNumber the index of the row
         * @param columnId the index of the column
         * @param rowIsSelected boolean reflecting if the row is selected
         * @param existingComponentToUpdate if component is null, then method must create and return a new component,
         * if not then this method must update the component and return it
         * @return juce component to be used in the cell
         */
        juce::Component* refreshComponentForCell (  int rowNumber,
                                                    int columnId,
                                                    bool isRowSelected,
                                                    Component *existingComponentToUpdate
                                                 ) override;
        
        /** Callback when the button is clicked
         * @param button pointer to the button that was clicked
         */
        void buttonClicked(juce::Button* button) override;
        
        /** Add a new track to the playlist and write it to a local file to persist across sessions
         * @param trackName the name of the track to be added
         * @param trackURL the location of the track as a url
         */
        void addTrack(juce::String trackName, juce::URL trackURL, juce::String trackLength);

        
    private:
        juce::TableListBox tableComponent;
        
        juce::XmlElement tracks{"Tracks"};
        juce::XmlElement filteredTracks{"Tracks"};
        juce::XmlElement loadTrackPlaylist();

        juce::TextButton addButton{"Add Track"};
        
        DeckGUI* deckGUI1;
        DeckGUI* deckGUI2;
        DeckGUI* deckGUI3;
        DeckGUI* deckGUI4;
        
        juce::TextEditor searchBar;
        
        void textEditorTextChanged(juce::TextEditor& searchBar) override;

        void filterTable(juce::String& searchValue);
    
        juce::TextButton* createPlaylistRowButton(juce::String buttonText, juce::String buttonId);
    
        juce::File getTracksFile();
    
        juce::String getTrackLength(juce::File result);
    
        juce::AudioFormatManager formatManager;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
