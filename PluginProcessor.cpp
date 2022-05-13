/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MySamplerAudioProcessor::MySamplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), myAPVTS(*this, nullptr, "Parameters", createParameters())
#endif
{
    myFormatManager.registerBasicFormats();
    myAPVTS.state.addListener(this);
    
    for (int i = 0; i < myNumVoices; i++ )
    {
        mySampler.addVoice(new juce::SamplerVoice());
    }
}

MySamplerAudioProcessor::~MySamplerAudioProcessor()
{
    myFormatReader = nullptr;
}

//==============================================================================
const juce::String MySamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MySamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MySamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MySamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MySamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MySamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MySamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MySamplerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MySamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void MySamplerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MySamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mySampler.setCurrentPlaybackSampleRate(sampleRate);
    updateADSR();
}

void MySamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MySamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MySamplerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    if (myShouldUpdate)
    {
        updateADSR();
    }

    juce::MidiMessage my;
    juce::MidiBuffer::Iterator it { midiMessages };
    int sample;
    
    while (it.getNextEvent(my, sample))
    {
        if (my.isNoteOn())
        {
            myIsNotePlayed = true;
        }
        else if (my.isNoteOff())
        {
            myIsNotePlayed = false;
        }
    }
    
    mySampleCount = myIsNotePlayed ? mySampleCount += buffer.getNumSamples() : 0;
    
    mySampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool MySamplerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MySamplerAudioProcessor::createEditor()
{
    return new MySamplerAudioProcessorEditor (*this);
}

//==============================================================================
void MySamplerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MySamplerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void MySamplerAudioProcessor::loadFile()
{
    mySampler.clearSounds();
    
    juce::FileChooser chooser { "Please load a file" };
    
    if (chooser.browseForFileToOpen())
    {
        auto file = chooser.getResult();
        myFormatReader = myFormatManager.createReaderFor(file);
    }
    
    juce::BigInteger  range;
    range.setRange(0, 128, true);
    
    mySampler.addSound (new juce::SamplerSound ("Sample", *myFormatReader, range, 60, 0.1, 0.1, 10));

    updateADSR();
}

void MySamplerAudioProcessor::loadFile(const juce::String& path)
{
    mySampler.clearSounds();
    
    auto file = juce::File (path);
    myFormatReader = myFormatManager.createReaderFor(file);
    
    auto sampleLength = static_cast<int>(myFormatReader->lengthInSamples);
    
    myWaveForm.setSize(1, sampleLength);
    myFormatReader->read(&myWaveForm, 0, sampleLength, 0, true, false);
    
    juce::BigInteger  range;
    range.setRange(0, 128, true);
    
    mySampler.addSound (new juce::SamplerSound ("Sample", *myFormatReader, range, 60, 0.1, 0.1, 10));
}

void MySamplerAudioProcessor::updateADSR()
{
    myADSRParams.attack = myAPVTS.getRawParameterValue("ATTACK")->load();
    myADSRParams.decay = myAPVTS.getRawParameterValue("DECAY")->load();
    myADSRParams.sustain = myAPVTS.getRawParameterValue("SUSTAIN")->load();
    myADSRParams.release = myAPVTS.getRawParameterValue("RELEASE")->load();
    
    for (int i = 0; i < mySampler.getNumSounds(); ++i)
    {
        if (auto sound = dynamic_cast<juce::SamplerSound*>(mySampler.getSound(i).get()))
        {
            sound->setEnvelopeParameters(myADSRParams);
        }
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout MySamplerAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", 0.0f, 5.0f, 0.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", 0.0f, 3.0f, 2.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f));
    parameters.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", 0.0f, 5.0f, 2.0f));
    
    return { parameters.begin(), parameters.end() };
}

void MySamplerAudioProcessor::valueTreePropertyChanged(juce::ValueTree& treeWhosePropertyHasChanged, const juce::Identifier& property)
{
    myShouldUpdate = true;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MySamplerAudioProcessor();
}
