/*
  ==============================================================================

    RadioButtonGroupAttachment.h
    Created: 3 Oct 2021 11:03:45am
    Author:  Stephane P. Pericat

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class RadioButtonGroupAttachment : public juce::Button::Listener
{
public:
    RadioButtonGroupAttachment (juce::AudioProcessorValueTreeState& s, juce::String parameterID, juce::OwnedArray<juce::TextButton>& b)  : attachment(*s.getParameter(parameterID), [this] (float newValue) { onValueChanged(newValue); })
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

    ~RadioButtonGroupAttachment ()
    {
        for(int i = 0; i < buttons.size(); ++i)
        {
            juce::TextButton* button = buttons.getUnchecked (i);
            button->removeListener(this);
        }
    }
private:
    void buttonClicked (juce::Button* b) override
    {
        for (int i= 0; i< buttons.size(); i++) {
            if (b == buttons.getUnchecked(i) && b->getToggleState()) {
                attachment.setValueAsCompleteGesture(i);
            }
        }
    }

    void onValueChanged(float& v)
    {
    }

    juce::Array<juce::Component::SafePointer<juce::TextButton>> buttons;
    juce::ParameterAttachment attachment;
};
