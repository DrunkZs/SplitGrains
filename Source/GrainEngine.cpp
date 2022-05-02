/*
  ==============================================================================

    GrainEngine.cpp
    Created: 16 Feb 2022 12:23:04pm
    Author:  Christopher Davies-Dickson
    Source: https://github.com/ollierik/puro-juce-granular

  ==============================================================================
*/

#include "GrainEngine.h"

GrainEngine::GrainEngine() : timer(0), intervalParam(1.0f, 0.0f, 0.1f, 5000.0f), durationParam(100.0f, 100.0f, 0, 44100 * 10)
                           , panningParam(0.0f, 0.0f, -1.0f, 1.0f), readposParam(44100.0f, 0.0f, 0, 88200)
                           , velocityParam(1.0f, 0.0f, 0.25f, 4.0f), directionParam(0.0f,1.0f), sourceBuffer(0, 0)
{
    pool.elements.reserve(4096);
}

GrainEngine::~GrainEngine()
{
}

void GrainEngine::processBlock(juce::AudioBuffer<float>& writeBuffer)
{
    juce::Logger::writeToLog("Buffer loaded  in process block" + writeBuffer.getNumChannels());
    // TODO potential bug if number of output channels is not 2
    errorif(writeBuffer.getNumChannels() < 2, "BUG: implement different write buffer sizes");

    auto dstBuffer = puro::buffer_from_juce_buffer<puro::buffer<2, float>>(writeBuffer);

    const int numChannels = sourceBuffer.num_channels();
    if (numChannels == 1)
    {
        processGrains(dstBuffer, sourceBuffer.as_buffer<puro::buffer<1, float>>());
    }
    else if (numChannels == 2)
    {
        processGrains(dstBuffer, sourceBuffer.as_buffer<puro::buffer<2, float>>());
    }
    else if (numChannels != 0)
    {
        errorif(true, "source buffer channel number not supported");
    }
    else
    {
        // if numChannels == 0, the audio source file has not been loaded, and we do nothing
    }
}

template<typename BufferType, typename SourceType>
inline void GrainEngine::processGrains(BufferType buffer, SourceType source)
{
    const int blockSize = buffer.length();
    juce::Logger::writeToLog("processing grain for block size " + blockSize );


    // iterate all grains, adding their output to audio buffer
    for (auto&& it : pool)
    {
        if (process_grain(buffer, it.get(), context, source))
        {
            juce::Logger::writeToLog("popping grain ");
            pool.pop(it);
        }
    }

    // add new grains
    int n = buffer.length();
    while ((n = timer.advance(n)) > 0)
    {
        // for each tick, reset interval, get new values for the grain, and create grain

        const float interval = intervalParam.get();
        timer.interval = puro::math::round(durationParam.centre / interval);

        errorif(timer.interval < 0, "Well this is unexpected, timer shouldn't be let to do that");

        const int duration = durationParam.get();
        const float panning = panningParam.get();
        const int readpos = readposParam.get();
        const float velocity = velocityParam.get();
        const float direction = directionParam.get();

        // push to the pool of grains, get a handle in return
        auto it = pool.push(Grain(blockSize - n, duration, readpos, panning, velocity, sourceBuffer.length(), direction));

        // immediately process the first block for the newly created grain, potentially also already removing it
        // if the pool is full, it rejects the push operation and returns invalid iterator, and the grain doesn't get added
        if (it.is_valid())
        {
            if (process_grain(buffer, it.get(), context, source))
            {
                pool.pop(it);
            }
        }
    }
}