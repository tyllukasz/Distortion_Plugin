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

    juce::Path transferFunctionCurve;

    g.fillAll(juce::Colours::grey);

    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(getRenderArea(),5);
    g.setColour(juce::Colours::red);
    g.drawVerticalLine(getRenderArea().getCentreX(), ((getHeight() - getRenderArea().getHeight()) / 2),
                       getHeight() - ((getHeight() - getRenderArea().getHeight()) / 2));

    g.drawHorizontalLine(getRenderArea().getCentreY(), ((getWidth() - getRenderArea().getWidth()) / 2),
                         getWidth() - ((getWidth() - getRenderArea().getWidth()) / 2));

    auto gain = processorRef.apvts.getRawParameterValue("GAIN");
    auto gain_value = gain->load();

    //==================================================================================================================
    //==================================================================================================================
    int verticalCurveResolution {1024};
    int horizontalCurveResolution {16};
    float maxInputAmplitudeValue {3.f};
    float maxOutputAmplitudeValue {2.f};

    std::vector<float> xRealValues(horizontalCurveResolution); // x values normalized from 0 to maxInputAmplitude
    for(int i = 0; i < horizontalCurveResolution; i++) {
        xRealValues.at(i) = juce::jmap(static_cast<float>(i),
                                       0.f, static_cast<float>(horizontalCurveResolution - 1),
                                       0.f, maxInputAmplitudeValue);
    }

    std::vector<float> yRealValues(xRealValues.size()); // y values normalized from 0 to maxOutputAmplitude
    for(int i = 0; i < yRealValues.size(); i++) {
        yRealValues.at(i) = arcTangens(xRealValues.at(i), gain_value, 1.f);
    }
    //==================================================================================================================
    //==================================================================================================================

    std::vector<float> xCoordinate(horizontalCurveResolution);
    std::vector<float> yCoordinate(horizontalCurveResolution);

    xCoordinate.at(0) = getLocalBounds().toFloat().getCentreX();
    yCoordinate.at(0) = getLocalBounds().toFloat().getCentreY();
    transferFunctionCurve.startNewSubPath(xCoordinate.at(0), yCoordinate.at(0));

    for(int i = 1; i < horizontalCurveResolution; i++) {

        xCoordinate.at(i) = juce::jmap(xRealValues.at(i),
                                 0.f, maxInputAmplitudeValue,
                                 getLocalBounds().toFloat().getCentreX(),
                                 getLocalBounds().toFloat().getWidth());


        yCoordinate.at(i) = juce::jmap(yRealValues.at(i),
                                       0.f, maxOutputAmplitudeValue,
                                       getLocalBounds().toFloat().getCentreY(), 0.f);
    }

    for(int i = 1; i < horizontalCurveResolution; i++) {
        transferFunctionCurve.lineTo(xCoordinate.at(i), yCoordinate.at(i));
    }

//    transferFunctionCurve.startNewSubPath(getRenderArea().getCentreX(), getRenderArea().getCentreY());
//    transferFunctionCurve.lineTo(getRenderArea().getCentreX()+50, gain_value * (getRenderArea().getCentreY()-50));
//    transferFunctionCurve.lineTo(getRenderArea().getCentreX()+100, gain_value * (getRenderArea().getCentreY()-50));
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