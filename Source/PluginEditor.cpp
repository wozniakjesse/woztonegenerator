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
    setSize (600, 300);
    
    // tone frequency slider
    toneFrequency.setSliderStyle (juce::Slider::LinearBar);
    toneFrequency.setRange (20.0, 20000.0, 1.0);
    toneFrequency.setValue(500.0);
    toneFrequency.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 90, 30);
    toneFrequency.setPopupDisplayEnabled (false, false, this);
    toneFrequency.setTextValueSuffix (" hz");
    
    // volume level slider
    volumeLevel.setSliderStyle (juce::Slider::LinearBar);
    volumeLevel.setRange (0.0, 100.0, 1.0);
    volumeLevel.setValue(12.5);
    volumeLevel.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 90, 30);
    volumeLevel.setPopupDisplayEnabled (false, false, this);
    volumeLevel.setTextValueSuffix (" %");
 
    // this function adds the slider to the editor
    addAndMakeVisible (&toneFrequency);
    addAndMakeVisible(&volumeLevel);
    
    // add the listener to the slider
    toneFrequency.addListener (this);
    volumeLevel.addListener(this);
    
    addAndMakeVisible(audioProcessor.keyboardComponent);
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
    g.drawFittedText ("Woz Tone Generator", getLocalBounds(), juce::Justification::centredTop, 1);
    
    if (!audioProcessor.keyboardComponent.hasKeyboardFocus(true) &&
        audioProcessor.keyboardComponent.isVisible()) {
            audioProcessor.keyboardComponent.grabKeyboardFocus();
    }
    
}

void WozToneGeneratorAudioProcessorEditor::resized()
{
    // sets the position and size of the slider with arguments (x, y, width, height)
    toneFrequency.setBounds (20, 80, getWidth() - 40, 20);
    volumeLevel.setBounds(20, 120, getWidth() - 40, 20);
    audioProcessor.keyboardComponent.setBounds (10, getHeight() / 2, getWidth() - 20, getHeight() / 2 - 10);
}

void WozToneGeneratorAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
    audioProcessor.toneFrequency = toneFrequency.getValue();
    audioProcessor.volumeLevel = volumeLevel.getValue() / 100;
    if (audioProcessor.currentSampleRate > 0.0)
        audioProcessor.updateAngleDelta();
}
