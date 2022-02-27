#include <JuceHeader.h>
#include <regex>
#include "PlaylistComponent.h"
#include "ColourScheme.h"


PlaylistComponent::PlaylistComponent(
                                      DeckGUI* _deckGUI1,
                                      DeckGUI* _deckGUI2,
                                      DeckGUI* _deckGUI3,
                                      DeckGUI* _deckGUI4
                                    ) : deckGUI1(_deckGUI1),
                                        deckGUI2(_deckGUI2),
                                        deckGUI3(_deckGUI3),
                                        deckGUI4(_deckGUI4)
{
    tableComponent.setRowHeight(50);
    tableComponent.getHeader().addColumn("Track title", 1, 300);
    tableComponent.getHeader().addColumn("Length", 2, 100);
    tableComponent.getHeader().addColumn("", 3, 50);
    tableComponent.getHeader().addColumn("", 4, 50);
    tableComponent.getHeader().addColumn("", 5, 50);
    tableComponent.getHeader().addColumn("", 6, 50);
    tableComponent.getHeader().setStretchToFitActive(true);

    tableComponent.setModel(this);
    
    addAndMakeVisible(tableComponent);
    addAndMakeVisible(addButton);
    addAndMakeVisible(searchBar);
    
    addButton.addListener(this);
    addAndMakeVisible(addButton);
    
    tracks = loadTrackPlaylist();
    filteredTracks = tracks;
    
    searchBar.setJustification(juce::Justification::centred);
    searchBar.setTextToShowWhenEmpty("Search for track", ColourScheme::primaryFont);
    searchBar.addListener(this);
}


PlaylistComponent::~PlaylistComponent()
{
}


void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll(ColourScheme::backgroundColour);
    tableComponent.setColour(juce::ListBox::backgroundColourId, ColourScheme::backgroundColour);
    searchBar.setColour(juce::TextEditor::backgroundColourId, ColourScheme::secondaryColour);
    searchBar.setColour(juce::TextEditor::outlineColourId, ColourScheme::secondaryColour);
    addButton.setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    addButton.setColour(juce::ComboBox::outlineColourId, ColourScheme::backgroundColour);
    tableComponent.getHeader().setColour(juce::TableHeaderComponent::backgroundColourId, ColourScheme::backgroundColour);
    tableComponent.getHeader().setColour(juce::TableHeaderComponent::outlineColourId , ColourScheme::backgroundColour);
    tableComponent.getHeader().setColour(juce::TableHeaderComponent::textColourId , ColourScheme::primaryAscent);
}


void PlaylistComponent::resized()
{
    double rowH = getHeight() / 50;
    
    searchBar.setBounds(0, rowH * 0, getWidth(), rowH * 2.5);
    tableComponent.setBounds(0, rowH * 2.5, getWidth(), rowH * 45);
    addButton.setBounds(0, rowH * 47.5, getWidth(), rowH * 2.5);
}


int PlaylistComponent::getNumRows()
{
    return filteredTracks.getNumChildElements();
};


void PlaylistComponent::paintRowBackground(juce::Graphics & g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) {
        g.fillAll(ColourScheme::primaryAscent);
    }
    else {
        g.fillAll(ColourScheme::backgroundColour);
    }
}


void PlaylistComponent::paintCell(juce::Graphics & g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour (ColourScheme::primaryFont);
    g.drawText(filteredTracks.getChildElement(rowNumber)->getStringAttribute("name"), 2, 0, width-4, height, juce::Justification::centredLeft, true);
}


juce::Component* PlaylistComponent::refreshComponentForCell ( int rowNumber, int columnId, bool isRowSelected,
                                                             juce::Component *existingComponentToUpdate)
{
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            existingComponentToUpdate = createPlaylistRowButton("1", std::to_string(rowNumber));
        }
    }
    if (columnId == 4)
    {
        if (existingComponentToUpdate == nullptr)
        {
            existingComponentToUpdate = createPlaylistRowButton("2", std::to_string(rowNumber));
        }
    }
    if (columnId == 5)
    {
        if (existingComponentToUpdate == nullptr)
        {
            existingComponentToUpdate = createPlaylistRowButton("3", std::to_string(rowNumber));
        }
    }
    if (columnId == 6)
    {
        if (existingComponentToUpdate == nullptr)
        {
            existingComponentToUpdate = createPlaylistRowButton("4", std::to_string(rowNumber));
        }
    }
    return existingComponentToUpdate;
}


void PlaylistComponent::buttonClicked(juce::Button* button)
{
    if (button == &addButton)
    {
        juce::FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
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
        
        if (action == "1")
        {
            deckGUI1->loadTrack(trackName, trackURL);
        }
        else if (action == "2")
        {
            deckGUI2->loadTrack(trackName, trackURL);
        }
        else if (action == "3")
        {
            deckGUI3->loadTrack(trackName, trackURL);
        }
        else if (action == "4")
        {
            deckGUI4->loadTrack(trackName, trackURL);
        }
        else
        {
            std::cout << "buttonClicked: '" << action << "' but no action." << std::endl;
        }
    }
}


void PlaylistComponent::addTrack(juce::String trackName, juce::URL trackURL)
{
    // handle unsupported file names
    juce::String trackIdentifier = std::regex_replace(trackName.toStdString(), std::regex("\%20"),"_"); // replace space chars in id
    juce::String trackDisplayName = std::regex_replace(trackName.toStdString(), std::regex("\%20")," "); // replace space chars in name
    juce::String trackUrlString = trackURL.toString(false).toStdString();
    
    juce::XmlElement* newTrack = new juce::XmlElement (trackIdentifier);
    newTrack->setAttribute("name", trackDisplayName);
    newTrack->setAttribute("url", trackUrlString);
    tracks.addChildElement(newTrack);
    
    juce::File tracksFile = getTracksFile();
        
    tracks.writeTo(tracksFile);
        
    filteredTracks = tracks;
    tableComponent.updateContent();
    repaint();
}


juce::XmlElement PlaylistComponent::loadTrackPlaylist()
{
    juce::File tracksFile = getTracksFile();
    
    if (!tracksFile.existsAsFile())
    {
        tracksFile.create();
        juce::XmlElement newTrackList{"Tracks"};
        newTrackList.writeTo(tracksFile);
    }
    std::unique_ptr<juce::XmlElement> savedPlaylist = juce::parseXML(tracksFile);
    juce::XmlElement playlist = *savedPlaylist;
    return playlist;

}


void PlaylistComponent::textEditorTextChanged(juce::TextEditor& searchBar)
{
    juce::String searchValue = searchBar.getText();
    filterTable(searchValue);
};


void PlaylistComponent::filterTable(juce::String& searchValue)
{
    if (searchValue != "")
    {
        filteredTracks.deleteAllChildElements(); // clear filtered tracks
                
        for (auto* element : tracks.getChildIterator()) // get new filtered tracks
        {
            if (element->getStringAttribute("name").containsIgnoreCase(searchValue)) {
                juce::XmlElement* newElement = new juce::XmlElement(*element);
                filteredTracks.addChildElement(newElement);
            }
        }
    }
    else
    {
        filteredTracks = tracks; // reset filtered tracks to all tracks
    }
    tableComponent.updateContent();
    repaint();
};


juce::TextButton* PlaylistComponent::createPlaylistRowButton(juce::String buttonText, juce::String buttonId)
{
    juce::TextButton* btn = new juce::TextButton{buttonText};
    btn->setColour(juce::TextButton::buttonColourId, ColourScheme::secondaryColour);
    btn->setColour(juce::ComboBox::outlineColourId, ColourScheme::backgroundColour);
    btn->setComponentID(buttonId);
    btn->addListener(this);
    
    return btn;
}


juce::File PlaylistComponent::getTracksFile()
{
    juce::File directory = juce::File::getSpecialLocation(juce::File::userMusicDirectory);
    return directory.getChildFile("OtodecksPlaylist.xml");;
}
