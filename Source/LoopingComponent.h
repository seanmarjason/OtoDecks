/*
  ==============================================================================

    LoopingComponent.h
    Created: 17 Feb 2022 10:44:44pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class LoopingComponent  : public juce::Component
{
public:
    LoopingComponent();
    ~LoopingComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::TextButton loop2{"2"};
    juce::TextButton loop4{"4"};
    juce::TextButton loop8{"8"};
    juce::TextButton loop16{"16"};
    juce::TextButton loopManual{"M"};

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoopingComponent)
};
