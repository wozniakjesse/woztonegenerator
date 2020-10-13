/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WozToneGeneratorAudioProcessor::WozToneGeneratorAudioProcessor()
     : AudioProcessor (BusesProperties().withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
       synthAudioSource(keyboardState),
       keyboardComponent (keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
}

WozToneGeneratorAudioProcessor::~WozToneGeneratorAudioProcessor()
{
}

//==============================================================================
const juce::String WozToneGeneratorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WozToneGeneratorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WozToneGeneratorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WozToneGeneratorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WozToneGeneratorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WozToneGeneratorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WozToneGeneratorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WozToneGeneratorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String WozToneGeneratorAudioProcessor::getProgramName (int index)
{
    return {};
}

void WozToneGeneratorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void WozToneGeneratorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synthAudioSource.prepareToPlay(samplesPerBlock, sampleRate);
}

void WozToneGeneratorAudioProcessor::releaseResources()
{
    keyboardState.reset();
    synthAudioSource.releaseResources();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WozToneGeneratorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void WozToneGeneratorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    return;
}

//==============================================================================
bool WozToneGeneratorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* WozToneGeneratorAudioProcessor::createEditor()
{
    return new WozToneGeneratorAudioProcessorEditor (*this);
}

//==============================================================================
void WozToneGeneratorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WozToneGeneratorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::MidiKeyboardComponent* WozToneGeneratorAudioProcessor::getKeyboard()
{
    return &keyboardComponent;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WozToneGeneratorAudioProcessor();
}
