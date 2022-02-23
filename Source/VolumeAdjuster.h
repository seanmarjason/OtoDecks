/*
  ==============================================================================

    VolumeAdjuster.h
    Created: 23 Feb 2022 10:24:05pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class VolumeAdjuster  : public juce::Component,
                        public juce::Slider::Listener

{
public:
    VolumeAdjuster(DJAudioPlayer* player);
    ~VolumeAdjuster() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Implement juce::Slider::Listener */
    void sliderValueChanged (juce::Slider *slider) override;


private:
    DJAudioPlayer* player;

    juce::Slider volSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeAdjuster)
};
