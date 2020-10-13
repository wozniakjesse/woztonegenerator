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
    attack.setSliderStyle (juce::Slider::LinearBar);
    attack.setRange (20.0, 20000.0, 1.0);
    attack.setValue(500.0);
    attack.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 90, 30);
    attack.setPopupDisplayEnabled (false, false, this);
    attack.setTextValueSuffix (" hz");
    addAndMakeVisible (&attack);
    attack.addListener (this);
    
    decay.setSliderStyle (juce::Slider::LinearBar);
    decay.setRange (20.0, 20000.0, 1.0);
    decay.setValue(500.0);
    decay.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 90, 30);
    decay.setPopupDisplayEnabled (false, false, this);
    decay.setTextValueSuffix (" hz");
    addAndMakeVisible (&decay);
    decay.addListener (this);

    sustain.setSliderStyle (juce::Slider::LinearBar);
    sustain.setRange (20.0, 20000.0, 1.0);
    sustain.setValue(500.0);
    sustain.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 90, 30);
    sustain.setPopupDisplayEnabled (false, false, this);
    sustain.setTextValueSuffix (" hz");
    addAndMakeVisible (&sustain);
    sustain.addListener (this);

    release.setSliderStyle (juce::Slider::LinearBar);
    release.setRange (20.0, 20000.0, 1.0);
    release.setValue(500.0);
    release.setTextBoxStyle (juce::Slider::TextBoxAbove, false, 90, 30);
    release.setPopupDisplayEnabled (false, false, this);
    release.setTextValueSuffix (" hz");
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
}

void ADSRComponent::resized()
{
    attack.setBounds (20, 30, getWidth() - 40, 20);
    decay.setBounds (20, 60, getWidth() - 40, 20);
    sustain.setBounds (20, 90, getWidth() - 40, 20);
    release.setBounds (20, 120, getWidth() - 40, 20);
}

void ADSRComponent::sliderValueChanged(juce::Slider* slider)
{
    params->attack = attack.getValue();
    params->decay = decay.getValue();
    params->sustain = sustain.getValue();
    params->release = release.getValue();
}
