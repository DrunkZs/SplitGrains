/*
  ==============================================================================

    spleeted.cpp
    Created: 8 Feb 2022 12:24:11pm
    Author:  Christopher Davies-Dickson


    Took the read, write and force stero from this project
    https://github.com/gvne/urSpleeter/blob/master/Source/SpleeterProcessor.cpp

  ==============================================================================
*/

#include "Spleeted.h"


Spleeted::Spleeted(SplitGrainsAudioProcessor& p) : audioProcessor(p)
{
}

Spleeted::~Spleeted()
{
}

//Forces the file to use stero channels instead of mono
spleeter::Waveform Spleeted::forceStereo(const Eigen::MatrixXf& data) {
    if (data.rows() == 2) {
        return data;
    }
    // make the mean over rows
    auto mean = data.array().rowwise().sum() / data.rows();

    // duplicate it twice to get stereo
    spleeter::Waveform output(2, data.cols());
    output.row(0) = mean;
    output.row(1) = mean;
    return output;
}

//Reads the file for further processing
spleeter::Waveform Spleeted::read(const juce::String& file, double* sample_rate,
    std::error_code& err) {
    juce::AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    auto reader = std::make_unique<juce::AudioFormatReaderSource>(
        formatManager.createReaderFor(file), true);
    auto sample_reader = reader->getAudioFormatReader();
    *sample_rate = sample_reader->sampleRate;
    Eigen::MatrixXf data(sample_reader->numChannels,
        sample_reader->lengthInSamples);

    // Alloc data
    std::vector<float*> array_data;
    std::vector<std::vector<float>> vec_data;
    for (auto channel_idx = 0; channel_idx < sample_reader->numChannels;
        channel_idx++) {
        std::vector<float> channel_data(sample_reader->lengthInSamples);
        array_data.push_back(channel_data.data());
        vec_data.emplace_back(std::move(channel_data));
    }
    // Read
    if (!sample_reader->read(array_data.data(), sample_reader->numChannels, 0,
        static_cast<int>(sample_reader->lengthInSamples))) {
        err = std::make_error_code(std::errc::io_error);
        return spleeter::Waveform();
    }

    // Fill in waveform
    for (auto channel_idx = 0; channel_idx < data.rows(); channel_idx++) {
        data.row(channel_idx) = Eigen::Map<Eigen::VectorXf>(
            vec_data[channel_idx].data(), vec_data[channel_idx].size());
    }

    return forceStereo(data);
}

void Spleeted::spleeted(const std::string& file, spleeter::SeparationType type , juce::String &output_dir)
{
    const juce::ScopedLock lock(splitting);
    auto juceFile = juce::File(file);

    spleeter::Waveform drums;
    spleeter::Waveform bass;
    spleeter::Waveform piano;
    spleeter::Waveform other;
    
    auto source = read(file, &sample_rate, err);
    if (err) {
        juce::Logger::writeToLog("Error reading file");
    }

    spleeter::Initialize("C:\\Users\\User\\Documents\\Dev\\Libraries\\spleeterpp\\models\\default", { type }, err);
    if (err) {
        juce::Logger::writeToLog("Error init model;s");
    }

    switch (type) {
    case spleeter::TwoStems: 
        splitTwo(source, err, output_dir, juceFile);
        break;
    
    case spleeter::FourStems: 
        splitFour(source, err, output_dir, juceFile);
        break;
    
    case spleeter::FiveStems: 
        splitFive(source, err, output_dir, juceFile);
        break;
    }
}

void Spleeted::splitTwo(spleeter::Waveform& source, std::error_code& err, juce::String& output_dir, juce::File& file) {
    spleeter::Waveform vocals;
    spleeter::Waveform accompaniment;

    spleeter::Split(source, &vocals, &accompaniment, err);
    if (err) {
        juce::Logger::writeToLog("ERROR SPLITTING");
    }

    Write(output_dir + file.getFileNameWithoutExtension() + " vocals.wav", vocals);
    Write(output_dir + file.getFileNameWithoutExtension() + " accompaniment.wav", accompaniment);
    juce::Logger::writeToLog("Split SuccessFul");
    audioProcessor.loadFile(output_dir + file.getFileNameWithoutExtension() + " vocals.wav");
}
void Spleeted::splitFour(spleeter::Waveform& source, std::error_code& err, juce::String& output_dir, juce::File& file) {
    spleeter::Waveform vocals;
    spleeter::Waveform drums;
    spleeter::Waveform bass;
    spleeter::Waveform other;

    spleeter::Split(source, &vocals, &drums, &bass, &other, err);
    if (err) {
        juce::Logger::writeToLog("ERROR SPLITTING");
    }
    Write(output_dir + file.getFileNameWithoutExtension() + " vocals.wav", vocals);
    Write(output_dir + file.getFileNameWithoutExtension() + " drums.wav", drums);
    Write(output_dir + file.getFileNameWithoutExtension() + " bass.wav", bass);
    Write(output_dir + file.getFileNameWithoutExtension() + " other.wav", other);
    juce::Logger::writeToLog("Split SuccessFul");
    audioProcessor.loadFile(output_dir + file.getFileNameWithoutExtension() + " other.wav");
}
void Spleeted::splitFive(spleeter::Waveform& source, std::error_code& err, juce::String& output_dir, juce::File& file) {
    spleeter::Waveform vocals;
    spleeter::Waveform drums;
    spleeter::Waveform bass;
    spleeter::Waveform piano;
    spleeter::Waveform other;

    spleeter::Split(source, &vocals, &drums, &bass, &piano, &other, err);
    if (err) {
        juce::Logger::writeToLog("ERROR SPLITTING");
    }
    Write(output_dir + file.getFileNameWithoutExtension() + " vocals.wav", vocals);
    Write(output_dir + file.getFileNameWithoutExtension() + " drums.wav", drums);
    Write(output_dir + file.getFileNameWithoutExtension() + " bass.wav", bass);
    Write(output_dir + file.getFileNameWithoutExtension() + " piano.wav", piano);
    Write(output_dir + file.getFileNameWithoutExtension() + " other.wav", other);
    juce::Logger::writeToLog("Split SuccessFul");
    audioProcessor.loadFile(output_dir + file.getFileNameWithoutExtension() + " bass.wav");

}

void Spleeted::Write(const juce::String& output_path, const spleeter::Waveform& data) {
    juce::File output_file(output_path);
    
    juce::WavAudioFormat format;

    auto writer = std::unique_ptr<juce::AudioFormatWriter>(
        format.createWriterFor(new juce::FileOutputStream(output_file), sample_rate,
            data.rows(), 16, juce::StringPairArray(), 0));

    juce::AudioSampleBuffer buffer(data.rows(), data.cols());
    for (auto channel_idx = 0; channel_idx < data.rows(); channel_idx++) {
        Eigen::VectorXf row = data.row(channel_idx);
        buffer.copyFrom(channel_idx, 0, row.data(), data.cols());
    }
    writer->writeFromAudioSampleBuffer(buffer, 0, data.cols());
    writer->flush();
}