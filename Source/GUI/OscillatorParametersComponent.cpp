//
// Created by zigen on 2020/09/13.
//

#include "OscillatorParametersComponent.h"

namespace {
    const Colour PANEL_COLOUR = juce::Colour(36, 36, 36);
    const float PANEL_NAME_FONT_SIZE = 24.0f;
    const float PARAM_LABEL_FLOAT_SIZE = 16.0f;
    const int PANEL_NAME_HEIGHT = 42;
    const int LOCAL_MARGIN = 2;
}

OscillatorParametersComponent::OscillatorParametersComponent(OscillatorParameters *oscParams)
        : _oscParamsPtr(oscParams),
          sineWaveLevelSlider(Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox),
          sawWaveLevelSlider(Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox),
          triWaveLevelSlider(Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox),
          squareWaveLevelSlider(Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox),
          noiseLevelSlider(Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox) {

    sineWaveLevelSlider.setRange(_oscParamsPtr->SineWaveLevel->range.start,
                                 _oscParamsPtr->SineWaveLevel->range.end, 0.01);
    sineWaveLevelSlider.setValue(_oscParamsPtr->SineWaveLevel->get(), dontSendNotification);
    sineWaveLevelSlider.setPopupDisplayEnabled(true, true, this);
    sineWaveLevelSlider.setPopupMenuEnabled(true);
    sineWaveLevelSlider.addListener(this);
    addAndMakeVisible(sineWaveLevelSlider);

    sawWaveLevelSlider.setRange(_oscParamsPtr->SawWaveLevel->range.start,
                                _oscParamsPtr->SawWaveLevel->range.end, 0.01);
    sawWaveLevelSlider.setValue(_oscParamsPtr->SawWaveLevel->get(), dontSendNotification);
    sawWaveLevelSlider.setPopupDisplayEnabled(true, true, this);
    sawWaveLevelSlider.setPopupMenuEnabled(true);
    sawWaveLevelSlider.addListener(this);
    addAndMakeVisible(sawWaveLevelSlider);

    triWaveLevelSlider.setRange(_oscParamsPtr->TriWaveLevel->range.start,
                                _oscParamsPtr->TriWaveLevel->range.end, 0.01);
    triWaveLevelSlider.setValue(_oscParamsPtr->TriWaveLevel->get(), dontSendNotification);
    triWaveLevelSlider.setPopupDisplayEnabled(true, true, this);
    triWaveLevelSlider.setPopupMenuEnabled(true);
    triWaveLevelSlider.addListener(this);
    addAndMakeVisible(triWaveLevelSlider);

    squareWaveLevelSlider.setRange(_oscParamsPtr->SquareWaveLevel->range.start,
                                   _oscParamsPtr->SquareWaveLevel->range.end, 0.01);
    squareWaveLevelSlider.setValue(_oscParamsPtr->SquareWaveLevel->get(), dontSendNotification);
    squareWaveLevelSlider.setPopupDisplayEnabled(true, true, this);
    squareWaveLevelSlider.setPopupMenuEnabled(true);
    squareWaveLevelSlider.addListener(this);
    addAndMakeVisible(squareWaveLevelSlider);

    noiseLevelSlider.setRange(_oscParamsPtr->NoiseLevel->range.start,
                              _oscParamsPtr->NoiseLevel->range.end, 0.01);
    noiseLevelSlider.setValue(_oscParamsPtr->NoiseLevel->get(), dontSendNotification);
    noiseLevelSlider.setPopupDisplayEnabled(true, true, this);
    noiseLevelSlider.setPopupMenuEnabled(true);
    noiseLevelSlider.addListener(this);
    addAndMakeVisible(noiseLevelSlider);

    Font paramLabelFont = Font(PARAM_LABEL_FLOAT_SIZE, Font::plain).withTypefaceStyle("Regular");

    sineWaveLevelLabel.setFont(paramLabelFont);
    sineWaveLevelLabel.setText("Sine", dontSendNotification);
    sineWaveLevelLabel.setJustificationType(Justification::centred);
    sineWaveLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(sineWaveLevelLabel);

    sawWaveLevelLabel.setFont(paramLabelFont);
    sawWaveLevelLabel.setText("Saw", dontSendNotification);
    sawWaveLevelLabel.setJustificationType(Justification::centred);
    sawWaveLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(sawWaveLevelLabel);

    triWaveLevelLabel.setFont(paramLabelFont);
    triWaveLevelLabel.setText("Tri", dontSendNotification);
    triWaveLevelLabel.setJustificationType(Justification::centred);
    triWaveLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(triWaveLevelLabel);

    squareWaveLevelLabel.setFont(paramLabelFont);
    squareWaveLevelLabel.setText("Square", dontSendNotification);
    squareWaveLevelLabel.setJustificationType(Justification::centred);
    squareWaveLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(squareWaveLevelLabel);

    noiseLevelLabel.setFont(paramLabelFont);
    noiseLevelLabel.setText("Noise", dontSendNotification);
    noiseLevelLabel.setJustificationType(Justification::centred);
    noiseLevelLabel.setEditable(false, false, false);
    addAndMakeVisible(noiseLevelLabel);

    startTimerHz(30.0f);
}

OscillatorParametersComponent::~OscillatorParametersComponent() {}

void OscillatorParametersComponent::paint(Graphics &g) {
    Font panelNameFont = Font(PANEL_NAME_FONT_SIZE, Font::plain).withTypefaceStyle("Italic");
    {
        float x = 0.0f, y = 0.0f, width = (float) getWidth(), height = (float) getHeight();
        g.setColour(PANEL_COLOUR);
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
    }

    {
        Rectangle<int> bounds = getLocalBounds();
        Rectangle<int> textArea = bounds.removeFromTop(PANEL_NAME_HEIGHT).reduced(LOCAL_MARGIN);
        String text("OSC MIX");
        Colour textColour = Colours::white;
        g.setColour(textColour);
        g.setFont(panelNameFont);
        g.drawText(text, textArea, Justification::centred, true);
    }
}

void OscillatorParametersComponent::resized() {
    float rowSize = 5.0f;
    float divide = 1.0f / rowSize;
    int labelHeight = 20;

    Rectangle<int> bounds = getLocalBounds();
    bounds.removeFromTop(PANEL_NAME_HEIGHT);
    {
        Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        sineWaveLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        sineWaveLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        sawWaveLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        sawWaveLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        triWaveLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        triWaveLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        squareWaveLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        squareWaveLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        noiseLevelLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        noiseLevelSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
}

void OscillatorParametersComponent::sliderValueChanged(Slider *slider) {
    if (slider == &sineWaveLevelSlider) {
        *_oscParamsPtr->SineWaveLevel = (float) sineWaveLevelSlider.getValue();
    }
    if (slider == &sawWaveLevelSlider) {
        *_oscParamsPtr->SawWaveLevel = (float) sawWaveLevelSlider.getValue();
    }
    if (slider == &triWaveLevelSlider) {
        *_oscParamsPtr->TriWaveLevel = (float) triWaveLevelSlider.getValue();
    }
    if (slider == &squareWaveLevelSlider) {
        *_oscParamsPtr->SquareWaveLevel = (float) squareWaveLevelSlider.getValue();
    }
    if (slider == &noiseLevelSlider) {
        *_oscParamsPtr->NoiseLevel = (float) noiseLevelSlider.getValue();
    }
}

void OscillatorParametersComponent::timerCallback() {
    sineWaveLevelSlider.setValue(_oscParamsPtr->SineWaveLevel->get(), dontSendNotification);
    sawWaveLevelSlider.setValue(_oscParamsPtr->SawWaveLevel->get(), dontSendNotification);
    triWaveLevelSlider.setValue(_oscParamsPtr->TriWaveLevel->get(), dontSendNotification);
    squareWaveLevelSlider.setValue(_oscParamsPtr->SquareWaveLevel->get(), dontSendNotification);
    noiseLevelSlider.setValue(_oscParamsPtr->NoiseLevel->get(), dontSendNotification);
}
