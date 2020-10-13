/*
  ==============================================================================

    ADSRComponent.h
    Created: 12 Oct 2020 11:36:26pm
    Author:  woz

  ==============================================================================
*/

#pragma once
#ifndef ADSR_COMPONENT_H
#define ADSR_COMPONENT_H

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PluginEditor.h"

typedef struct ADSRParams {
    float attack;
    float decay;
    float sustain;
    float release;
} ADSRParams;

class ADSRComponent : public juce::Component,
                      private juce::Slider::Listener
{
public:
    ADSRComponent();
    ~ADSRComponent();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void addParams(ADSRParams*);

private:
    void sliderValueChanged(juce::Slider* slider) override;
    
    juce::Slider attack;
    juce::Slider decay;
    juce::Slider sustain;
    juce::Slider release;
    
    ADSRParams* params;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};

#endif
