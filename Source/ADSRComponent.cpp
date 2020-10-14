/*
  ==============================================================================

    ADSRComponent.cpp
    Created: 12 Oct 2020 11:36:44pm
    Author:  woz

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ADSRComponent.h"

ADSRComponent::ADSRComponent()
{
    setSize (600, 300);
    
    // attack
    attack.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    attack.setRange (0.0, 10.0, 0.01);
    attack.setValue(0.0);
    attack.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 90, 30);
    attack.setPopupDisplayEnabled (false, false, this);
    attack.setTextValueSuffix (" sec");
    attack.setRotaryParameters(0, 2, true);
    addAndMakeVisible (&attack);
    attack.addListener (this);
    
    decay.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    decay.setRange (0.0, 10.0, 0.01);
    decay.setValue(1.0);
    decay.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 90, 30);
    decay.setPopupDisplayEnabled (false, false, this);
    decay.setTextValueSuffix (" sec");
    decay.setRotaryParameters(0, 2, true);
    addAndMakeVisible (&decay);
    decay.addListener (this);

    sustain.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    sustain.setRange (0.0, 10.0, 0.01);
    sustain.setValue(0.5);
    sustain.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 90, 30);
    sustain.setPopupDisplayEnabled (false, false, this);
    sustain.setTextValueSuffix (" sec");
    sustain.setRotaryParameters(0, 2, true);
    addAndMakeVisible (&sustain);
    sustain.addListener (this);

    release.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    release.setRange (0.0, 10.0, 0.01);
    release.setValue(0.5);
    release.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 90, 30);
    release.setPopupDisplayEnabled (false, false, this);
    release.setTextValueSuffix (" sec");
    release.setRotaryParameters(0, 2, true);
    addAndMakeVisible (&release);
    release.addListener (this);
}

ADSRComponent::~ADSRComponent()
{
}

void ADSRComponent::addParams(ADSRParams* adsrParams) {
    params = adsrParams;
}

void ADSRComponent::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
    attack.setColour(0x0001, juce::Colours::white);
    decay.setColour(0x0001, juce::Colours::white);
    sustain.setColour(0x0001, juce::Colours::white);
    release.setColour(0x0001, juce::Colours::white);
}

void ADSRComponent::resized()
{
    attack.setBounds (50, 50, 50, 50);
    decay.setBounds (125, 50, 50, 50);
    sustain.setBounds (200, 50, 50, 50);
    release.setBounds (275, 50, 50, 50);
}

void ADSRComponent::sliderValueChanged(juce::Slider* slider)
{
    params->attack = attack.getValue();
    params->decay = decay.getValue();
    params->sustain = sustain.getValue();
    params->release = release.getValue();
}
