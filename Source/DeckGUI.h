/*
  ==============================================================================

    DeckGUI.h
    Created: 31 Jan 2022 8:16:11pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class DeckGUI  :    public juce::Component,
                    public juce::Button::Listener,
                    public juce::Slider::Listener

{
public:
    DeckGUI(DJAudioPlayer* _player);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    /** Implement juce::Button::Listener */
    void buttonClicked (juce::Button *) override;
    
    /** Implement juce::Slider::Listener */
    void sliderValueChanged (juce::Slider *slider) override;
    
    /** Implement drag and drop */

    

private:
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    
    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;
    
    DJAudioPlayer* player;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
