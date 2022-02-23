/*
  ==============================================================================

    StopButton.h
    Created: 23 Feb 2022 11:49:29pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class StopButton  : public juce::Component,
                    public juce::Button::Listener

{
public:
    StopButton(DJAudioPlayer* player);
    ~StopButton() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Implement juce::Button::Listener */
    void buttonClicked (juce::Button *) override;

private:
    DJAudioPlayer* player;

    juce::TextButton stopButton{"STOP"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StopButton)
};
