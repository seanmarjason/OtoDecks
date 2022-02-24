#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Set the size of the component
    setSize (1280, 800);

    // Request permissions to open input channels
    // (some platforms require permissions)
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 8); });
    }
    else
    {
        // Specify number of input and output channels to open
        setAudioChannels (0, 8);
    }
    
    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(deckGUI3);
    addAndMakeVisible(deckGUI4);

    addAndMakeVisible(playlistComponent);
    
    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player3.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player4.prepareToPlay(samplesPerBlockExpected, sampleRate);
        
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
    mixerSource.addInputSource(&player3, false);
    mixerSource.addInputSource(&player4, false);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
    player2.releaseResources();
    player3.releaseResources();
    player4.releaseResources();
    
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(ColourScheme::backgroundColour);
}

void MainComponent::resized()
{
    double colW = getWidth() / 10;
    double rowH = getHeight() / 4;
    
    playlistComponent.setBounds(0, 0, colW * 3, getHeight());
    
    deckGUI1.setBounds(colW * 3, rowH * 0, colW * 7, rowH * 1);
    deckGUI2.setBounds(colW * 3, rowH * 1, colW * 7, rowH * 1);
    deckGUI3.setBounds(colW * 3, rowH * 2, colW * 7, rowH * 1);
    deckGUI4.setBounds(colW * 3, rowH * 3, colW * 7, rowH * 1);
}
