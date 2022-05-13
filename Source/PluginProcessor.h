/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class MySamplerAudioProcessor  : public juce::AudioProcessor,
                                 public juce::ValueTree::Listener
{
public:
    //==============================================================================
    MySamplerAudioProcessor();
    ~MySamplerAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void loadFile();
    void loadFile (const juce::String& path);

    int getNumSamplerSounds() { return mySampler.getNumSounds(); }
    juce::AudioBuffer<float>& getWaveForm() { return myWaveForm; }
    
    void updateADSR();
    
    juce::ADSR::Parameters& getADSRParams() { return myADSRParams; }
    juce::AudioProcessorValueTreeState& getAPVTS() { return myAPVTS; }
    
    std::atomic<bool>& isNotePlayed() { return myIsNotePlayed; }
    std::atomic<int>& getSampleCount() { return mySampleCount; }
    
private:
    juce::Synthesiser mySampler;
    const int myNumVoices { 3 };
    juce::AudioBuffer<float> myWaveForm;
    
    juce::ADSR::Parameters myADSRParams;
    
    juce::AudioFormatManager myFormatManager;
    juce::AudioFormatReader* myFormatReader { nullptr };
    
    juce::AudioProcessorValueTreeState myAPVTS;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
    void valueTreePropertyChanged (juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property) override;
    
    std::atomic<bool> myShouldUpdate { false };
    std::atomic<bool> myIsNotePlayed { false };
    std::atomic<int> mySampleCount { 0 };
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MySamplerAudioProcessor)
};
