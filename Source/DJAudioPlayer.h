#pragma once

#include <JuceHeader.h>

class DJAudioPlayer :   public juce::AudioSource,
                        public juce::Timer
{
    public:
        DJAudioPlayer(juce::AudioFormatManager& _formatManager);
        ~DJAudioPlayer();
        
    
        /** Prepare the audio app component for playback
         * @param samplesPerBlockExpected number of samples source will supply for each audio block
         * @param sampleRate sample rate for output
        */
        void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
        /** Called repeatedly to fetch subsequent blocks of audio data
         * @param bufferToFill The destination buffer to fill with audio data
        */
        void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    
        /** Allows the source to release anything it no longer needs after playback has stopped
        */
        void releaseResources() override;
    
        /** Load a URL containing an audio file into the audio format reader source
         * @param audioURL the url to be loaded
        */
        void loadURL(juce::URL audioURL);
    
        /** Adjust the gain / volume of the audio source
         * @param gain value to set the gain to
        */
        void setGain(double gain);
    
        /** Adjust the speed of the audio source
         * @param ratio value to set the speed to
        */
        void setSpeed(double ratio);
    
        /** Adjust the position of the audio source in seconds
         * @param posInSecs value in seconds to set the position to
        */
        void setPosition(double posInSecs);
    
        /** Adjust the position of the audio source relatively
         * @param pos value as proportion of total track length to set the position to
        */
        void setPositionRelative(double pos);
        
        /** Start the audio source
        */
        void pause();
    
        /** Stop the audio source
        */
        void play();
    
        /** Check if the audio source is playing
         * @return boolean representing if the audio source is playing
        */
        bool isPlaying();
    
        /** Get the relative position of the playhead
         * @return double representing relative position of the playhead
        */
        double getPositionRelative();
    
        /** Get the position in seconds of the playhead
         * @return double containing position in seconds of the playhead
        */
        double getCurrentPosition();
    
        /** Callback routine that gets called periodically based on timer
         */
        void timerCallback() override;
    
        /** Trigger a loop of the audio source
         * @param startPos the position in the track to start the loop in seconds
         * @param endPos the position in the track to end the loop in seconds
        */
        void startAudioLoop(double startPos, double endPos);
    
        /** End looping of the audio source
        */
        void endAudioLoop();
    
        /** Get the length in seconds of the track as a string
         * @return string representing length in seconds of the playhead (M.SS)
        */
        std::string getTrackLengthString();
    
        /** Get the position in seconds of the playhead as a string
         * @return string representing position in seconds of the playhead (M.SS)
        */
        std::string getTrackPositionString();
    
    
    private:
        juce::AudioFormatManager& formatManager;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        juce::AudioTransportSource transportSource;
        juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
    
        bool looping;
        double startLoop;
        double endLoop;
};

