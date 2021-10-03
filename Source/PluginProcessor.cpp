/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
RadioButtonGroupAudioProcessor::RadioButtonGroupAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), state(*this, nullptr, "parameters", createParams())
#endif
{
}

RadioButtonGroupAudioProcessor::~RadioButtonGroupAudioProcessor()
{
}

//==============================================================================
const juce::String RadioButtonGroupAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RadioButtonGroupAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RadioButtonGroupAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool RadioButtonGroupAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double RadioButtonGroupAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RadioButtonGroupAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RadioButtonGroupAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RadioButtonGroupAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String RadioButtonGroupAudioProcessor::getProgramName (int index)
{
    return {};
}

void RadioButtonGroupAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void RadioButtonGroupAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void RadioButtonGroupAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RadioButtonGroupAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void RadioButtonGroupAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//
//        // ..do something to the data...
//    }
    std::cout << "CHANNEL: " << getChannelId() << std::endl;
}

//==============================================================================
bool RadioButtonGroupAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* RadioButtonGroupAudioProcessor::createEditor()
{
    return new RadioButtonGroupAudioProcessorEditor (*this);
//    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void RadioButtonGroupAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // Store an xml representation of our state.
    if (auto xmlState = state.copyState().createXml())
        copyXmlToBinary(*xmlState, destData);
}

void RadioButtonGroupAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Restore our plug-in's state from the xml representation stored in the above method.
    if (auto xmlState = getXmlFromBinary(data, sizeInBytes))
        state.replaceState(juce::ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RadioButtonGroupAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout RadioButtonGroupAudioProcessor::createParams()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    juce::StringArray channelLabels = {
        "clean",
        "crunch",
        "rhythm",
        "lead"
    };
    
//    layout.add(std::make_unique<juce::AudioParameterChoice>("CHANNEL", "Channel", channelLabels, 1));
    
//    layout.add(std::make_unique<juce::AudioParameterInt>("CAB", "Cab", 1, 2, 1));
    layout.add(std::make_unique<juce::AudioParameterInt>("CHANNEL", "Channel", 1, 4, 1));
    
    return layout;
}

int RadioButtonGroupAudioProcessor::getChannelId()
{
    return state.getRawParameterValue("CHANNEL")->load();
}
