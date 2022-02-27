#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

class JogWheel  : public juce::AnimatedAppComponent
{
    public:
        JogWheel(DJAudioPlayer* player);
        ~JogWheel() override;

        void paint (juce::Graphics&) override;
        void resized() override;
    
        void update() override;

    
    private:
        DJAudioPlayer* player;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JogWheel)
};
