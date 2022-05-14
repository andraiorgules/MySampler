/*
  ==============================================================================

    WaveformThumbnail.cpp
    Created: 12 May 2022 4:10:41pm
    Author:  AndradaIorgulescu

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformThumbnail.h"

//==============================================================================
WaveformThumbnail::WaveformThumbnail(MySamplerAudioProcessor& p) : audioProcessor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

WaveformThumbnail::~WaveformThumbnail()
{
}

void WaveformThumbnail::paint (juce::Graphics& g)
{
    
    auto waveform = audioProcessor.getWaveForm();
  
     if (waveform.getNumSamples() > 0)
    {
        //darker function just makes the color darker//not necessary 
        g.fillAll(juce::Colours::purple.darker());
        
        juce::Path p;
        myAudioPoints.clear();
        
        
        auto ratio = waveform.getNumSamples() / getWidth();
        auto buffer = waveform.getReadPointer(0);
            
        for (int sample = 0; sample < waveform.getNumSamples(); sample+=ratio)
        {
            myAudioPoints.push_back(buffer[sample]);
        }
            
        g.setColour(juce::Colours::white);
        
        p.startNewSubPath(0, getHeight() / 2);
            
        for (int sample = 0; sample < myAudioPoints.size(); ++sample)
        {
            auto point = juce::jmap<float>(myAudioPoints[sample], -1.0f, 1.0f, getHeight(), 0);
            p.lineTo(sample, point);
        }
            
        g.strokePath(p, juce::PathStrokeType(2));
        
        //change color and font size of wav file name display
        g.setColour(juce::Colours::white);
        g.setFont(15.0f);
        
        auto textBounds = getLocalBounds().reduced(10, 10);
        
        g.drawFittedText(myFileName, textBounds, juce::Justification::topRight, 1);
        
        auto playHeadPosition = juce::jmap<int> (audioProcessor.getSampleCount(), 0, audioProcessor.getWaveForm().getNumSamples(), 0, getWidth());
        
        g.setColour(juce::Colours::white);
        g.drawLine(playHeadPosition, 0, playHeadPosition, getHeight(), 2.0f);
        
        g.setColour(juce::Colours::black.withAlpha (0.2f));
        g.fillRect(0, 0, playHeadPosition, getHeight());
    }
    else
    {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::white);
        g.setFont (40.0f);
        g.drawFittedText("Drag and Drop an Audio File", getLocalBounds(), juce::Justification::centred, 1);
    }
}

void WaveformThumbnail::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

bool WaveformThumbnail::isInterestedInFileDrag (const juce::StringArray& files)
{
    for (auto file : files)
    {
        if (file.contains (".wav") || file.contains (".mp3") || file.contains (".aif") )
        {
            return true;
        }
    }
    
    return false;
}

void WaveformThumbnail::filesDropped (const juce::StringArray& files, int x, int y)
{
    for (auto file : files)
    {
        if (isInterestedInFileDrag(file))
        {
            auto myFile = std::make_unique<juce::File>(file);
            myFileName = myFile->getFileNameWithoutExtension();
            
            audioProcessor.loadFile(file);
        }
    }
    
    repaint();
}
