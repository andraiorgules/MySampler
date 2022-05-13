/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MySamplerAudioProcessorEditor::MySamplerAudioProcessorEditor (MySamplerAudioProcessor& p)
    : AudioProcessorEditor (&p), myWaveformThumbnail(p), myADSR (p), audioProcessor (p)
{
    //myLoadButton.onClick = [&]() { audioProcessor.loadFile(); };
    //addAndMakeVisible(myLoadButton);
    
    addAndMakeVisible(myWaveformThumbnail);
    
    addAndMakeVisible(myADSR);
    
    startTimerHz(30);
    
    setSize (600, 400);
}

MySamplerAudioProcessorEditor::~MySamplerAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void MySamplerAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
}

void MySamplerAudioProcessorEditor::resized()
{
    //this sets the placement of the waveform: x, y, width, height
    myWaveformThumbnail.setBoundsRelative(0.0f, 0.25f, 1.0f, 0.5f);
    
    myADSR.setBoundsRelative(0.0f, 0.75f, 1.0f, 0.25f);

    myLoadButton.setBounds(getWidth() / 2 - 120, getHeight() / 2 - 130, 250, 20);
}

void MySamplerAudioProcessorEditor::timerCallback()
{
    repaint();
}
