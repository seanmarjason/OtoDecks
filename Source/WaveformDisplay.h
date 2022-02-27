#pragma once

#include <JuceHeader.h>

class WaveformDisplay  :    public juce::Component,
                            public juce::ChangeListener
{
    public:
        WaveformDisplay(juce::AudioFormatManager & formatManagerToUse,
                        juce::AudioThumbnailCache & cacheToUse);
        ~WaveformDisplay();

    
        /** Callback called by the operating system to render component on screen
         * @param g graphics context used for drawing a component or image
        */
        void paint (juce::Graphics&) override;
        
        /** Callback called when this component's size has been changed
         */
        void resized() override;
        
        /** Receives change event callbacks that are sent out by a ChangeBroadcaster
         * @param source pointer to the Change Broadcaster
         */
        void changeListenerCallback(juce::ChangeBroadcaster *source) override;
        
        /** Load a URL containing an audio file into the audio thumbnail
         * @param audioURL the url to be loaded
        */
        void loadURL(juce::URL audioURL);
        
        /** Adjust the position of the playhead in the waveform
         * @param pos value as proportion of total track length to set the position to
        */
        void setPositionRelative(double pos);
        
    
    private:
        juce::AudioThumbnail audioThumb;
        bool fileLoaded;
        double position;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
