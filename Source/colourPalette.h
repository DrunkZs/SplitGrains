/*
  ==============================================================================

    colourPalette.h
    Created: 9 Feb 2022 4:01:10pm
    Author:  Christopher Davies-Dickson

  ==============================================================================
*/
#include <JuceHeader.h>

#pragma once
class ColourPalette {

public:
    juce::Colour getLavender();
    juce::Colour getLightGray();
    juce::Colour getSilverMetal();
    juce::Colour getSpaceCadet();
    juce::Colour getBabyBlueEyes();

private:
    const juce::Colour LAVENDER_WEB = juce::Colour(234, 232, 255);
    const juce::Colour LIGHT_GRAY = juce::Colour(216, 213, 219);
    const juce::Colour SILVER_METAL = juce::Colour(173, 172, 181);
    const juce::Colour SPACE_CADET = juce::Colour(45, 49, 66);
    const juce::Colour BABY_BLUE_EYES = juce::Colour(176, 215, 255);
};