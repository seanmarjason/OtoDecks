/*
  ==============================================================================

    TempoAdjuster.h
    Created: 23 Feb 2022 10:45:18pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class TempoAdjuster  :    public juce::Component,
                        public juce::Slider::Listener

{
public:
    TempoAdjuster(DJAudioPlayer* player);
    ~TempoAdjuster() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Implement juce::Slider::Listener */
    void sliderValueChanged (juce::Slider *slider) override;

    
private:
    DJAudioPlayer* player;
    
    juce::Slider tempoSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TempoAdjuster)
};
