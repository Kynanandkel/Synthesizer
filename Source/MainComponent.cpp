#include "MainComponent.h"


//==============================================================================
MainComponent::MainComponent() : keyboardComponent(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard),
synthAudioSource(keyboardState)
{
    //midi keyboard
    addAndMakeVisible(keyboardComponent);

    setSize (200, 200);
    setAudioChannels (0, 2);
   
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    synthAudioSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{ 
    synthAudioSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    synthAudioSource.releaseResources();
}


//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{}

void MainComponent::resized()
{
    keyboardComponent.setBounds(10, 40, getWidth() - 20, getHeight() - 50);
}

void MainComponent::timerCallback()
{
    keyboardComponent.grabKeyboardFocus();
    stopTimer();
}

