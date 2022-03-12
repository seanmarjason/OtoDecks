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
    
    double size = calculateSize();
    double center = size / 2 + margin;
    int radius = size / 2;
    
    g.fillEllipse (margin, margin, size, size);
    
        
    if (player->isPlaying())
    {
        point.x = center + radius * std::cos((float) player->getCurrentPosition());
        point.y = center + radius * std::sin((float) player->getCurrentPosition());
    }
    
    g.setColour (ColourScheme::greyAscent);
    g.drawLine(point.x, point.y, center, center, 5);

}

void JogWheel::resized()
{
    if (player->getCurrentPosition() == 0)
    {
        double size = calculateSize();
        double center = size / 2 + margin;
        int radius = size / 2;

        point.x = center + radius * std::cos((float) 0);
        point.y = center + radius * std::sin((float) 0);
    }
}

void JogWheel::update()
{
}

double JogWheel::calculateSize()
{
    double margin = 10;
    double width = getWidth();
    double height = getHeight();
    double size = ((width <= height) ? width : height) - (margin * 2);
    return size;
}

void JogWheel::mouseDown(const juce::MouseEvent &event)
{
    std::cout << "Mouse Down" << std::endl;
    player->pause();
}


void JogWheel::mouseUp(const juce::MouseEvent &event)
{
    std::cout << "Mouse Up" << std::endl;
    player->play();
}

void JogWheel::mouseDrag(const juce::MouseEvent &event)
{
    std::cout << "Mouse Drag | " << "X: " << event.x << " Y: " << event.y << std::endl;
}
