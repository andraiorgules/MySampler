/*
  ==============================================================================

    myADSRComponent.cpp
    Created: 12 May 2022 5:10:56pm
    Author:  AndradaIorgulescu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "myADSRComponent.h"

//==============================================================================
myADSRComponent::myADSRComponent(MySamplerAudioProcessor& p) : audioProcessor(p)
{
    //try different slider styles
    
    //ATTACK SLIDER
    myAttackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    myAttackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    myAttackSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    addAndMakeVisible(myAttackSlider);
    
    myAttackLabel.setFont(10.0f);
    myAttackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    myAttackLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::purple);
    myAttackLabel.setJustificationType(juce::Justification::centredTop);
    myAttackLabel.attachToComponent(&myAttackSlider, false);
    
    myAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "ATTACK", myAttackSlider);
   
    //DECAY SLIDER
    myDecaySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    myDecaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    myDecaySlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    addAndMakeVisible(myDecaySlider);
    
    myDecayLabel.setFont(10.0f);
    myDecayLabel.setText("Decay", juce::NotificationType::dontSendNotification);
    myDecayLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::purple);
    myDecayLabel.setJustificationType(juce::Justification::centredTop);
    myDecayLabel.attachToComponent(&myDecaySlider, false);
    
    myDecayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "DECAY", myDecaySlider);
    
    //SUSTAIN SLIDER
    mySustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    mySustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    mySustainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    addAndMakeVisible(mySustainSlider);
    
    mySustainLabel.setFont(10.0f);
    mySustainLabel.setText("Sustain", juce::NotificationType::dontSendNotification);
    mySustainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::purple);
    mySustainLabel.setJustificationType(juce::Justification::centredTop);
    mySustainLabel.attachToComponent(&mySustainSlider, false);
    
    mySustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "SUSTAIN", mySustainSlider);
    
    //RELEASE SLIDER
    myReleaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    myReleaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    myReleaseSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    addAndMakeVisible(myReleaseSlider);
    
    myReleaseLabel.setFont(10.0f);
    myReleaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
    myReleaseLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::purple);
    myReleaseLabel.setJustificationType(juce::Justification::centredTop);
    myReleaseLabel.attachToComponent(&myReleaseSlider, false);
    
    myReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.getAPVTS(), "RELEASE", myReleaseSlider);
}

myADSRComponent::~myADSRComponent()
{
}

void myADSRComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void myADSRComponent::resized()
{
    //affects the placement of the sliders
    const auto startX = 0.1f;
    const auto startY = 0.2f;
    const auto sliderWidth = 0.1f;
    const auto sliderHeight = 0.75f;
    
    myAttackSlider.setBoundsRelative(startX, startY, sliderWidth, sliderHeight);
    myDecaySlider.setBoundsRelative(startX + 0.25, startY, sliderWidth, sliderHeight);
    mySustainSlider.setBoundsRelative(startX + (0.25 * 2), startY, sliderWidth, sliderHeight);
    myReleaseSlider.setBoundsRelative(startX + (0.25 * 3), startY, sliderWidth, sliderHeight);
}
