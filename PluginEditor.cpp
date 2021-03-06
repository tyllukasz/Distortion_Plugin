#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), kcp(p), tfd(p), bcp(p)
{
    juce::ignoreUnused (processorRef);

    //==============================================================================
    addAndMakeVisible(tfd);
    addAndMakeVisible(kcp);
    addAndMakeVisible(bcp);

    //==============================================================================
    // === SLIDERS ===
//    addAndMakeVisible(gainInKnobSlider);
//    gainInKnobSlider.setLookAndFeel(&myKnobLookAndFeel);
//    gainInKnobSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
//    gainInKnobSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
//
//    gainInKnobSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "GAIN", gainInKnobSlider);



    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 400);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour::fromRGBA(143,143,143,255));
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor...

    tfd.setBounds(marginInPixels,marginInPixels,getWidth() - 2*marginInPixels,150);
    kcp.setBounds(marginInPixels, 150 + 2 * marginInPixels, getWidth() - 2*marginInPixels, 115);
    bcp.setBounds(marginInPixels, 265 + 3 * marginInPixels, getWidth() - 2*marginInPixels, 115);

    // ============================================================
    //gainInKnobSlider.setBoundsRelative(0.1, 0.54, 0.3, 0.3);
}



