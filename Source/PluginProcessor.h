/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PuroEngine.h"
#include "puro.hpp"
//==============================================================================
/**
*/
class SplitGrainsAudioProcessor : public juce::AudioProcessor{
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

    puro::AlignedPool<Grain> getGrainPool();

    void setSplit(const juce::StringArray &stems);
    void loadFile(const juce::String& path, BOOLEAN);
    juce::StringArray stems;
    int splitType = 0;

    PuroEngine grainEngine;

private:
    //==============================================================================
    juce::AudioFormatManager formatManager;
    juce::AudioSampleBuffer& getNewBuffer();
    juce::AudioSampleBuffer newBuffer;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SplitGrainsAudioProcessor)
};
//long long int time;
//long long int nextGrainOnset;
    //juce::dsp::ProcessorDuplicator <juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients <float>> lowPassFilter;
    //juce::dsp::IIR::Coefficients<float>::Ptr coefficients;
    //juce::ReferenceCountedArray<ReferenceCountedBuffer> buffers;
    //ReferenceCountedBuffer::Ptr fileBuffer;
    //juce::Array<Grain> grainStack;
    //float getMaximumPosition();
    //float getMaximumSampleCount();
    //void run() override;
    //void checkBuffersToFree();
    //int wrap(int val, const int low, const int high); //#include "Grain.h"
 //#include "ReferenceCountedBuffer.h";
//    
    //void deleteExtraFiles(const juce::String& path, spleeter::SeparationType type);
//    std::vector<double> magnitudes;
//std::vector<double> frequencies;

//float lastSampleRate;
//bool shouldUpdateFilter;
//int activeMidiNotes[128] = { 0 };
    //void checkForBuffersToFree();
//    float clip(float n, float lower, float upper);
