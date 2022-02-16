/*
  ==============================================================================

    ParameterSlider.cpp
    Created: 15 Feb 2022 6:10:25pm
    Author:  User

  ==============================================================================
*/

#include "ParameterSlider.h"

ParameterSlider::ParameterSlider(juce::AudioProcessorParameter& p): Slider (p.getName(256)), param(p)
{
    setRange(0.0, 1.0, 0.0);
    startTimerHz(60);
    updateSliderPos();
}

ParameterSlider::~ParameterSlider()
{
}

void ParameterSlider::startedDragging()
{
    param.beginChangeGesture();
    isDragging = true;
}

void ParameterSlider::stoppedDragging()
{
    param.endChangeGesture(); 
    isDragging = false;
}

void ParameterSlider::timerCallback()
{
    updateSliderPos();
}

void ParameterSlider::updateSliderPos()
{
    const float newValue = param.getValue();

    if (newValue != (float)Slider::getValue()) {
        Slider::setValue(newValue);
    }
}

void ParameterSlider::valueChanged()
{
    if (isDragging) {
        param.setValueNotifyingHost((float)Slider::getValue());
    }
    else {
        param.setValue((float)Slider::getValue());
    }
}

double ParameterSlider::getValueFromText(const juce::String& text)
{
    return param.getValueForText(text);
}

juce::String ParameterSlider::getTextFromValue(double value)
{
    return param.getText((float)value, 1024);
}
