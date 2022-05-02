/*
  ==============================================================================

    GrainEngine.h
    Created: 16 Feb 2022 12:23:04pm
    Author:  Christopher Davies-Dickson
    Source: https://github.com/ollierik/puro-juce-granular

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "puro.hpp"
#include <cmath>

#define MAX_NUM_CHANNELS 2
#define MAX_NUM_SRC_CHANNELS 2
#define MAX_BLOCK_SIZE 2048

struct Grain
{
    Grain(int offset, int length, int startIndex, float panning, double velocity, int sourceLength, int direction)
        : alignment({ offset, length })
        , readInc(velocity)
        , readPos(startIndex)
        , envelopeInc(puro::envelope_halfcos_get_increment<float>(length))
        , envelopePos(envelopeInc)
        , panCoeffs(puro::pan_create_stereo(panning))
        , direction(direction)
    {
        std::tie(alignment, readPos) = puro::interp_avoid_out_of_bounds_reads<3>(alignment, readPos, readInc, sourceLength, direction);
    }

    puro::relative_alignment alignment;

    const double readInc;
    double readPos;

    const float envelopeInc;
    float envelopePos;

    int direction;

    puro::PanCoeffs<float, 2> panCoeffs;
};

struct Context {
    puro::heap_block_pool<float, std::allocator<float>> context_pool;
    puro::dynamic_buffer<MAX_NUM_CHANNELS, float> temp;
    puro::buffer<1, float> envelope;

    Context() : temp(MAX_NUM_CHANNELS, MAX_BLOCK_SIZE, context_pool), envelope(MAX_BLOCK_SIZE, context_pool) {}
};


template <typename BufferType, typename ElementType, typename ContextType, typename SourceType>
bool process_grain(BufferType dst, ElementType& grain, ContextType& context, const SourceType source) {
    // Crop the dst buffer to fit the grain's offset and length, i.e. if the grain starts in the middle of the block, or ends
     // before the end of the block. Update the dst buffer and grain.alignment.
    std::tie(dst, grain.alignment) = puro::alignment_advance_and_crop_buffer(dst, grain.alignment);

    // audio buffer uses the memory from context.temp, casting it into a buffer with compile-time constant number of channels, and truncating it to needed length
    auto audio = context.temp.template as_buffer<SourceType>().trunc(dst.length()); // clang "feature", requires the keyword "template" with the function call

    // read audio from source, cubic interpolation
    grain.readPos = puro::interp3_fill(audio, source, grain.readPos, grain.readInc);

    // truncate temp envelope buffer to fit the length of our audio, and fill
    auto envelope = context.envelope.trunc(audio.length());
    grain.envelopePos = puro::envelope_halfcos_fill(envelope, grain.envelopePos, grain.envelopeInc);

    puro::multiply(audio, envelope);

    // get the cropped output segment that we want to add our output to, apply panning and add the audio signal
    BufferType output = dst.trunc(envelope.length());
    puro::pan_apply_and_add(output, audio, grain.panCoeffs);

    // return true if should be removed
    return (grain.alignment.remaining <= 0) // grain has depleted
        || (output.length() != dst.length()); // we've run out of source material to read
}

class GrainEngine {
    public:
        GrainEngine();
        ~GrainEngine();

        void processBlock(juce::AudioBuffer<float>& writeBuffer);
        
        template<typename BufferType, typename SourceType>
        void processGrains(BufferType buffer, SourceType source);

        Context context;
        puro::Timer<int> timer;
        puro::AlignedPool<Grain> pool;
        puro::dynamic_buffer<MAX_NUM_SRC_CHANNELS, float> sourceBuffer;

        puro::Parameter<float, true> intervalParam;
        puro::Parameter<int, false> durationParam;
        puro::Parameter<float, false> panningParam;
        puro::Parameter<int, false> readposParam;
        puro::Parameter<float, true> velocityParam;
        puro::Parameter<float, true> directionParam;
    private:
};
/*
template <typename BufferType, typename PositionType>
PositionType envelope_release(BufferType buffer, PositionType position, const PositionType increment) noexcept
{
    auto dst = buffer.channel(0);
    for (int i = 0; i < buffer.length(); ++i)
    {
        const auto sample = std::cos(position);
        dst[i] = sample;
        position += increment;
    }

    for (int ch = 1; ch < buffer.num_channels(); ++ch)
    {
        puro::math::copy(buffer.channel(ch), buffer.channel(0), buffer.length());
    }

    return position;
}

template <typename BufferType, typename PositionType>
PositionType envelope_attack(BufferType buffer, PositionType position, const PositionType increment) noexcept
{
    auto dst = buffer.channel(0);
    for (int i = 0; i < buffer.length(); ++i)
    {
        const auto sample = std::sin(position);
        dst[i] = sample;
        position += increment;
    }

    for (int ch = 1; ch < buffer.num_channels(); ++ch)
    {
        puro::math::copy(buffer.channel(ch), buffer.channel(0), buffer.length());
    }

    return position;
} */