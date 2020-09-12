//
// Created by zigen on 2020/09/13.
//

#include "AmpEnvelopeComponent.h"
namespace {
    const Colour PANEL_COLOUR = juce::Colour(36, 36, 36);
    const float PANEL_NAME_FONT_SIZE = 24.0f;
    const float PARAM_LABEL_FLOAT_SIZE = 16.0f;
    const int PANEL_NAME_HEIGHT = 42;
    const int LOCAL_MARGIN = 2;
}

AmpEnvelopeParametersComponent::AmpEnvelopeParametersComponent(AmpEnvelopeParameters *ampEnvParams)
        : _ampEnvParamsPtr(ampEnvParams),
          attackSlider(Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox),
          decaySlider(Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox),
          sustainSlider(Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox),
          releaseSlider(Slider::SliderStyle::LinearVertical, Slider::TextEntryBoxPosition::NoTextBox) {

    attackSlider.setRange(_ampEnvParamsPtr->Attack->range.start,
                          _ampEnvParamsPtr->Attack->range.end, 0.01);
    attackSlider.setValue(_ampEnvParamsPtr->Attack->get(), dontSendNotification);
    attackSlider.setPopupDisplayEnabled(true, true, this);
    attackSlider.setPopupMenuEnabled(true);
    attackSlider.addListener(this);
    addAndMakeVisible(attackSlider);

    decaySlider.setRange(_ampEnvParamsPtr->Decay->range.start,
                         _ampEnvParamsPtr->Decay->range.end, 0.01);
    decaySlider.setValue(_ampEnvParamsPtr->Decay->get(), dontSendNotification);
    decaySlider.setPopupDisplayEnabled(true, true, this);
    decaySlider.setPopupMenuEnabled(true);
    decaySlider.addListener(this);
    addAndMakeVisible(decaySlider);

    sustainSlider.setRange(_ampEnvParamsPtr->Sustain->range.start,
                           _ampEnvParamsPtr->Sustain->range.end, 0.01);
    sustainSlider.setValue(_ampEnvParamsPtr->Sustain->get(), dontSendNotification);
    sustainSlider.setPopupDisplayEnabled(true, true, this);
    sustainSlider.setPopupMenuEnabled(true);
    sustainSlider.addListener(this);
    addAndMakeVisible(sustainSlider);

    releaseSlider.setRange(_ampEnvParamsPtr->Release->range.start,
                           _ampEnvParamsPtr->Release->range.end, 0.01);
    releaseSlider.setValue(_ampEnvParamsPtr->Release->get(), dontSendNotification);
    releaseSlider.setPopupDisplayEnabled(true, true, this);
    releaseSlider.setPopupMenuEnabled(true);
    releaseSlider.addListener(this);
    addAndMakeVisible(releaseSlider);

    Font paramLabelFont = Font(PARAM_LABEL_FLOAT_SIZE, Font::plain).withTypefaceStyle("Regular");

    attackLabel.setFont(paramLabelFont);
    attackLabel.setText("Attack", dontSendNotification);
    attackLabel.setJustificationType(Justification::centred);
    attackLabel.setEditable(false, false, false);
    addAndMakeVisible(attackLabel);

    decayLabel.setFont(paramLabelFont);
    decayLabel.setText("Decay", dontSendNotification);
    decayLabel.setJustificationType(Justification::centred);
    decayLabel.setEditable(false, false, false);
    addAndMakeVisible(decayLabel);

    sustainLabel.setFont(paramLabelFont);
    sustainLabel.setText("Sustain", dontSendNotification);
    sustainLabel.setJustificationType(Justification::centred);
    sustainLabel.setEditable(false, false, false);
    addAndMakeVisible(sustainLabel);

    releaseLabel.setFont(paramLabelFont);
    releaseLabel.setText("Release", dontSendNotification);
    releaseLabel.setJustificationType(Justification::centred);
    releaseLabel.setEditable(false, false, false);
    addAndMakeVisible(releaseLabel);

    startTimerHz(30.0f);
}

AmpEnvelopeParametersComponent::~AmpEnvelopeParametersComponent() {}

void AmpEnvelopeParametersComponent::paint(Graphics &g) {
    Font panelNameFont = Font(PANEL_NAME_FONT_SIZE, Font::plain).withTypefaceStyle("Italic");
    {
        float x = 0.0f, y = 0.0f, width = (float) getWidth(), height = (float) getHeight();
        g.setColour(PANEL_COLOUR);
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
    }

    {
        Rectangle<int> bounds = getLocalBounds();
        Rectangle<int> textArea = bounds.removeFromTop(PANEL_NAME_HEIGHT).reduced(LOCAL_MARGIN);
        String text("Envelope");
        Colour textColour = Colours::white;
        g.setColour(textColour);
        g.setFont(panelNameFont);
        g.drawText(text, textArea, Justification::centred, true);
    }
}

void AmpEnvelopeParametersComponent::resized() {
    float rowSize = 4.0f;
    float divide = 1.0f / rowSize;
    int labelHeight = 20;

    Rectangle<int> bounds = getLocalBounds();
    bounds.removeFromTop(PANEL_NAME_HEIGHT);
    {
        Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        attackLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        attackSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        decayLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        decaySlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        sustainLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        sustainSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        Rectangle<int> area = bounds.removeFromLeft(getWidth() * divide);
        releaseLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        releaseSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
}

void AmpEnvelopeParametersComponent::sliderValueChanged(Slider *slider) {
    if (slider == &attackSlider) {
        *_ampEnvParamsPtr->Attack = (float) attackSlider.getValue();
    }
    if (slider == &decaySlider) {
        *_ampEnvParamsPtr->Decay = (float) decaySlider.getValue();
    }
    if (slider == &sustainSlider) {
        *_ampEnvParamsPtr->Sustain = (float) sustainSlider.getValue();
    }
    if (slider == &releaseSlider) {
        *_ampEnvParamsPtr->Release = (float) releaseSlider.getValue();
    }
}

void AmpEnvelopeParametersComponent::timerCallback() {
    attackSlider.setValue(_ampEnvParamsPtr->Attack->get(), dontSendNotification);
    decaySlider.setValue(_ampEnvParamsPtr->Decay->get(), dontSendNotification);
    sustainSlider.setValue(_ampEnvParamsPtr->Sustain->get(), dontSendNotification);
    releaseSlider.setValue(_ampEnvParamsPtr->Release->get(), dontSendNotification);
}
