#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class VolumeAdjuster  : public juce::Component,
                        public juce::Slider::Listener
{
    public:
        VolumeAdjuster(DJAudioPlayer* player);
        ~VolumeAdjuster() override;

        /** Callback called by the operating system to render component on screen
         * @param g graphics context used for drawing a component or image
        */
        void paint (juce::Graphics&) override;
        
        /** Callback called when this component's size has been changed
         */
        void resized() override;
        
        /** Callback when the volume slider is changed
         * @param slider pointer to the slider that was changed
         */
        void sliderValueChanged (juce::Slider *slider) override;


    private:
        DJAudioPlayer* player;

        juce::Slider volSlider;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeAdjuster)
};
