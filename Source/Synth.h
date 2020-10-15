/*
  ==============================================================================

    Synth.h
    Created: 13 Oct 2020 7:00:43pm
    Author:  woz

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================
struct SineWaveSound   : public juce::SynthesiserSound
{
    SineWaveSound() {}

    bool appliesToNote    (int) override        { return true; }
    bool appliesToChannel (int) override        { return true; }
};

//==============================================================================
struct SineWaveVoice   : public juce::SynthesiserVoice
{
    SineWaveVoice()
    {
        adsr.setSampleRate(getSampleRate());
        juce::ADSR::Parameters adsrParams = {0.5, 1.0, 1.0, 0.5};
        adsr.setParameters(adsrParams);
        
    }

    bool canPlaySound (juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<SineWaveSound*> (sound) != nullptr;
    }

    void startNote (int midiNoteNumber, float velocity,
                    juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override
    {
        adsr.noteOn();
        currentAngle = 0.0;
        level = velocity * 0.15;

        auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
        auto cyclesPerSample = cyclesPerSecond / getSampleRate();

        angleDelta = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
    }

    void stopNote (float /*velocity*/, bool allowTailOff) override
    {
        adsr.noteOff();
    }

    void pitchWheelMoved (int) override      {}
    void controllerMoved (int, int) override {}

    void renderNextBlock (juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override
    {
        if (angleDelta != 0.0)
        {

                while (--numSamples >= 0)
                {
                    auto currentSample = (float) (std::sin (currentAngle) * level * adsr.getNextSample());

                    for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                        outputBuffer.addSample (i, startSample, currentSample);

                    currentAngle += angleDelta;
                    ++startSample;
                    
                    if (!adsr.isActive()) {
                        clearCurrentNote();
                        adsr.reset();
                        angleDelta = 0.0;
                        break;
                    }

                }
        }
    }

private:
    double currentAngle = 0.0, angleDelta = 0.0, level = 0.0;
    juce::ADSR adsr;
};

//==============================================================================
class SynthAudioSource   : public juce::AudioSource
{
public:
    SynthAudioSource (juce::MidiKeyboardState& keyState)
        : keyboardState (keyState)
    {
        for (auto i = 0; i < 64; ++i)                // [1]
            synth.addVoice (new SineWaveVoice());

        synth.addSound (new SineWaveSound());       // [2]
    }

    void setUsingSineWaveSound()
    {
        synth.clearSounds();
    }

    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        synth.setCurrentPlaybackSampleRate (sampleRate); // [3]
    }

    void releaseResources() override {}

    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        bufferToFill.clearActiveBufferRegion();

        synth.renderNextBlock (*bufferToFill.buffer, *midiBuffer,
                               bufferToFill.startSample, bufferToFill.numSamples); // [5]
    }
    
    void setMidiBuffer(juce::MidiBuffer* buffer)
    {
        midiBuffer = buffer;
    }

private:
    juce::MidiBuffer* midiBuffer;
    juce::MidiKeyboardState& keyboardState;
    juce::Synthesiser synth;
};
