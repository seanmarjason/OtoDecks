#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class JogWheel  : public juce::AnimatedAppComponent
{
    public:
        JogWheel(DJAudioPlayer* player);
        ~JogWheel() override;

        /** Callback called by the operating system to render component on screen
         * @param g graphics context used for drawing a component or image
        */
        void paint (juce::Graphics&) override;
    
        /** Callback called when this component's size has been changed
         */
        void resized() override;
    
        /** Callback called periodically, at the frequency specified by setFramesPerSecond().
         * Used for advancing animation parameters, checking the mouse position, etc.
         */
        void update() override;
    
        /** Called when a mouse button is pressed
         * @param event the mouse event object containing methods to examine mouse position, key, etc.
         */
        void mouseDown(const juce::MouseEvent &event) override;
    
        /** Called when a mouse button is released
         * @param event the mouse event object containing methods to examine mouse position, key, etc.
         */
        void mouseUp(const juce::MouseEvent &event) override;
    
        /** Called when a mouse button is pressed and subsequently dragged on the screen
         * @param event the mouse event object containing methods to examine mouse position, key, etc.
         */
        void mouseDrag(const juce::MouseEvent &event) override;

    
    private:
        DJAudioPlayer* player;
    
        juce::Point<float> point;
    
        double margin = 10;
    
        double calculateSize();
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JogWheel)
};
