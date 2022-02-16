/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Grain.h";
#include "ReferenceCountedBuffer.h";

//==============================================================================
/**
*/
class SplitGrainsAudioProcessor  : public juce::AudioProcessor, public juce::Thread {
public:
    //==============================================================================
    SplitGrainsAudioProcessor();
    ~SplitGrainsAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    void processMidi(juce::MidiBuffer& midiMessages, int numSamples);

    float clip(float n, float lower, float upper);

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //void deleteExtraFiles(const juce::String& path, spleeter::SeparationType type);

    void checkForBuffersToFree();

    void run() override;
    void checkBuffersToFree();
    void loadFile(const juce::String& path);
    int wrap(int val, const int low, const int high);

    //Main Grain Parameters
    juce::AudioParameterFloat* positionParam;
    juce::AudioParameterFloat* randPosParam;
    juce::AudioParameterFloat* directionParam;
    juce::AudioParameterFloat* densityParam;
    juce::AudioParameterFloat* randDensityParam;
    juce::AudioParameterFloat* durationParam;
    juce::AudioParameterFloat* randDurParam;
    juce::AudioParameterFloat* transParam;
    juce::AudioParameterFloat* randTransParam;
    juce::AudioParameterFloat* volumeParam;
    juce::AudioParameterFloat* randVolumeParam;
    juce::AudioParameterBool* holdParam;

    //Envelope parameters
    juce::AudioParameterFloat* envMidParam;
    juce::AudioParameterFloat* envSustainParam;
    juce::AudioParameterFloat* envCurveParam;
private:
    //==============================================================================
    juce::AudioFormatManager formatManager;
    //juce::AudioBuffer<float> waveform;
    //juce::Synthesiser mSampler;

    juce::ReferenceCountedArray<ReferenceCountedBuffer> buffers;
    ReferenceCountedBuffer::Ptr fileBuffer;
    long long int time;
    long long int nextGrainOnset;
    double sampleRate;
    int midiNotes[128] = { 0 };

    juce::Array<Grain> grainStack;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SplitGrainsAudioProcessor)
};
