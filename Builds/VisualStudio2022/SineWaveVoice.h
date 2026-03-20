#pragma once

#include <JuceHeader.h>

struct SineWaveVoice : juce::SynthesiserVoice
{
	
	public:
		SineWaveVoice();
		bool canPlaySound(juce::SynthesiserSound* sound) override;
		void startNote(int midiNoteNumber, float veloity,
			juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;
		void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;
		void stopNote(float /*velocity*/, bool allowTailOff) override;
		void pitchWheelMoved(int) override {}
		void controllerMoved(int, int) override {}
		void PrepareToPlay(int samplesPerBlockExpected, double sampleRate, int numChannels);

	private:
		juce::dsp::ProcessSpec spec;
		juce::dsp::Oscillator<float> sineOsc{ [](float x) {return std::sin(x);}};
		juce::dsp::Gain<float> gain;
		juce::ADSR adsr;
		juce::ADSR::Parameters params;
		bool isPrepared = false;

	
};

