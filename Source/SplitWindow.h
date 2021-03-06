/*
  ==============================================================================

    WaveThumbnail.h
    Created: 1 Feb 2022 9:02:52pm
    Author:  Christopher Davies-Dickson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "colourPalette.h"
#include "SpleeterThread.h"

//==============================================================================
/*
*/
class SplitWindow : public juce::FileDragAndDropTarget,
    public juce::DocumentWindow
{
public:
    SplitWindow(SplitGrainsAudioProcessor&);
    ~SplitWindow() override;
    void closeButtonPressed() override;


    void paint(juce::Graphics&) override;
    bool isInterestedInFileDrag(const juce::StringArray& files);
    void filesDropped(const juce::StringArray& files, int x, int y);

    void resized() override;

private:
    juce::String fileName{ "" };
    juce::TextButton noSepB{ "No seperation" }, twoSepB{ "2 stem seperation " }, fourSepB{ "4 stem seperation " }, fiveSepB{ "5 stem seperation " };
    juce::TextEditor modelDir{ "Set the dierctory the models are stored in" }, outputDir{ "Output directory of the split stems" };

    bool buttonSelected = false;
    int splitType = 7;

    ColourPalette colourPalette;
    SplitGrainsAudioProcessor& audioProcessor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SplitWindow)
};
