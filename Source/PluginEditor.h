/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ParameterSlider.h"
#include "SplitWindow.h"
#include "colourPalette.h"


//==============================================================================
/**
*/
class SplitGrainsAudioProcessorEditor : public juce::AudioProcessorEditor,
    public juce::Slider::Listener,
    public juce::Timer
{
public:
    SplitGrainsAudioProcessorEditor (SplitGrainsAudioProcessor&);
    ~SplitGrainsAudioProcessorEditor() override;

    void timerCallback() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void showSplitWindow();

    void sliderValueChanged(juce::Slider* slider) override;

    void stemChanged();

    enum stemSelect {
        source,
        vocal,
        accompaniment,
        drums,
        bass,
        piano,
        other
    };
    juce::Slider intervalSlider;
    juce::Slider durationSlider;
    juce::Slider panningSlider;
    juce::Slider readposSlider;
    juce::Slider velocitySlider;
    juce::Slider directionSlider;

    juce::Slider intervalRandSlider;
    juce::Slider durationRandSlider;
    juce::Slider panningRandSlider;
    juce::Slider readposRandSlider;
    juce::Slider velocityRandSlider;
    juce::Slider directionRandSlider;

    juce::Label intervalLabel;
    juce::Label durationLabel;
    juce::Label panningLabel;
    juce::Label readposLabel;
    juce::Label velocityLabel;
    juce::Label randomLabel;
    juce::Label directionLabel;

    juce::Label activeGrainsLabel;

    juce::ComboBox stemSelect;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SplitGrainsAudioProcessor& audioProcessor;
    SplitWindow splitWindow;
    ColourPalette colourPalette;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SplitGrainsAudioProcessorEditor)
};
