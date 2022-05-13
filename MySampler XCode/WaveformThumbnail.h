/*
  ==============================================================================

    WaveformThumbnail.h
    Created: 12 May 2022 4:10:41pm
    Author:  AndradaIorgulescu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class WaveformThumbnail  : public juce::Component,
                           public juce::FileDragAndDropTarget
{
public:
    WaveformThumbnail(MySamplerAudioProcessor& p);
    ~WaveformThumbnail() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    bool isInterestedInFileDrag(const juce::StringArray& files) override;
    void filesDropped (const juce::StringArray& files, int x, int y) override;

private:
    
    std::vector<float> myAudioPoints;
    
    bool myShouldBePainting {false};
    
    juce::String myFileName { "" };
    
    MySamplerAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformThumbnail)
};
