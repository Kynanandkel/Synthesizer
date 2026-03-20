#pragma once

#include <JuceHeader.h>

struct SineWaveSound : public juce::SynthesiserSound
{
	SineWaveSound();
	bool appliesToNote(int) override;
	bool appliesToChannel(int) override;
};

