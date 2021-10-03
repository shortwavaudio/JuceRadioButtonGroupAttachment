/*
  ==============================================================================

    RadioButtonGroupAttachment.cpp
    Created: 3 Oct 2021 11:03:45am
    Author:  Stephane P. Pericat

  ==============================================================================
*/

#include "RadioButtonGroupAttachment.h"

RadioButtonGroupAttachment::RadioButtonGroupAttachment(juce::AudioProcessorValueTreeState& s, juce::String parameterID, juce::OwnedArray<juce::TextButton>& b) : attachment(*s.getParameter(parameterID), [this] (float newValue) { onValueChanged(newValue); })
{
    int defaultSelection = s.getRawParameterValue(parameterID)->load();
    
    for(int i = 0; i < b.size(); ++i)
    {
        juce::TextButton* button = b.getUnchecked (i);
        button->addListener(this);
        
        if(defaultSelection == i)
            button->setToggleState(true, juce::dontSendNotification);
        
        buttons.add(button);
    }
    
    attachment.sendInitialUpdate();
}

RadioButtonGroupAttachment::~RadioButtonGroupAttachment()
{
    for(int i = 0; i < buttons.size(); ++i)
    {
        juce::TextButton* button = buttons.getUnchecked (i);
        button->removeListener(this);
    }
}

void RadioButtonGroupAttachment::buttonClicked(juce::Button *b)
{
    for (int i= 0; i< buttons.size(); i++) {
        if (b == buttons.getUnchecked(i) && b->getToggleState()) {
            attachment.setValueAsCompleteGesture(i);
        }
    }
}

void RadioButtonGroupAttachment::onValueChanged(float &v)
{
}
