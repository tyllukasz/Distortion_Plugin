#pragma once

#include "PluginProcessor.h"
#include "sliderLookAndFeel.h"
#include "guiComponents.h"

//==============================================================================
class AudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    // =========================================================
//    knobLookAndFeel myKnobLookAndFeel;
//    juce::Slider gainKnobSlider;

    // =========================================================
    // Layout definition
    transferFunctionDisplay tfd;
    knobsControlPanel kcp;
    buttonsControlPanel bcp;
    // =========================================================

//    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainKnobSliderAttachment;

    // =========================================================
    // Layout parameters

    int marginInPixels = 5;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};


