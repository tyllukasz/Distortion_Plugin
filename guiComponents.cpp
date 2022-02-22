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

    g.fillAll(juce::Colour::fromRGBA(143,143,143,255));

    g.setColour(juce::Colours::black);
    g.fillRoundedRectangle(getRenderArea(),7);
    g.setColour(juce::Colours::red);
    g.drawVerticalLine(getRenderArea().getCentreX(), 0.f,
                       getHeight());

    g.drawHorizontalLine(getRenderArea().getCentreY(), 0.f,
                         getWidth());

    auto gain = processorRef.apvts.getRawParameterValue("SHAPE");
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
    renderArea.removeFromTop(1.5f);
    renderArea.removeFromBottom(1.5f);
    renderArea.removeFromLeft(1.5f);
    renderArea.removeFromRight(1.5f);
    return renderArea;
}

knobsControlPanel::knobsControlPanel(AudioPluginAudioProcessor& p) : processorRef(p) {

    //============================================================================================================
    addAndMakeVisible(gainInKnobSlider);
    gainInKnobSlider.setLookAndFeel(&myKnobLookAndFeel);
    gainInKnobSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainInKnobSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    gainInKnobSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    gainInKnobSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour::fromRGBA(143,143,143,255));

    gainInKnobSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "GAIN_IN", gainInKnobSlider);

    gainInLabel.setText("Input gain", juce::dontSendNotification);
    gainInLabel.setJustificationType(juce::Justification::centred);
    gainInLabel.attachToComponent(&gainInKnobSlider, false);
    gainInLabel.setSize(60, 20);
    gainInLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(gainInLabel);

    //============================================================================================================
    addAndMakeVisible(shapeKnobSlider);
    shapeKnobSlider.setLookAndFeel(&myKnobLookAndFeel);
    shapeKnobSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    shapeKnobSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    shapeKnobSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    shapeKnobSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour::fromRGBA(143,143,143,255));

    shapeKnobSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "SHAPE", shapeKnobSlider);

    shapeLabel.setText("Shape", juce::dontSendNotification);
    shapeLabel.setJustificationType(juce::Justification::centred);
    shapeLabel.attachToComponent(&shapeKnobSlider, false);
    shapeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(shapeLabel);

    //============================================================================================================
    addAndMakeVisible(gainOutKnobSlider);
    gainOutKnobSlider.setLookAndFeel(&myKnobLookAndFeel);
    gainOutKnobSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    gainOutKnobSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    gainOutKnobSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    gainOutKnobSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colour::fromRGBA(143,143,143,255));

    gainOutKnobSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(processorRef.apvts, "GAIN_OUT", gainOutKnobSlider);

    gainOutLabel.setText("Output gain", juce::dontSendNotification);
    gainOutLabel.setJustificationType(juce::Justification::centred);
    gainOutLabel.attachToComponent(&gainOutKnobSlider, false);
    gainOutLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(gainOutLabel);
}

void knobsControlPanel::paint(juce::Graphics& g) {
    g.fillAll(juce::Colour::fromRGBA(143,143,143,255));

    g.setColour(juce::Colour::fromRGBA(93,93,93,255));
    g.drawRoundedRectangle(1.5f, 1.5f, getWidth()-3.f, getHeight()-3.f, 7.f, 1.f);

};

void knobsControlPanel::resized() {

    gainInKnobSlider.setBounds(0, 25, getWidth()/3, getHeight()-30);
    shapeKnobSlider.setBounds(getWidth()/3, 25, getWidth()/3, getHeight()-30);
    gainOutKnobSlider.setBounds(2*getWidth()/3, 25, getWidth()/3, getHeight()-30);

}

void buttonsControlPanel::paint(juce::Graphics& g) {

    g.fillAll(juce::Colour::fromRGBA(143,143,143,255));

    g.setColour(juce::Colour::fromRGBA(93,93,93,255));
    g.drawRoundedRectangle(1.5f, 1.5f, getWidth()-3.f, getHeight()-3.f, 7.f, 1.f);

};