#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
    
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(volSlider);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    volSlider.addListener(this);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    phase = 0.0;
    dphase = 0.0001;
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    /** Generate sound output */
    auto* leftChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    auto* rightChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
    
    for (auto i=0; i < bufferToFill.numSamples; ++i)
    {
//        double sample = rand.nextDouble() * 0.25; // white noise
//        double sample = fmod(phase, 0.2); // sawtooth wave
        double sample = sin(phase) * 0.1; // sine wave
        leftChan[i] = sample;
        rightChan[i] = sample;
        
        phase += dphase;
    }

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
//    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    
    double rowH = getHeight() / 5;
    
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked" << std::endl;
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked" << std::endl;
    }
}

void MainComponent::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &volSlider)
    {
//        std::cout << "volSlider moved " << slider->getValue() << std::endl;
//        dphase = volSlider.getValue() * 0.001; // attach slider to sawtooth phaser
        dphase = volSlider.getValue() * 0.01; // attach slider to sine phaser
    }
}
