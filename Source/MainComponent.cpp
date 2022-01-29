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
        setAudioChannels (0, 2);
    }
    
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    
    volSlider.setRange(0.0, 1.0);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    /** Instantiate variables for generating sound output */
    phase = 0.0;
    dphase = 0.0001;
    
    /** Handle audio file reading */
    formatManager.registerBasicFormats();

    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    /** Generate sound output */
//    auto* leftChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
//    auto* rightChan = bufferToFill.buffer->getWritePointer(0, bufferToFill.startSample);
//    for (auto i=0; i < bufferToFill.numSamples; ++i)
//    {
////        double sample = rand.nextDouble() * 0.25; // white noise
////        double sample = fmod(phase, 0.2); // sawtooth wave
//        double sample = sin(phase) * 0.1; // sine wave
//        leftChan[i] = sample;
//        rightChan[i] = sample;
//
//        phase += dphase;
//    }
    
    /** Handle Audio File Input */
//    transportSource.getNextAudioBlock(bufferToFill);
    resampleSource.getNextAudioBlock(bufferToFill);

}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.
    
    transportSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
 
    double rowH = getHeight() / 5;
    
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    loadButton.setBounds(0, rowH * 4, getWidth(), rowH);
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked" << std::endl;
        transportSource.start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked" << std::endl;
        transportSource.stop();
    }
    if (button == &loadButton)
    {
        juce::FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
            loadURL(juce::URL{chooser.getResult()});
        }
    }
}

void MainComponent::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &volSlider)
    {
        transportSource.setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        resampleSource.setResamplingRatio(slider->getValue());
    }
}

void MainComponent::loadURL (juce::URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) //good file
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}
