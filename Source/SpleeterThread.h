/*
  ==============================================================================

    SpleeterThread.h
    Created: 14 Feb 2022 4:22:56pm
    Author:  Christopher Davies-Dickson

  ==============================================================================
*/
#include <JuceHeader.h>
#include "Spleeted.h"
#pragma once
class SpleeterThread : public Spleeted, public juce::Thread 
{
public:
    SpleeterThread(SplitGrainsAudioProcessor& p, const std::string& f, spleeter::SeparationType t, juce::String& o);
    ~SpleeterThread();

    void run() override;

private:
    std::string file;
    juce::String output_dir;
    spleeter::SeparationType type;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpleeterThread);
};