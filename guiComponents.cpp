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
    g.drawVerticalLine(getRenderArea().getCentreX(), 0.f,
                       getHeight());

    g.drawHorizontalLine(getRenderArea().getCentreY(), 0.f,
                         getWidth());

    auto gain = processorRef.apvts.getRawParameterValue("GAIN");
    auto gain_value = gain->load();

    //==================================================================================================================
    //==================================================================================================================
    int curveResolution {256};
    float maxInputAmplitudeValue {1.5f};
    float maxOutputAmplitudeValue {1.0f};

    std::vector<float> xRealValues(curveResolution); // x values normalized from -maxInputAmplitude to maxInputAmplitude
    for(int i = 0; i < curveResolution; i++) {
        xRealValues.at(i) = juce::jmap(static_cast<float>(i),
                                       0.f, static_cast<float>(curveResolution - 1),
                                       -maxInputAmplitudeValue, maxInputAmplitudeValue);
    }

    std::vector<float> yRealValues(xRealValues.size()); // y values normalized from 0 to maxOutputAmplitude
    for(int i = 0; i < yRealValues.size(); i++) {
        yRealValues.at(i) = arcTangens(xRealValues.at(i), gain_value);
    }
    //==================================================================================================================
    //==================================================================================================================

    std::vector<float> xCoordinate(curveResolution);
    std::vector<float> yCoordinate(curveResolution);

    xCoordinate.at(0) = 0.f;
    yCoordinate.at(0) = juce::jmap(yRealValues.at(0),
                                   -maxOutputAmplitudeValue, maxOutputAmplitudeValue,
                                   getLocalBounds().toFloat().getHeight(), 0.f);
    transferFunctionCurve.startNewSubPath(xCoordinate.at(0), yCoordinate.at(0));

    for(int i = 1; i < curveResolution; i++) {

        xCoordinate.at(i) = juce::jmap(xRealValues.at(i),
                                 -maxInputAmplitudeValue, maxInputAmplitudeValue,
                                 0.f,
                                 getLocalBounds().toFloat().getWidth());


        yCoordinate.at(i) = juce::jmap(yRealValues.at(i),
                                       -maxOutputAmplitudeValue, maxOutputAmplitudeValue,
                                       getLocalBounds().toFloat().getHeight(), 0.f);
    }

    for(int i = 1; i < curveResolution; i++) {
        transferFunctionCurve.lineTo(xCoordinate.at(i), yCoordinate.at(i));
    }

    g.setColour(juce::Colour::fromRGBA(147,211,241,255));
    g.strokePath(transferFunctionCurve, juce::PathStrokeType(3.f));

    //==================================================================================================================
    //==================================================================================================================
    juce::Rectangle<float> currentSample;
    currentSample.setSize(10.f, 10.f);

    auto sample = processorRef.bufferForGuiInterface.getReadPointer(0);

    auto actualXofCircle = juce::jmap(sample[0],
                                   0.f, maxInputAmplitudeValue,
                                   getLocalBounds().toFloat().getCentreX(),
                                   getLocalBounds().toFloat().getWidth());


   auto actualYofCircle = juce::jmap(arcTangens(sample[0], gain_value),
                                   0.f, maxOutputAmplitudeValue,
                                   getLocalBounds().toFloat().getCentreY(), 0.f);

    currentSample.setCentre(actualXofCircle, actualYofCircle);
    g.setColour(juce::Colours::orange);
    g.fillEllipse(currentSample);

}

void transferFunctionDisplay::parameterValueChanged(int parameterIndex, float newValue) {
    parametersChanged.set(true);
}

void transferFunctionDisplay::timerCallback() {
//    if(parametersChanged.compareAndSetBool(false, true)) {
//        repaint();
//    }
    repaint();
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