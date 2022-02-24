#pragma once

#include <JuceHeader.h>
#include "ColourScheme.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
class MainComponent  :  public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;
    
    
    /** Prepare the audio app component for playback
     * @param samplesPerBlockExpected number of samples source will supply for each audio block
     * @param sampleRate sample rate for output
    */
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    
    /** Called repeatedly to fetch subsequent blocks of audio data
     * @param bufferToFill The destination buffer to fill with audio data
    */
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    
    /** Allows the source to release anything it no longer needs after playback has stopped
    */
    void releaseResources() override;

    
    /** Callback called by the operating system to render component on screen
     * @param g graphics context used for drawing a component or image
    */
    void paint (juce::Graphics& g) override;
    
    
    /** Callback called when this component's size has been changed
     */
    void resized() override;
    

private:
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{100};
    
    DJAudioPlayer player1{formatManager};
    DJAudioPlayer player2{formatManager};
    DJAudioPlayer player3{formatManager};
    DJAudioPlayer player4{formatManager};
    
    DeckGUI deckGUI1{&player1, formatManager, thumbCache};
    DeckGUI deckGUI2{&player2, formatManager, thumbCache};
    DeckGUI deckGUI3{&player3, formatManager, thumbCache};
    DeckGUI deckGUI4{&player4, formatManager, thumbCache};
    
    juce::MixerAudioSource mixerSource;
    
    PlaylistComponent playlistComponent{&deckGUI1, &deckGUI2, &deckGUI3, &deckGUI4};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
