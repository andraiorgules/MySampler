/*
  ==============================================================================

    myADSRComponent.h
    Created: 12 May 2022 5:10:56pm
    Author:  AndradaIorgulescu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class myADSRComponent  : public juce::Component
{
public:
    myADSRComponent(MySamplerAudioProcessor& p);
    ~myADSRComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Slider myAttackSlider, myDecaySlider, mySustainSlider, myReleaseSlider;
    juce::Label myAttackLabel, myDecayLabel, mySustainLabel, myReleaseLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> myAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> myDecayAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mySustainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> myReleaseAttachment;
    
    MySamplerAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (myADSRComponent)
};
