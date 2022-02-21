/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 30 Jan 2022 6:16:37pm
    Author:  Sean Marjason

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager
                             ) : formatManager(_formatManager)
{
    
}

DJAudioPlayer::~DJAudioPlayer(){
    
}

void DJAudioPlayer::prepareToPlay (int samplesPerBlockExpected, double sampleRate) {
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) {
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources() {
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(juce::URL audioURL) {
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) //good file
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

void DJAudioPlayer::setGain(double gain) {
    if (gain < 0.1 || gain > 2.0) {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 2" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio) {
    if (ratio < 0.1 || ratio > 2.0) {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 10" << std::endl;
    }
    else {
        double rate = ratio; // TODO: scale rate to have greater influence on speed
        resampleSource.setResamplingRatio(rate);
    }
}

void DJAudioPlayer::setPosition(double posInSecs) {
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos) {
    if (pos < 0.0 || pos > 1.0) {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }
    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

void DJAudioPlayer::start() {
    transportSource.start();
}

void DJAudioPlayer::stop() {
    transportSource.stop();
}

double DJAudioPlayer::getPositionRelative(){
    if (transportSource.getCurrentPosition() == 0) {
        return 0;
    }
    else {
        return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
    }
}

double DJAudioPlayer::getCurrentPosition(){
    return transportSource.getCurrentPosition();
}

void DJAudioPlayer::startAudioLoop(double startPos, double endPos) {
    transportSource.setPosition(startPos);
}
