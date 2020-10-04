/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WozToneGeneratorAudioProcessorEditor::WozToneGeneratorAudioProcessorEditor (WozToneGeneratorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    toneFrequency.setSliderStyle (juce::Slider::LinearBarVertical);
    toneFrequency.setRange (20.0, 20000.0, 1.0);
    toneFrequency.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    toneFrequency.setPopupDisplayEnabled (true, false, this);
    toneFrequency.setTextValueSuffix (" hz");
    toneFrequency.setValue(1.0);
 
    // this function adds the slider to the editor
    addAndMakeVisible (&toneFrequency);
    
    // add the listener to the slider
    toneFrequency.addListener (this);
}

WozToneGeneratorAudioProcessorEditor::~WozToneGeneratorAudioProcessorEditor()
{
}

//==============================================================================
void WozToneGeneratorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Woz Tone Generator", getLocalBounds(), juce::Justification::centred, 1);
}

void WozToneGeneratorAudioProcessorEditor::resized()
{
    // sets the position and size of the slider with arguments (x, y, width, height)
    toneFrequency.setBounds (40, 30, 20, getHeight() - 60);
}

void WozToneGeneratorAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    audioProcessor.toneFrequency = toneFrequency.getValue();
    audioProcessor.updateAngleDelta();
}
