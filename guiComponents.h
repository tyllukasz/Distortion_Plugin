#ifndef DISTORTION_PLUGIN_NEW_GUICOMPONENTS_H
#define DISTORTION_PLUGIN_NEW_GUICOMPONENTS_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "sliderLookAndFeel.h"
#include "TransferFunctions.h"


class transferFunctionDisplay : public juce::Component,
                                public juce::Timer,
                                public juce::AudioProcessorParameter::Listener {
public:
    transferFunctionDisplay(AudioPluginAudioProcessor& p);
    ~transferFunctionDisplay();

    void paint(juce::Graphics& g) override;
    void parameterValueChanged(int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {}
    void timerCallback() override;

    juce::Rectangle<float> getRenderArea();

private:
    AudioPluginAudioProcessor& processorRef;
    juce::Atomic<bool> parametersChanged {false};

};

class knobsControlPanel : public Component {
public:
    knobsControlPanel(AudioPluginAudioProcessor& p);
    void paint(juce::Graphics& g) override;
    void resized() override;


private:
    AudioPluginAudioProcessor& processorRef;

//    knobLookAndFeel myKnobLookAndFeel;
    myLookAndFeelV2 myKnobLookAndFeel;

    juce::Slider gainInKnobSlider;
    juce::Label gainInLabel;

    juce::Slider shapeKnobSlider;
    juce::Label shapeLabel;

    juce::Slider gainOutKnobSlider;
    juce::Label gainOutLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainInKnobSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> shapeKnobSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainOutKnobSliderAttachment;
};

class buttonsControlPanel : public juce::Component {
public:
    void paint(juce::Graphics& g) override;
};

#endif //DISTORTION_PLUGIN_NEW_GUICOMPONENTS_H
