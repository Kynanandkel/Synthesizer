#include "synthAudioSource.h"
#include "sineWaveSound.h"
#include "sineWaveVoice.h"

synthAudioSource::synthAudioSource(juce::MidiKeyboardState& keyState) : keyboardState(keyState)
{
    for (auto i = 0; i < 4; ++i)
        synth.addVoice(new SineWaveVoice());
    synth.addSound(new SineWaveSound());
}

void synthAudioSource::setUsingSineWaveSound()
{
    synth.clearSounds();
}

void synthAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    midiCollector.reset(sampleRate);

    for (int i{}; i < synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SineWaveVoice*>(synth.getVoice(i)))
        {
            voice->PrepareToPlay(samplesPerBlockExpected, sampleRate, 2);
        }
        
    }
}

void synthAudioSource::releaseResources()
{
}

void synthAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    juce::MidiBuffer incomingMidi;
    midiCollector.removeNextBlockOfMessages(incomingMidi, bufferToFill.numSamples);
    keyboardState.processNextMidiBuffer(incomingMidi, bufferToFill.startSample, bufferToFill.numSamples, true);
    synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, bufferToFill.startSample, bufferToFill.numSamples);
}

juce::MidiMessageCollector* synthAudioSource::getMidiCollector()
{
    return &midiCollector;
}
