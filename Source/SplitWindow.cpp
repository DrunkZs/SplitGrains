/*
  ==============================================================================

    WaveThumbnail.cpp
    Created: 1 Feb 2022 9:02:52pm
    Author:  Christopher Davies-Dickson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SplitWindow.h"


//==============================================================================

SplitWindow::SplitWindow(SplitGrainsAudioProcessor& p) : audioProcessor(p), spleeted (p), 
DocumentWindow("SplitGrains Split", colourPalette.getSpaceCadet(), DocumentWindow::closeButton | DocumentWindow::minimiseButton, true)

{
    noSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
    noSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
    noSepB.onClick = [&] {
        splitType = 0;
        buttonSelected = true;
        noSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getBabyBlueEyes());
        twoSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
        fourSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
        fiveSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());

        noSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getSpaceCadet());
        twoSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
        fourSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
        fiveSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
    };

    twoSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
    twoSepB.setColour(juce::TextButton::ColourIds::buttonOnColourId, colourPalette.getBabyBlueEyes());
    twoSepB.setColour(juce::TextButton::ColourIds::textColourOffId, colourPalette.getLavender());
    twoSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
    twoSepB.onClick = [&] {
        splitType = 1;
        buttonSelected = true;
        noSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
        twoSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getBabyBlueEyes());
        fourSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
        fiveSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());

        noSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
        twoSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getSpaceCadet());
        fourSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
        fiveSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
    };

    fourSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
    fourSepB.setColour(juce::TextButton::ColourIds::buttonOnColourId, colourPalette.getBabyBlueEyes());
    fourSepB.setColour(juce::TextButton::ColourIds::textColourOffId, colourPalette.getLavender());
    fourSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
    fourSepB.onClick = [&] {
        splitType = 2;
        buttonSelected = true;
        noSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
        twoSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
        fourSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getBabyBlueEyes());
        fiveSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());

        noSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
        twoSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
        fourSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getSpaceCadet());
        fiveSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
    };

    fiveSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
    fiveSepB.setColour(juce::TextButton::ColourIds::buttonOnColourId, colourPalette.getBabyBlueEyes());
    fiveSepB.setColour(juce::TextButton::ColourIds::textColourOffId, colourPalette.getLavender());
    fiveSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
    fiveSepB.onClick = [&] {
        splitType = 3;
        buttonSelected = true;
        noSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
        twoSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
        fourSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getSpaceCadet());
        fiveSepB.setColour(juce::TextButton::ColourIds::buttonColourId, colourPalette.getBabyBlueEyes());

        noSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
        twoSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
        fourSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getLavender());
        fiveSepB.setColour(juce::TextButton::ColourIds::textColourOnId, colourPalette.getSpaceCadet());
    };

    addAndMakeVisible(noSepB);
    addAndMakeVisible(twoSepB);
    addAndMakeVisible(fourSepB);
    addAndMakeVisible(fiveSepB);
}

void SplitWindow::closeButtonPressed() {
    delete this;
}

SplitWindow::~SplitWindow()
{
}

void SplitWindow::paint(juce::Graphics& g)
{
    g.fillAll(colourPalette.getSpaceCadet());
    g.setGradientFill(juce::ColourGradient(colourPalette.getSilverMetal(), 0.f, 0.f, colourPalette.getSpaceCadet(), static_cast<float>(getWidth()), static_cast<float>(getHeight() * 0.6), false));
    g.fillRect(0.f, 0.f, static_cast<float>(getWidth()), static_cast<float>(getHeight()));
    g.drawRect(0.f, 0.f, static_cast<float>(getWidth()), static_cast<float>(getHeight()));
    g.setColour(colourPalette.getLavender());
    g.drawMultiLineText("Select Seperation type. Then drop Files to Split into stems. Once process is done this window will close and main synth ui will open", getWidth() * 0.25, getHeight() * 0.25, 250, juce::Justification::centred, true);
    
}

bool SplitWindow::isInterestedInFileDrag(const juce::StringArray& files)
{
    for (auto file : files) {
        if (file.contains(".wav") || file.contains(".mp3") || file.contains(".aif")) {
            return true;
        }
    }

    return false;
}

void SplitWindow::filesDropped(const juce::StringArray& files, int x, int y)
{
    juce::String output = "C:\\Users\\User\\Documents\\Dev\\";
    for (auto file : files) {
        if (isInterestedInFileDrag(files)) {
            auto myFile = std::make_unique<juce::File>(file);
            juce::String str = output + myFile->getFileNameWithoutExtension();
            switch (splitType) {
            case 0:
                //fileName = myFile->getFileNameWithoutExtension();
                audioProcessor.loadFile(file);
                break;
            case 1:              
                new SpleeterThread(audioProcessor, myFile->getFullPathName().toStdString(), spleeter::TwoStems, output);
                //spleeted.spleeted((myFile->getFullPathName().toStdString()), spleeter::TwoStems, output);
                //fileName = myFile->getFileNameWithoutExtension() + " accompaniment";
                //audioProcessor.loadFile(str);
                break;
            case 2:
                new SpleeterThread(audioProcessor, myFile->getFullPathName().toStdString(), spleeter::FourStems, output);
                //spleeted.spleeted((myFile->getFullPathName().toStdString()), spleeter::FourStems, output);
                //fileName = myFile->getFileNameWithoutExtension() + " other";
                //audioProcessor.loadFile(str);
                break;
            case 3:
                new SpleeterThread(audioProcessor, myFile->getFullPathName().toStdString(), spleeter::FiveStems, output);
                //spleeted.spleeted((myFile->getFullPathName().toStdString()), spleeter::FiveStems, output);
                //fileName = myFile->getFileNameWithoutExtension() + " piano";
                //audioProcessor.loadFile(str);
                break;
            }
            if(buttonSelected) closeButtonPressed();
        }
    }
}
void SplitWindow::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    noSepB.setBounds(getWidth() * 0.05, getHeight() * 0.70, 80, 50);
    twoSepB.setBounds(getWidth() * 0.30, getHeight() * 0.70, 80, 50);
    fourSepB.setBounds(getWidth() * 0.55, getHeight() * 0.70, 80, 50);
    fiveSepB.setBounds(getWidth() * 0.80, getHeight() * 0.70, 80, 50);
}
