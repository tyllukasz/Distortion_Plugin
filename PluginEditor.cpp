#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    // === SLIDERS ===
    addAndMakeVisible(gainKnobSlider);
    gainKnobSlider.setLookAndFeel(&myKnobLookAndFeel);
    gainKnobSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainKnobSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);

    gainKnobSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "GAIN", gainKnobSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::grey);

    g.setColour (juce::Colours::orange);
    auto r = getBounds().toFloat();
    r.removeFromRight(40.f);
    r.removeFromLeft(40.f);
    r.removeFromBottom(65.f);
    g.drawRoundedRectangle(r, 20, 5);

}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor...

    // ============================================================
    gainKnobSlider.setBoundsRelative(0.1, 0.54, 0.3, 0.3);
}



