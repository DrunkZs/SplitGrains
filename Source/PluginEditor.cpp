/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SplitGrainsAudioProcessorEditor::SplitGrainsAudioProcessorEditor(SplitGrainsAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), splitWindow(p)
{   
    //Opens window for user to split stems
    showSplitWindow();

    //Shows the ui for the granulation
    
    //Position
    positionSlider = new ParameterSlider(*p.positionParam);
    addAndMakeVisible(positionSlider);
    positionSlider->setSliderStyle(juce::Slider::LinearBar);
    positionSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);

    randPosLabel.setText("rP", juce::dontSendNotification);
    addAndMakeVisible(randPosLabel);

    randPosSlider = new ParameterSlider(*p.randPosParam);
    addAndMakeVisible(randPosSlider);
    randPosSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    randPosSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);

    // Duration
    addAndMakeVisible(durationLabel);
    durationLabel.setText("Duration", juce::dontSendNotification);

    addAndMakeVisible(durationSlider = new ParameterSlider(*p.durationParam));
    durationSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    durationSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);


    addAndMakeVisible(randDurSlider = new ParameterSlider(*p.randDurParam));
    randDurSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    randDurSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);

    // Density
    addAndMakeVisible(densityLabel);
    densityLabel.setText("Density", juce::dontSendNotification);

    addAndMakeVisible(densitySlider = new ParameterSlider(*p.densityParam));
    densitySlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    densitySlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);

    addAndMakeVisible(randDenSlider = new ParameterSlider(*p.randDensityParam));
    randDenSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    randDenSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);

    // Transposition
    addAndMakeVisible(transLabel);
    transLabel.setText("Transpose", juce::dontSendNotification);

    addAndMakeVisible(transSlider = new ParameterSlider(*p.transParam));
    transSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    transSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);

    addAndMakeVisible(randTransSlider = new ParameterSlider(*p.randTransParam));
    randTransSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    randTransSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);

    // Volume
    addAndMakeVisible(volLabel);
    volLabel.setText("Volume", juce::dontSendNotification);

    addAndMakeVisible(volSlider = new ParameterSlider(*p.volumeParam));
    volSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    volSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);

    addAndMakeVisible(randVolSlider = new ParameterSlider(*p.randVolumeParam));
    randVolSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    randVolSlider->setTextBoxStyle(juce::Slider::NoTextBox, false, 80, 20);

    // Envelope
    addAndMakeVisible(envLabel);
    envLabel.setText("Envelope", juce::dontSendNotification);

    addAndMakeVisible(envMidLabel);
    envMidLabel.setText("Mid", juce::dontSendNotification);

    addAndMakeVisible(envMidSlider = new ParameterSlider(*p.envMidParam));
    envMidSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    envMidSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);

    addAndMakeVisible(envSusLabel);
    envSusLabel.setText("Sustain", juce::dontSendNotification);

    addAndMakeVisible(envSusSlider = new ParameterSlider(*p.envSustainParam));
    envSusSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    envSusSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);

    addAndMakeVisible(envCurveLabel);
    envCurveLabel.setText("Curve", juce::dontSendNotification);

    addAndMakeVisible(envCurveSlider = new ParameterSlider(*p.envCurveParam));
    envCurveSlider->setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    envCurveSlider->setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);

    setSize (500, 400);
}

SplitGrainsAudioProcessorEditor::~SplitGrainsAudioProcessorEditor()
{
    //stopThread(4000);
}

//==============================================================================
void SplitGrainsAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (colourPalette.getSpaceCadet());
    
}

void SplitGrainsAudioProcessorEditor::resized()
{
    const int width = getWidth();

    // Position:
    positionSlider->setBounds(10, 40, width - 50, 20);

    randPosLabel.setBounds(width - 30, 20, 25, 20);
    randPosSlider->setBounds(width - 30, 37, 25, 25);

    // Duration:
    durationLabel.setBounds(10, 70, 50, 20);
    durationSlider->setBounds(10, 90, 50, 65);

    randDurSlider->setBounds(15, 160, 40, 40);

    // Density:
    densityLabel.setBounds(70, 70, 70, 20);
    densitySlider->setBounds(70, 90, 50, 65);

    randDenSlider->setBounds(75, 160, 40, 40);

    // Transposition
    transLabel.setBounds(130, 70, 70, 20);
    transSlider->setBounds(130, 90, 50, 65);

    randTransSlider->setBounds(135, 160, 40, 40);

    // Volume
    volLabel.setBounds(190, 70, 70, 20);
    volSlider->setBounds(190, 90, 50, 65);

    randVolSlider->setBounds(195, 160, 40, 40);

    // Envelope
    envLabel.setBounds(320, 70, 70, 20);

    envMidLabel.setBounds(320, 85, 70, 20);
    envMidSlider->setBounds(320, 105, 50, 65);

    envSusLabel.setBounds(380, 85, 70, 20);
    envSusSlider->setBounds(380, 105, 50, 65);

    envCurveLabel.setBounds(440, 85, 70, 20);
    envCurveSlider->setBounds(440, 105, 50, 65);
}


void SplitGrainsAudioProcessorEditor::showSplitWindow() {
    auto* splitWindow = new SplitWindow(audioProcessor);
    //windows.add(splitWindow);

    splitWindow->setBounds(0,0,400,400);
    splitWindow->setSize(400,400);
    splitWindow->setUsingNativeTitleBar(true);
    splitWindow->setAlwaysOnTop(true);
    splitWindow->setDropShadowEnabled(true);
    splitWindow->setVisible(true);
}

void SplitGrainsAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{

}
