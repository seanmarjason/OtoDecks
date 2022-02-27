#include <JuceHeader.h>
#include "ColourScheme.h"
#include "WaveformDisplay.h"


WaveformDisplay::WaveformDisplay(   juce::AudioFormatManager & formatManagerToUse,
                                    juce::AudioThumbnailCache & cacheToUse
                                 ) : audioThumb(1000, formatManagerToUse, cacheToUse),
                                     fileLoaded(false),
                                     position(0)
{
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}


void WaveformDisplay::paint (juce::Graphics& g)
{
    g.fillAll(ColourScheme::backgroundColour);

    g.setColour (ColourScheme::primaryAscent);
    
    if (fileLoaded)
    {
        audioThumb.drawChannel(g, getLocalBounds(), 0, audioThumb.getTotalLength(), 0, 1.0f);
        g.setColour(juce::Colours::lightgreen);
        g.drawRect(position * getWidth(), 0, getWidth() / 100, getHeight());
    }
    else
    {
        g.setFont (20.0f);
        g.drawText ("File not loaded...", getLocalBounds(), juce::Justification::centred, true); // draw some placeholder text
    }
}


void WaveformDisplay::resized()
{
}


void WaveformDisplay::loadURL(juce::URL audioURL)
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    
    if (fileLoaded)
    {
        repaint();
    }
    else
    {
        std::cout << "Error: WFD::loadURL not loaded" << std::endl;
    }
}


void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    repaint();
}


void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position) {
        position = pos;
        repaint();
    }
}
