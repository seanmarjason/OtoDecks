#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"


class TempoAdjuster  :  public juce::Component,
                        public juce::Slider::Listener
{
    public:
        TempoAdjuster(DJAudioPlayer* player);
        ~TempoAdjuster() override;

        /** Callback called by the operating system to render component on screen
         * @param g graphics context used for drawing a component or image
        */
        void paint (juce::Graphics&) override;
        
        /** Callback called when this component's size has been changed
         */
        void resized() override;
        
        /** Callback when the tempo slider is changed
         * @param slider pointer to the slider that was changed
         */
        void sliderValueChanged (juce::Slider *slider) override;

        
    private:
        DJAudioPlayer* player;
        
        juce::Slider tempoSlider;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TempoAdjuster)
};
