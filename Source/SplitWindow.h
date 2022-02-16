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
#include "spleeted.h"
#include "colourPalette.h"
#include "SpleeterThread.h"

//==============================================================================
/*
*/
class SplitWindow  :     public juce::FileDragAndDropTarget, 
                         public juce::DocumentWindow
{
public:
    SplitWindow(SplitGrainsAudioProcessor&);
    ~SplitWindow() override;
    void closeButtonPressed() override;


    void paint (juce::Graphics&) override;
    bool isInterestedInFileDrag(const juce::StringArray& files);
    void filesDropped(const juce::StringArray& files, int x, int y);
        
    void resized() override;

private:
    std::vector<float> mAudioPoints;
    juce::String fileName{""};
    const juce::File models_path = juce::File("C:\\Users\\User\\Documents\\Dev\\Libraries\\spleeterpp\\models");
    std::error_code err;
    juce::TextButton noSepB{ "No seperation" }, twoSepB{"2 stem seperation "}, fourSepB{ "4 stem seperation " }, fiveSepB { "5 stem seperation " };

    bool buttonSelected = false;
    int splitType = 7;

    ColourPalette colourPalette;
    SplitGrainsAudioProcessor& audioProcessor;

    Spleeted spleeted;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SplitWindow)
};
