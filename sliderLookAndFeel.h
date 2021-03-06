//
// Created by User on 09/02/2022.
//

#ifndef DISTORTION_PLUGIN_NEW_SLIDERLOOKANDFEEL_H
#define DISTORTION_PLUGIN_NEW_SLIDERLOOKANDFEEL_H

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class knobLookAndFeel : public juce::LookAndFeel_V4
{

public:
    knobLookAndFeel();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

private:
    juce::Image image;

};

//==============================================================================
class myLookAndFeelV2 : public LookAndFeel_V4
{

public:
    myLookAndFeelV2();

    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
                          float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;

};

#endif //DISTORTION_PLUGIN_NEW_SLIDERLOOKANDFEEL_H
