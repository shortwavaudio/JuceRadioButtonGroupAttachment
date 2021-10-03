/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//#include "ff_gui_attachments.h"
#include "RadioButtonGroupAttachment.h"

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
    
//    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachments[4];
//    std::unique_ptr<RadioButtonAttachment> myAttachment;
    std::unique_ptr<RadioButtonGroupAttachment> channelAttachment;
    
//    juce::Label channelLbl;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RadioButtonGroupAudioProcessorEditor)
};
