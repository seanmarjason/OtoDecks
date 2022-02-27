#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "VolumeAdjuster.h"
#include "TempoAdjuster.h"
#include "TrackNavigator.h"
#include "PlayButton.h"
#include "StopButton.h"
#include "WaveformDisplay.h"
#include "LoopingComponent.h"

class DeckGUI  :    public juce::Component,
                    public juce::FileDragAndDropTarget,
                    public juce::Timer
{
    public:
        DeckGUI(DJAudioPlayer* player,
                juce::AudioFormatManager & formatManagerToUse,
                juce::AudioThumbnailCache & cacheToUse);
    
        ~DeckGUI();

    
        /** Callback called by the operating system to render component on screen
         * @param g graphics context used for drawing a component or image
        */
        void paint (juce::Graphics&) override;
    
        /** Callback called when this component's size has been changed
         */
        void resized() override;
        
        /** Callback to check whether this target is interested in the set of files being offered
         * @param files the set of (absolute) pathnames of the files that the user is dragging
         * @return boolean representing whether component listens to file drag
         */
        bool isInterestedInFileDrag(const juce::StringArray &files) override;
    
        /** Callback to indicate that the user has dropped the files onto this component
         @param files the set of (absolute) pathnames of the files that the user is dragging
         @param x the mouse x position, relative to this component
         @param y the mouse y position, relative to this component
         */
        void filesDropped (const juce::StringArray &files, int x, int y) override;
        
        /** Callback routine that gets called periodically based on timer
         */
        void timerCallback() override;
        
        /** Orchestrating function to load track into the gui and audio player
         @param trackName the name of the track to be loaded
         @param trackURL the location of the track as a url
         */
        void loadTrack(juce::String trackName, juce::URL trackURL);

    
    private:
        DJAudioPlayer* player;
        
        PlayButton playButton{player};
        StopButton stopButton{player};
        
        VolumeAdjuster volSlider{player};
        TempoAdjuster tempoSlider{player};
        
        TrackNavigator trackNavigator{player};
        
        juce::Label trackTitle;
        
        WaveformDisplay waveformDisplay;
        
        LoopingComponent loopingComponent{player};
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
