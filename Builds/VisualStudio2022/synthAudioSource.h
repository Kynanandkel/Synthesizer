#pragma once

#include <JuceHeader.h>


class synthAudioSource : public juce::AudioSource
{

public:
	synthAudioSource(juce::MidiKeyboardState& keyState);
	void setUsingSineWaveSound();
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void releaseResources() override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	juce::MidiMessageCollector* synthAudioSource::getMidiCollector();
private:
	juce::MidiKeyboardState& keyboardState;
	juce::Synthesiser synth;
	juce::MidiMessageCollector midiCollector;

};

