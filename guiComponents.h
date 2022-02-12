#ifndef DISTORTION_PLUGIN_NEW_GUICOMPONENTS_H
#define DISTORTION_PLUGIN_NEW_GUICOMPONENTS_H

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "sliderLookAndFeel.h"

class transferFunctionDisplay : public juce::Component {
public:
//    transferFunctionDisplay();
//    ~transferFunctionDisplay();

    void paint(juce::Graphics& g) override;
//    void resized() override;
};

class knobsControlPanel : public Component {
public:
    knobsControlPanel(AudioPluginAudioProcessor& p);
    void paint(juce::Graphics& g) override;
    void resized() override;


private:
    AudioPluginAudioProcessor& processorRef;

    knobLookAndFeel myKnobLookAndFeel;
    juce::Slider gainKnobSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainKnobSliderAttachment;
};

class buttonsControlPanel : public juce::Component {
public:
    void paint(juce::Graphics& g) override;
};

#endif //DISTORTION_PLUGIN_NEW_GUICOMPONENTS_H
