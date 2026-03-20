#pragma once

#include <JuceHeader.h>
#include <SineWaveVoice.h>
#include <sineWaveSound.h>
#include <synthAudioSource.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::AudioAppComponent,
                       private juce::Timer,
                       private juce::AudioSource
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void setMidiInput(int index);
    

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    

private:
    void timerCallback() override;

    //==============================================================================
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;
    synthAudioSource synthAudioSource;


    juce::ComboBox midiInputList;
    juce::Label midiInputListLabel;
    int lastInputIndex = 0;
    juce::dsp::Oscillator<float> sineOsc{ [](float x) {return std::sin(x); } };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
