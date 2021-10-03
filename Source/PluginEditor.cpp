/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
//#include "RadioButtonGroupAttachment.h"

//==============================================================================
RadioButtonGroupAudioProcessorEditor::RadioButtonGroupAudioProcessorEditor (RadioButtonGroupAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    createChannelSelector(&Channels);
    channelAttachment = std::make_unique<RadioButtonGroupAttachment>(audioProcessor.state, "CHANNEL", Channels);

    setSize (640, 480);
}

RadioButtonGroupAudioProcessorEditor::~RadioButtonGroupAudioProcessorEditor()
{
}

//==============================================================================
void RadioButtonGroupAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void RadioButtonGroupAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto row = getLocalBounds().reduced(10, 40).removeFromTop(35);
    for(auto* b : Channels)
    {
        b->setBounds(row.removeFromLeft((getWidth() - 20) / 4));
    }
}

void RadioButtonGroupAudioProcessorEditor::createChannelSelector(juce::OwnedArray<juce::TextButton>* channels)
{
    for(int i = 0; i < 4; ++i) {
        juce::TextButton* b = new juce::TextButton();
        
        
        b->setButtonText(channelLabels[i]);
        b->setRadioGroupId(1);
        b->setClickingTogglesState(true);
        
        switch (i) {
            case 0:
                b->setConnectedEdges(juce::Button::ConnectedOnRight);
                break;
            case 1:
            case 2:
                b->setConnectedEdges(juce::Button::ConnectedOnRight + juce::Button::ConnectedOnLeft);
                break;
            case 3:
                b->setConnectedEdges(juce::Button::ConnectedOnLeft);
                break;

            default:
                break;
        }
        
        if(i == 0)
        {
            b->setToggleState(true, juce::dontSendNotification);
        }
        
        addAndMakeVisible(b);
        
        channels->add(b);
    }
}
