/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveformThumbnail.h"
#include "myADSRComponent.h"

//==============================================================================
/**
*/
class MySamplerAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                       public juce::Timer
{
public:
    MySamplerAudioProcessorEditor (MySamplerAudioProcessor&);
    ~MySamplerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;
    
private:
    juce::TextButton myLoadButton { "Load File" };
    
    WaveformThumbnail myWaveformThumbnail;
    
    myADSRComponent myADSR;
    
    MySamplerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MySamplerAudioProcessorEditor)
};
