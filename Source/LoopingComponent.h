/*
  ==============================================================================

    LoopingComponent.h
    Created: 17 Feb 2022 10:44:44pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class LoopingComponent  :   public juce::Component,
                            public juce::Button::Listener
{
public:
    LoopingComponent(DJAudioPlayer* player);
    
    ~LoopingComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Implement juce::Button::Listener */
    void buttonClicked (juce::Button *) override;

private:
    juce::TextButton loop2{"2"};
    juce::TextButton loop4{"4"};
    juce::TextButton loop8{"8"};
    juce::TextButton loop16{"16"};
    juce::TextButton loopManual{"M"};
    
    DJAudioPlayer* player;
    
    double manualLoopStart;
    double manualLoopEnd;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoopingComponent)
};
