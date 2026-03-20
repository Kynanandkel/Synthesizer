#include "SineWaveVoice.h"
#include "SineWaveSound.h"

SineWaveVoice::SineWaveVoice(){}

void SineWaveVoice::PrepareToPlay(int samplesPerBlockExpected, double sampleRate, int numChannels) 
{

    adsr.setSampleRate(sampleRate);
    

    spec.numChannels = numChannels;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlockExpected;

    sineOsc.prepare(spec);
    gain.prepare(spec);
    //sineOsc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    sineOsc.setFrequency(220);
    gain.setGainLinear(0.1f);

    isPrepared = true;
}

bool SineWaveVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<SineWaveSound*> (sound) != nullptr;
}

void SineWaveVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int)
{
    
}

void SineWaveVoice::renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{

    jassert(isPrepared);


    juce::dsp::AudioBlock<float> block{ outputBuffer };
    sineOsc.process(juce::dsp::ProcessContextReplacing<float>(block));
    gain.process(juce::dsp::ProcessContextReplacing<float>(block));

    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}

void SineWaveVoice::stopNote(float, bool allowTailOff)
{
    
    clearCurrentNote();
    
}
