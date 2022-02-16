/*
  ==============================================================================

    Grain.h
    Created: 10 Feb 2022 12:42:07pm
    Author: Christopher Davies-Dickson

  ==============================================================================
*/
#include <JuceHeader.h>

#pragma once
class Grain {
public:
    const long long int onset;
    const int length;
    const int startPosition;

    const float envAttack, envAttackRecip;
    const float envRelease, envReleaseRecip;
    const float envCurve;
    const float lengthRecip;

    const float rate;
    const float AMP;

    Grain();
    Grain(long long int onset, int length, int startPos, float center, float sustain, float curve, float r, float a);
    ~Grain();

    void process(juce::AudioSampleBuffer& currentBlock, juce::AudioSampleBuffer& fileBuffer, int numChannels, int blockNumSamples, int fileNumSamples, int time);
    float envelope(int time);

    inline float cubicinterp(float x, float y0, float y1, float y2, float y3);

private:
};