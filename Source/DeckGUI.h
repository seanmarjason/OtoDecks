/*
  ==============================================================================

    DeckGUI.h
    Created: 31 Jan 2022 8:16:11pm
    Author:  Sean Marjason

  ==============================================================================
*/

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

//==============================================================================
/*
*/
class DeckGUI  :    public juce::Component,
                    public juce::FileDragAndDropTarget,
                    public juce::Timer

{
public:
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse);
    
    ~DeckGUI();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Implement drag and drop */
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped (const juce::StringArray &files, int x, int y) override;
    
    void timerCallback() override;
    
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
