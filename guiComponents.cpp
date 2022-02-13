#include "guiComponents.h"

transferFunctionDisplay::transferFunctionDisplay(AudioPluginAudioProcessor& p) : processorRef(p) {

    const auto& params = processorRef.getParameters();
    for(auto param: params) {
        param->addListener(this);
    }

    startTimer(30);

}

transferFunctionDisplay::~transferFunctionDisplay() noexcept {
    const auto& params = processorRef.getParameters();
    for(auto param: params) {
        param->removeListener(this);
    }
}

void transferFunctionDisplay::paint(juce::Graphics &g) {

    transferFunctionCurve.clear();
    g.fillAll(juce::Colours::grey);

    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(getRenderArea(),5);
    g.setColour(juce::Colours::red);
    g.drawVerticalLine(getRenderArea().getCentreX(), 0.f, getHeight());
    g.drawHorizontalLine(getRenderArea().getCentreY(), 0.f, getWidth());

    auto gain = processorRef.apvts.getRawParameterValue("GAIN");
    auto gain_value = gain->load();
    transferFunctionCurve.startNewSubPath(getRenderArea().getCentreX(), getRenderArea().getCentreY());
    transferFunctionCurve.lineTo(getRenderArea().getCentreX()+50, gain_value * (getRenderArea().getCentreY()-50));
    transferFunctionCurve.lineTo(getRenderArea().getCentreX()+100, gain_value * (getRenderArea().getCentreY()-50));
    //transferFunctionCurve.closeSubPath();

    g.setColour(juce::Colours::blueviolet);
    g.strokePath(transferFunctionCurve, juce::PathStrokeType(3.f));


}

void transferFunctionDisplay::parameterValueChanged(int parameterIndex, float newValue) {
    parametersChanged.set(true);
}

void transferFunctionDisplay::timerCallback() {
    if(parametersChanged.compareAndSetBool(false, true)) {
        repaint();
    }
}

//void transferFunctionDisplay::resized() {
//
//}

juce::Rectangle<float> transferFunctionDisplay::getRenderArea() {
    auto renderArea = getLocalBounds().toFloat();
    renderArea.removeFromTop(5);
    renderArea.removeFromBottom(5);
    renderArea.removeFromLeft(5);
    renderArea.removeFromRight(5);
    return renderArea;
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