/*
  ==============================================================================

    PlayButton.h
    Created: 23 Feb 2022 11:39:05pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class PlayButton  : public juce::Component,
                    public juce::Button::Listener
{
public:
    PlayButton(DJAudioPlayer* player);
    ~PlayButton() override;

    /** Callback called by the operating system to render component on screen
     * @param g graphics context used for drawing a component or image
    */
    void paint (juce::Graphics&) override;
    
    /** Callback called when this component's size has been changed
     */
    void resized() override;
    
    /** Callback when the play button is clicked
     * @param button pointer to the button that was clicked
     */
    void buttonClicked (juce::Button *) override;
    
private:
    DJAudioPlayer* player;

    juce::TextButton playButton{"PLAY"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayButton)
};
