#include "guiComponents.h"

//transferFunctionDisplay::transferFunctionDisplay() {
//    //...
//}

void transferFunctionDisplay::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::grey);
}

knobsControlPanel::knobsControlPanel(AudioPluginAudioProcessor& p) : processorRef(p) {

    addAndMakeVisible(gainKnobSlider);
    gainKnobSlider.setLookAndFeel(&myKnobLookAndFeel);
    gainKnobSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainKnobSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);

    gainKnobSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "GAIN", gainKnobSlider);
}

void knobsControlPanel::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::grey);

    g.setColour(juce::Colours::orange);
    g.drawRoundedRectangle(5.f, 5.f, getWidth()-10.f, getHeight()-10.f, 20, 5);

};

void knobsControlPanel::resized() {

//    gainKnobSlider.setBounds(0, 0, getHeight(), getHeight());
    gainKnobSlider.setBoundsRelative(0.1f, 0.1f, 0.2, 0.8f);

}

void buttonsControlPanel::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::grey);

    g.setColour(juce::Colours::orange);
    g.drawRoundedRectangle(5.f, 5.f, getWidth()-10.f, getHeight()-10.f, 20, 5);

};