/*
  ==============================================================================

    PlayButton.h
    Created: 23 Feb 2022 11:39:05pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class PlayButton  : public juce::Component,
                    public juce::Button::Listener
{
public:
    PlayButton(DJAudioPlayer* player);
    ~PlayButton() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Implement juce::Button::Listener */
    void buttonClicked (juce::Button *) override;
    
private:
    DJAudioPlayer* player;

    juce::TextButton playButton{"PLAY"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayButton)
};
