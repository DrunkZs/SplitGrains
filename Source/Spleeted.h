/*
  ==============================================================================

    spleeted.h
    Created: 8 Feb 2022 12:24:11pm
    Author:  Christopher Davies-Dickson

    Using spleeterpp library found here https://github.com/gvne/spleeterpp
    Spleeterpp is a spleeter interface for c++ created by https://github.com/gvne
  ==============================================================================
*/
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "spleeter/spleeter.h"

#pragma once
class Spleeted
{
public:
    Spleeted(SplitGrainsAudioProcessor&);
    ~Spleeted();

    spleeter::Waveform forceStereo(const Eigen::MatrixXf& data);
    spleeter::Waveform read(const juce::String& file, double* sample_rate, std::error_code& err);
    void spleeted(const std::string& file, spleeter::SeparationType type, juce::String& output_dir, juce::String& model_dir);
    void splitTwo(spleeter::Waveform& source, std::error_code& err, juce::String& output_dir, juce::File& file);
    void splitFour(spleeter::Waveform& source, std::error_code& err, juce::String& output_dir, juce::File& file);
    void splitFive(spleeter::Waveform& source, std::error_code& err, juce::String& output_dir, juce::File& file);
    void Write(const juce::String& output_path, const spleeter::Waveform& data);

private:
    double sample_rate;
    std::error_code err;
    SplitGrainsAudioProcessor& audioProcessor;

    juce::CriticalSection splitting;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Spleeted)
};