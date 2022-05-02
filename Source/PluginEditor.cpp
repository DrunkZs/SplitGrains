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
    , intervalSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , durationSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , panningSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , readposSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , velocitySlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , directionSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)

    , intervalRandSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , durationRandSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , panningRandSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , readposRandSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , velocityRandSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
    , directionRandSlider(juce::Slider::SliderStyle::RotaryVerticalDrag, juce::Slider::TextEntryBoxPosition::TextBoxBelow)
{   
    //Opens window for user to split stems
    showSplitWindow();

    startTimerHz(60);
    
    addAndMakeVisible(intervalSlider);
    intervalSlider.setRange(0.1, 5000);
    intervalSlider.setSkewFactorFromMidPoint(1);
    intervalSlider.onValueChange = [this] {
        audioProcessor.grainEngine.intervalParam.centre = (float)intervalSlider.getValue();
        const float interval = audioProcessor.grainEngine.intervalParam.get();
        audioProcessor.grainEngine.timer.interval = puro::math::round(audioProcessor.grainEngine.durationParam.centre / interval);
    };
    intervalSlider.setValue(1.0);

    addAndMakeVisible(activeGrainsLabel);

    addAndMakeVisible(durationSlider);
    durationSlider.setRange(1, 4000);
    durationSlider.onValueChange = [this] {
        audioProcessor.grainEngine.durationParam.centre = (float)(durationSlider.getValue() / 1000.0f * audioProcessor.getSampleRate());
    };
    durationSlider.setValue(300);

    addAndMakeVisible(panningSlider);
    panningSlider.setRange(-1, 1);
    panningSlider.onValueChange = [this] {
        audioProcessor.grainEngine.panningParam.centre = (float)panningSlider.getValue();
    };
    panningSlider.setValue(0);

    addAndMakeVisible(readposSlider);
    readposSlider.setRange(0, 1);
    readposSlider.onValueChange = [this] {
        audioProcessor.grainEngine.readposParam.centre = (float)(readposSlider.getValue() * audioProcessor.getSampleRate());
    };
    readposSlider.setValue(0);

    addAndMakeVisible(velocitySlider);
    velocitySlider.setRange(0.25, 4);
    velocitySlider.onValueChange = [this] {
        audioProcessor.grainEngine.velocityParam.centre = (float)(velocitySlider.getValue());
    };
    velocitySlider.setValue(1);

    addAndMakeVisible(directionSlider);
    directionSlider.setRange(0.25, 4);
    directionSlider.onValueChange = [this] {
        audioProcessor.grainEngine.directionParam.centre = (float)(directionSlider.getValue());
    };
    directionSlider.setValue(1);
    // Randomness

    addAndMakeVisible(intervalRandSlider);
    intervalRandSlider.setRange(0, 1);
    intervalRandSlider.onValueChange = [this] {
        audioProcessor.grainEngine.intervalParam.deviation = (float)intervalRandSlider.getValue();
    };
    intervalRandSlider.setValue(0.0);

    addAndMakeVisible(durationRandSlider);
    durationRandSlider.setRange(0, 1000);
    durationRandSlider.onValueChange = [this] {
        audioProcessor.grainEngine.durationParam.deviation = (float)(durationRandSlider.getValue() / 1000.0f * audioProcessor.getSampleRate());
    };
    durationRandSlider.setValue(0);

    addAndMakeVisible(panningRandSlider);
    panningRandSlider.setRange(0, 2);
    panningRandSlider.onValueChange = [this] {
        audioProcessor.grainEngine.panningParam.deviation = (float)panningRandSlider.getValue();
    };
    panningRandSlider.setValue(0);

    addAndMakeVisible(readposRandSlider);
    readposRandSlider.setRange(0, 10);
    readposRandSlider.onValueChange = [this] {
        audioProcessor.grainEngine.readposParam.deviation = (float)(readposRandSlider.getValue() * audioProcessor.getSampleRate());
    };
    readposRandSlider.setValue(0);

    addAndMakeVisible(velocityRandSlider);
    velocityRandSlider.setRange(0, 1);
    velocityRandSlider.setSkewFactorFromMidPoint(0.1);
    velocityRandSlider.onValueChange = [this] {
        audioProcessor.grainEngine.velocityParam.deviation = (float)velocityRandSlider.getValue();
    };
    velocityRandSlider.setValue(0.0);

    addAndMakeVisible(directionRandSlider);
    directionRandSlider.setRange(0, 1);
    directionRandSlider.setSkewFactorFromMidPoint(0.1);
    directionRandSlider.onValueChange = [this] {
        audioProcessor.grainEngine.directionParam.deviation = (float)directionRandSlider.getValue();
    };
    directionRandSlider.setValue(0.0);

    addAndMakeVisible(intervalLabel);
    addAndMakeVisible(durationLabel);
    addAndMakeVisible(panningLabel);
    addAndMakeVisible(readposLabel);
    addAndMakeVisible(velocityLabel);
    addAndMakeVisible(randomLabel);
    addAndMakeVisible(directionLabel);

    intervalLabel.setText("interval", juce::dontSendNotification);
    durationLabel.setText("duration", juce::dontSendNotification);
    panningLabel.setText("panning", juce::dontSendNotification);
    readposLabel.setText("readpos", juce::dontSendNotification);
    velocityLabel.setText("velocity", juce::dontSendNotification);
    randomLabel.setText("random", juce::dontSendNotification);
    directionLabel.setText("direction", juce::dontSendNotification);

    intervalLabel.setJustificationType(juce::Justification::centred);
    durationLabel.setJustificationType(juce::Justification::centred);
    panningLabel.setJustificationType(juce::Justification::centred);
    readposLabel.setJustificationType(juce::Justification::centred);
    velocityLabel.setJustificationType(juce::Justification::centred);
    randomLabel.setJustificationType(juce::Justification::centred);
    directionLabel.setJustificationType(juce::Justification::centred);


    addAndMakeVisible(stemSelect);
    stemSelect.addItem("source", source);
    stemSelect.addItem("vocals", vocal);
    stemSelect.addItem("drums", drums);
    stemSelect.addItem("bass", bass);
    stemSelect.addItem("piano", piano);
    stemSelect.addItem("other", other);
    stemSelect.addItem("accompaniment", accompaniment);

    stemSelect.onChange = [this] { stemChanged(); };

    setSize(800, 600);
}

SplitGrainsAudioProcessorEditor::~SplitGrainsAudioProcessorEditor()
{
    //stopThread(4000);
}



void SplitGrainsAudioProcessorEditor::timerCallback()
{
    activeGrainsLabel.setText(juce::String(audioProcessor.grainEngine.pool.size()), juce::dontSendNotification);
}

//==============================================================================
void SplitGrainsAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (colourPalette.getSpaceCadet());
    
}

void SplitGrainsAudioProcessorEditor::resized()
{
    //const int width = getWidth();
    intervalLabel.setBounds(100, 50, 100, 30);
    durationLabel.setBounds(200, 50, 100, 30);
    panningLabel.setBounds(300, 50, 100, 30);
    readposLabel.setBounds(400, 50, 100, 30);
    velocityLabel.setBounds(500, 50, 100, 30);
    directionLabel.setBounds(600, 50, 100, 30);

    intervalSlider.setBounds(100, 100, 100, 100);
    durationSlider.setBounds(200, 100, 100, 100);
    panningSlider.setBounds(300, 100, 100, 100);
    readposSlider.setBounds(400, 100, 100, 100);
    velocitySlider.setBounds(500, 100, 100, 100);
    directionSlider.setBounds(600, 100, 100, 100);

    randomLabel.setBounds(0, 230, 100, 30);

    intervalRandSlider.setBounds(100, 200, 100, 100);
    durationRandSlider.setBounds(200, 200, 100, 100);
    panningRandSlider.setBounds(300, 200, 100, 100);
    readposRandSlider.setBounds(400, 200, 100, 100);
    velocityRandSlider.setBounds(500, 200, 100, 100);
    directionRandSlider.setBounds(600, 200, 100, 100);

    activeGrainsLabel.setBounds(10, getHeight() - 40, 100, 30);

    stemSelect.setBounds(getWidth() * 0.05, getHeight() * 0.7, getWidth() * 0.85, getHeight() * 0.10);

    readposSlider.setRange(0, audioProcessor.grainEngine.readposParam.maximum / audioProcessor.getSampleRate());

 
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

void SplitGrainsAudioProcessorEditor::stemChanged()
{
    switch (stemSelect.getSelectedId())
    {
        case source:
            juce::Logger::writeToLog(audioProcessor.stems.getReference(0));
            audioProcessor.loadFile(audioProcessor.stems.getReference(0), true); 
            break;
        case vocal:
            juce::Logger::writeToLog(audioProcessor.stems.getReference(1));
            audioProcessor.loadFile(audioProcessor.stems.getReference(1), true);
            break;
        case accompaniment:
            juce::Logger::writeToLog(audioProcessor.stems.getReference(2));
            audioProcessor.loadFile(audioProcessor.stems.getReference(2), true);
            break;
        case drums:
            juce::Logger::writeToLog(audioProcessor.stems.getReference(3));
            audioProcessor.loadFile(audioProcessor.stems.getReference(3), true);
            break;
        case bass:
            juce::Logger::writeToLog(audioProcessor.stems.getReference(4));
            audioProcessor.loadFile(audioProcessor.stems.getReference(4), true);
            break;
        case piano:
            juce::Logger::writeToLog(audioProcessor.stems.getReference(5));
            audioProcessor.loadFile(audioProcessor.stems.getReference(5), true);
            break;
        case other:
            juce::Logger::writeToLog(audioProcessor.stems.getReference(6));
            audioProcessor.loadFile(audioProcessor.stems.getReference(6), true);
            break;

        default: audioProcessor.loadFile(audioProcessor.stems.getReference(0), false); break;
    }
}
