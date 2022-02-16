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
class SplitGrainsAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                         public juce::Slider::Listener
{
public:
    SplitGrainsAudioProcessorEditor (SplitGrainsAudioProcessor&);
    ~SplitGrainsAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //void run() override;
    //void checkForPathToOpen();
    //void checkForBuffersToFree();
    void showSplitWindow();

    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SplitGrainsAudioProcessor& audioProcessor;
    SplitWindow splitWindow;
    ColourPalette colourPalette;

    juce::ScopedPointer<ParameterSlider> positionSlider;
    juce::ScopedPointer<ParameterSlider> randPosSlider;
    juce::Label randPosLabel;
    //  Duration
    juce::Label durationLabel;
    juce::ScopedPointer<ParameterSlider> durationSlider;
    juce::ScopedPointer<ParameterSlider> randDurSlider;

    // Density:
    juce::Label densityLabel;
    juce::ScopedPointer<ParameterSlider> densitySlider;
    juce::ScopedPointer<ParameterSlider> randDenSlider;

    // Transposition:
    juce::Label transLabel;
    juce::ScopedPointer<ParameterSlider> transSlider;
    juce::ScopedPointer<ParameterSlider> randTransSlider;

    // Volume:
    juce::Label volLabel;
    juce::ScopedPointer<ParameterSlider> volSlider;
    juce::ScopedPointer<ParameterSlider> randVolSlider;

    // Envelope:
    juce::Label envLabel;
    juce::Label envMidLabel;
    juce::ScopedPointer<ParameterSlider> envMidSlider;

    juce::Label envSusLabel;
    juce::ScopedPointer<ParameterSlider> envSusSlider;

    juce::Label envCurveLabel;
    juce::ScopedPointer<ParameterSlider> envCurveSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SplitGrainsAudioProcessorEditor)
};
