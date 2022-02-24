/*
  ==============================================================================

    ColourScheme.h
    Created: 22 Feb 2022 9:20:55pm
    Author:  Sean Marjason

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ColourScheme
{
public:
    /** Base colour for the application, to be used as borders around components */
    static juce::Colour borderColour;
    
    /** Base colour for components */
    static juce::Colour backgroundColour;
    
    /** Colour for actionable elements of components */
    static juce::Colour secondaryColour;
    
    /** Primary ascent colour for key features of application */
    static juce::Colour primaryAscent;
    
    /** Red secondary ascent colour */
    static juce::Colour redAscent;
    
    /** Green secondary ascent colour */
    static juce::Colour greenAscent;
    
    /** Grey secondary ascent colour */
    static juce::Colour greyAscent;
    
private:
    
};
