#include <JuceHeader.h>
#include <cmath>
#include "JogWheel.h"
#include "ColourScheme.h"

JogWheel::JogWheel(DJAudioPlayer* _player) : player(_player)
{
    setFramesPerSecond(60);
}

JogWheel::~JogWheel()
{
}

void JogWheel::paint (juce::Graphics& g)
{
    g.fillAll (ColourScheme::backgroundColour);
    
    g.setColour (ColourScheme::borderColour);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (ColourScheme::secondaryColour);
    
    double width = getWidth();
    double height = getHeight();
    double margin = 10;
    double size = ((width <= height) ? width : height) - (margin * 2);
    double center = size / 2 + margin;
    g.fillEllipse (margin, margin, size, size);
    
    int radius = size / 2;
    
    juce::Point<float> p (center + radius - (margin * 2), center + radius - (margin * 2));
    
    if (player->isPlaying())
    {
        p.x = center + radius * std::cos((float) getFrameCounter() * 0.04f);
        p.y = center + radius * std::sin((float) getFrameCounter() * 0.04f);
    }
    
    g.setColour (ColourScheme::greyAscent);
    g.drawLine(p.x, p.y, center, center, 5);

}

void JogWheel::resized()
{
}

void JogWheel::update()
{
}
