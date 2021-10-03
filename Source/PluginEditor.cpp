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
//    myAttachment = std::make_unique<RadioButtonAttachment>(audioProcessor.state.getParameter("CHANNEL"), Channels, "ChannelSelector", 42);
//    myAttachment = std::make_unique<RadioButtonAttachment>(audioProcessor.state.getParameter("CHANNEL"), Channels, "CHANNEL", 42, nullptr);
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
//
//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ((juce::String)audioProcessor.state.getRawParameterValue("CHANNEL")->load(), getLocalBounds(), juce::Justification::centred, 1);
//    std::cout << "PAINT: " << audioProcessor.state.getRawParameterValue("CHANNEL")->load() << std::endl;
//    int channelIdx = audioProcessor.state.getRawParameterValue("CHANNEL")->load() - 1;
//    g.drawFittedText ((juce::String)audioProcessor.state.getRawParameterValue("CHANNEL")->load(), getLocalBounds(), juce::Justification::centred, 1);
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
        b->setRadioGroupId(42);
        b->setClickingTogglesState(true);
//        b->setColour(juce::TextButton::buttonColourId, highlightColor);
        
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
//        attachments[i] = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.state, "CHANNEL", *b);
        
        channels->add(b);
    }
}
