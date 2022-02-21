/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 30 Jan 2022 6:16:37pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource {
    public:
        DJAudioPlayer(juce::AudioFormatManager& _formatManager);
        ~DJAudioPlayer();
        
        void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
        void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
        void releaseResources() override;
    
        void loadURL(juce::URL audioURL);
        void setGain(double gain);
        void setSpeed(double ratio);
        void setPosition(double posInSecs);
        void setPositionRelative(double pos);
        
        void start();
        void stop();
    
        /** get relative position of playhead */
        double getPositionRelative();
    
        double getCurrentPosition();
    
        void startAudioLoop(double startPos, double endPos);
        void stopAudioLoop();
    
    
    private:
        juce::AudioFormatManager& formatManager;
        std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
        juce::AudioTransportSource transportSource;
        juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
    
        bool looping;

};
