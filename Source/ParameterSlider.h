/*
  ==============================================================================

    ParameterSlider.h
    Created: 15 Feb 2022 6:10:25pm
    Author:  User

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once
class ParameterSlider : public juce::Slider, private juce::Timer {
public:
    ParameterSlider(juce::AudioProcessorParameter& p);
    ~ParameterSlider();
    void startedDragging() override;
    void stoppedDragging() override;
    void timerCallback() override;
    void updateSliderPos();
    void valueChanged() override;
    double getValueFromText(const juce::String& text) override;
    juce::String getTextFromValue(double value) override;
    juce::AudioProcessorParameter& param;
    bool isDragging = false;

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterSlider)
};