/*
  ==============================================================================

    RadioButtonGroupAttachment.h
    Created: 3 Oct 2021 11:03:45am
    Author:  Stephane P. Pericat

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/*To implement a new attachment type, create a new class which includes an instance of this class as a data member. Your class should pass a function to the constructor of the ParameterAttachment, which will then be called on the message thread when the parameter changes. You can use this function to update the state of the UI control. Your class should also register as a listener of the UI control and respond to changes in the UI element by calling either setValueAsCompleteGesture or beginGesture, setValueAsPartOfGesture and endGesture.

Make sure to call sendInitialUpdate at the end of your new attachment's constructor, so that the UI immediately reflects the state of the parameter.*/

class RadioButtonGroupAttachment : public juce::Button::Listener
{
public:
    RadioButtonGroupAttachment (juce::AudioProcessorValueTreeState& s, juce::String parameterID, juce::OwnedArray<juce::TextButton>& b);
    ~RadioButtonGroupAttachment ();
private:
    void buttonClicked (juce::Button* b) override;
    void onValueChanged(float& v);

    juce::Array<juce::Component::SafePointer<juce::TextButton>> buttons;
    juce::ParameterAttachment attachment;
};
