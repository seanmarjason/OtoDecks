#include "ColourScheme.h"


ColourScheme::ColourScheme()
{
}

ColourScheme::~ColourScheme()
{
}

// Main Colours
juce::Colour ColourScheme::borderColour = juce::Colour(19,19,26); // app background
juce::Colour ColourScheme::backgroundColour = juce::Colour(28,28,36); // component containers
juce::Colour ColourScheme::secondaryColour = juce::Colour(41,41,50); // actionable components (buttons/sliders/etc)
juce::Colour ColourScheme::primaryFont = juce::Colour(255, 255, 255); // primary font

// Ascent colours
juce::Colour ColourScheme::primaryAscent = juce::Colour(80,181,255); // blue
juce::Colour ColourScheme::redAscent = juce::Colour(252,90,90); // red
juce::Colour ColourScheme::greenAscent = juce::Colour(50,151,113); // green
juce::Colour ColourScheme::greyAscent = juce::Colour(211, 211, 211); // light grey
juce::Colour ColourScheme::darkgreyAscent = juce::Colour(150, 150, 150); // dark grey
