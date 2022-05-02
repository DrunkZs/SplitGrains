/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SplitGrainsAudioProcessor::SplitGrainsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    formatManager.registerBasicFormats();

}

SplitGrainsAudioProcessor::~SplitGrainsAudioProcessor()
{

}

//==============================================================================
const juce::String SplitGrainsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SplitGrainsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SplitGrainsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SplitGrainsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SplitGrainsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SplitGrainsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SplitGrainsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SplitGrainsAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SplitGrainsAudioProcessor::getProgramName (int index)
{
    return {};
}

void SplitGrainsAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SplitGrainsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(samplesPerBlock);
    juce::ignoreUnused(sampleRate);
}

void SplitGrainsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SplitGrainsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void SplitGrainsAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{    
    for (int i = 0; i < buffer.getNumChannels(); ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    juce::ScopedNoDenormals noDenormals;

    grainEngine.processBlock(buffer);

/*    

    processMidi(midiMessages, numSamplesInBlock);

    ReferenceCountedBuffer::Ptr retainedBuffer(fileBuffer);

    if (retainedBuffer == nullptr) return;

    juce::AudioSampleBuffer* currentBuffer = retainedBuffer->getAudioSampleBuffer();

    const int numSamplesInFile = currentBuffer->getNumSamples();

    const juce::Array<Grain> localStack = grainStack;

    for (int s = 0; s < numSamplesInBlock; ++s) {
        for (int i = 0; i < localStack.size(); ++i) {
            if (localStack[i].onset < time) {
                if (time < (localStack[i].onset + localStack[i].length)) {
                    localStack[i].process(buffer, *currentBuffer, buffer.getNumChannels(), numSamplesInBlock, numSamplesInFile, time);
                }
            }
        }
        // check for bad values
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
            float* channelData = buffer.getWritePointer(channel);
            float currentSample = channelData[s];
            for (int i = 0; i < localStack.size(); ++i) {
                if (currentSample > 1.0 || currentSample < -1.0) {
                    juce::Logger::writeToLog("WARN: Bad Sample Value: " + juce::String(currentSample));
                    juce::Logger::writeToLog("Dumping Grain Stack: \n Onset:" + juce::String(localStack[i].onset)
                       + " length: " + juce::String(localStack[i].length)
                       + " startPos: " + juce::String(localStack[i].startPosition)
                       + " envAttack: " + juce::String(localStack[i].envAttack)
                       + " envRelease: " + juce::String(localStack[i].envRelease)
                       + " envCurve: " + juce::String(localStack[i].envCurve)
                       + " Rate: " + juce::String(localStack[i].rate)
                       + " Amp: " + juce::String(localStack[i].AMP));
                }
            }
            channelData[s] = clip(currentSample, -1.0, 1.0);
        }
        ++time;
    }
    */
}

void SplitGrainsAudioProcessor::processMidi(juce::MidiBuffer& midiMessages, int numSamples)
{
    /*
    juce::MidiBuffer::Iterator i(midiMessages);
    juce::MidiMessage message;
    int time;

    while (i.getNextEvent(message, time))
    {
        if (message.isNoteOn()) {
            midiNotes[message.getNoteNumber()] = message.getVelocity();
            notify();
        }
        if (message.isNoteOff()) {
            midiNotes[message.getNoteNumber()] = 0;
        }
        if (message.isAllNotesOff()) {
            for (int i = 0; i < 128; ++i)
                midiNotes[i] = 0;
        }
    }
    */
}

//==============================================================================
bool SplitGrainsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SplitGrainsAudioProcessor::createEditor()
{
    return new SplitGrainsAudioProcessorEditor (*this);
}

//==============================================================================
void SplitGrainsAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SplitGrainsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SplitGrainsAudioProcessor();
}

//void SplitGrainsAudioProcessor::run()
//{
//    while (!threadShouldExit()) {
//        checkBuffersToFree();
//        wait(500);
//    }
//}


void SplitGrainsAudioProcessor::setSplit(const juce::StringArray& splitStems)
{
    stems.mergeArray(splitStems);
}

void SplitGrainsAudioProcessor::loadFile(const juce::String& path, BOOLEAN clear) {
    juce::Logger::writeToLog("Loading File");
    
    auto file = juce::File(path);
    if (file == juce::File{}) return;
    try {

        std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
        if (reader != 0)
        {
            newBuffer = juce::AudioSampleBuffer(reader->numChannels, (int)reader->lengthInSamples);
            reader->read(&newBuffer, 0, (int)reader->lengthInSamples, 0, true, true);
        }

        grainEngine.sourceBuffer = puro::dynamic_buffer<MAX_NUM_SRC_CHANNELS, float>(newBuffer.getNumChannels()
            , newBuffer.getNumSamples()
            , newBuffer.getArrayOfWritePointers());
        grainEngine.readposParam.maximum = newBuffer.getNumSamples();
    }
    catch (const std::exception& e){
        juce::Logger::writeToLog(e.what());
    }
}

juce::AudioSampleBuffer& SplitGrainsAudioProcessor::getNewBuffer() {
    return newBuffer;
}




puro::AlignedPool<Grain> SplitGrainsAudioProcessor::getGrainPool()
{
    return puro::AlignedPool<Grain>();
}







//unused functions
/*
* 
* 
* float SplitGrainsAudioProcessor::getMaximumPosition()
{
    return 0.0f;
}

float SplitGrainsAudioProcessor::getMaximumSampleCount()
{
    return 0.0f;
}
* int SplitGrainsAudioProcessor::wrap(int val, const int low, const int high)
{
    int range_size = high - low + 1;
    if (val < low) {
        val += range_size * ((low - val) / range_size + 1);
    }
    return low + (val - low) % range_size;
}
void SplitGrainsAudioProcessor::run()
{
    checkForBuffersToFree();
    while (!threadShouldExit()) {
        int dur = 1000;

        //deleting grains
        // delete grains
        if (grainStack.size() > 0) {
            for (int i = grainStack.size() - 1; i >= 0; --i) {
                // check if the grain has ended
                long long int grainEnd = grainStack[i].onset + grainStack[i].length;
                bool hasEnded = grainEnd < time;

                if (hasEnded) grainStack.remove(i); // [4]
            }
        }

        // handle MIDI
        juce::Array<juce::Array<int>> activeNotes;

        for (int i = 0; i < 128; i++) {
            if (midiNotes[i] > 0) {
                activeNotes.add(juce::Array<int> {i, midiNotes[i] });
            }
        }

        // add grains
        if (fileBuffer != nullptr) {
            if (activeNotes.size() > 0) {
                // initialize nextGrainOnset to lie in the future
                if (nextGrainOnset == 0) nextGrainOnset = time;

                int numSamples = fileBuffer->getAudioSampleBuffer()->getNumSamples();

                //Transposition
                float midiNote = 60;
                midiNote = activeNotes[juce::Random::getSystemRandom().nextInt(activeNotes.size())][0];
                midiNote = (midiNote - 61);

                float trans = *transParam + midiNote;
                trans += 1 + (*randTransParam * (juce::Random::getSystemRandom().nextFloat() * 2 - 1));

                float ratio = pow(2.0, trans / 12.0);

                // Duration
                float dur = *durationParam * (1 + (*randDurParam * (juce::Random::getSystemRandom().nextFloat() * 2 - 1)));
                // this mapping introduces some problems check later!
                //dur *= (1 / ratio);

                int schedDelay = 700;
                long long int onset = nextGrainOnset + schedDelay;

                // Length
                float density = *densityParam * (1 + (*randDensityParam * (juce::Random::getSystemRandom().nextFloat() * 2 - 1)));
                int length = density * dur * sampleRate;

                // Position
                float randPosition = *randPosParam * (juce::Random::getSystemRandom().nextFloat() - 0.5);
                int startPosition = (*positionParam + randPosition) * numSamples;
                startPosition = wrap(startPosition, 0, numSamples);

                // Envelope
                float envMid = *envMidParam;
                float envSus = *envSustainParam;
                float envCurve = *envCurveParam;

                // Amplitude
                float amp = *volumeParam;
                amp *= 1 + *randVolumeParam * (juce::Random::getSystemRandom().nextFloat() * 2 - 1);

                nextGrainOnset = onset + (dur * sampleRate);

                grainStack.add(Grain(onset, length, startPosition, envMid, envSus, envCurve, ratio, amp));

                double schedError = ((onset - schedDelay) - time) / sampleRate;
                dur += schedError;
                wait(dur * 1000);
            }
            else {
                // there are no held notes so we should reset the value for nextGrainOnset
                nextGrainOnset = 0;
                wait(100);
            }
        }
        else {
            wait(100);
        }

    }
} 
float SplitGrainsAudioProcessor::clip(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}
*/