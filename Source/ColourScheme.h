#pragma once

#include <JuceHeader.h>

class ColourScheme
{
    public:
        ColourScheme();
        ~ColourScheme();

        /** Base colour for the application, to be used as borders around components */
        static juce::Colour borderColour;
        
        /** Base colour for components */
        static juce::Colour backgroundColour;
        
        /** Colour for actionable elements of components */
        static juce::Colour secondaryColour;
    
        /** Primary Font colour */
        static juce::Colour primaryFont;
        
        /** Primary ascent colour for key features of application */
        static juce::Colour primaryAscent;
        
        /** Red secondary ascent colour */
        static juce::Colour redAscent;
        
        /** Green secondary ascent colour */
        static juce::Colour greenAscent;
        
        /** Grey secondary ascent colour */
        static juce::Colour greyAscent;
    
        /** Dark Grey secondary ascent colour */
        static juce::Colour darkgreyAscent;
        
    
    private:
        // nil
};
