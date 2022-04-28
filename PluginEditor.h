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
//    juce::Slider gainInKnobSlider;

    // =========================================================
    // Layout definition
    transferFunctionDisplay tfd;
    KnobsControlPanel kcp;
    ButtonsControlPanel bcp;
    // =========================================================

//    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainInKnobSliderAttachment;

    // =========================================================
    // Layout parameters

    int marginInPixels = 5;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};


