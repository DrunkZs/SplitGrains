/*
  ==============================================================================

    ReferenceCountedBuffer.cpp
    Created: 15 Feb 2022 1:36:15pm
    Author:  Christopher Davies-Dickson

  ==============================================================================
*/
#include "ReferenceCountedBuffer.h"

ReferenceCountedBuffer::ReferenceCountedBuffer(const juce::String& nameToUse, int numChannels, int numSamples) : name(nameToUse), buffer(numChannels, numSamples)
{
    juce::Logger::writeToLog("Buffer named " + name + " constructed. numChannels = " + juce::String(numChannels) + " , numSamples = " + juce::String(numSamples));
}

ReferenceCountedBuffer::~ReferenceCountedBuffer()
{
    juce::Logger::writeToLog("Buffer named '" + name + "' destroyed");
}

juce::AudioSampleBuffer* ReferenceCountedBuffer::getAudioSampleBuffer()
{
    return &buffer;
}
