/*
  ==============================================================================

    TrackNavigator.h
    Created: 23 Feb 2022 11:14:48pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"


//==============================================================================
/*
*/
class TrackNavigator  : public juce::Component,
                        public juce::Slider::Listener
{
public:
    TrackNavigator(DJAudioPlayer* player);
    ~TrackNavigator() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Implement juce::Slider::Listener */
    void sliderValueChanged (juce::Slider *slider) override;
    
    void setValue(double value);

private:
    DJAudioPlayer* player;
    
    juce::Slider trackSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackNavigator)
};
