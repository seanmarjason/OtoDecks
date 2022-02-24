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

class LoopingComponent  :   public juce::Component,
                            public juce::Button::Listener
{
    public:
        LoopingComponent(DJAudioPlayer* player);
        ~LoopingComponent() override;

        /** Callback called by the operating system to render component on screen
         * @param g graphics context used for drawing a component or image
        */
        void paint (juce::Graphics& g) override;
    
        /** Callback called when this component's size has been changed
         */
        void resized() override;
        
        /** Callback when the button is clicked
         * @param button pointer to the button that was clicked
         */
        void buttonClicked (juce::Button* button) override;

    private:
        juce::TextButton loop2{"-2s"};
        juce::TextButton loop4{"-4s"};
        juce::TextButton loop8{"-8s"};
        juce::TextButton loopManual{"M"};
        
        DJAudioPlayer* player;
        
        double manualLoopStart;
        double manualLoopEnd;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoopingComponent)
};
