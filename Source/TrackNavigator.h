#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class TrackNavigator  : public juce::Component,
                        public juce::Slider::Listener
{
    public:
        TrackNavigator(DJAudioPlayer* player);
        ~TrackNavigator() override;

    
        /** Callback called by the operating system to render component on screen
         * @param g graphics context used for drawing a component or image
        */
        void paint (juce::Graphics&) override;
        
        /** Callback called when this component's size has been changed
         */
        void resized() override;
        
        /** Callback when the track nvaigation slider is changed
         * @param slider pointer to the slider that was changed
         */
        void sliderValueChanged (juce::Slider *slider) override;
        
        /** Set the relative value of the track navigator
         * @param value double representing the relative value to set the navigator to
         */
        void setValue(double value);

    
    private:
        DJAudioPlayer* player;
        
        juce::Slider trackSlider;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrackNavigator)
};
