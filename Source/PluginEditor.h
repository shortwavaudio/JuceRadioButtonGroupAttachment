/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "include/RadioButtonGroupAttachment.h"

//==============================================================================
/**
*/
class RadioButtonGroupAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    RadioButtonGroupAudioProcessorEditor (RadioButtonGroupAudioProcessor&);
    ~RadioButtonGroupAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RadioButtonGroupAudioProcessor& audioProcessor;
    
    juce::StringArray channelLabels = {
        "clean",
        "crunch",
        "rhythm",
        "lead"
    };

    juce::OwnedArray<juce::TextButton> Channels;
    void createChannelSelector(juce::OwnedArray<juce::TextButton>*);

    std::unique_ptr<RadioButtonGroupAttachment> channelAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RadioButtonGroupAudioProcessorEditor)
};
