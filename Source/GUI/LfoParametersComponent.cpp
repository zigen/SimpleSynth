//
// Created by zigen on 2020/09/13.
//

#include "LfoParametersComponent.h"

namespace {
    const Colour PANEL_COLOUR = juce::Colour(36, 36, 36);
    const float PANEL_NAME_FONT_SIZE = 24.0f;
    const float PARAM_LABEL_FLOAT_SIZE = 16.0f;
    const int PANEL_NAME_HEIGHT = 42;
    const int LOCAL_MARGIN = 2;
}

LfoParametersComponent::LfoParametersComponent(LfoParameters *lfoParams) :
        _lfoParamsPtr(lfoParams),
        targetSelector("LFO-Target"),
        waveTypeSelector("LFO-WaveType"),
        amountSlider(Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox),
        speedSlider(Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox) {

    targetSelector.addItemList(_lfoParamsPtr->LfoTarget->getAllValueStrings(), 1);
    targetSelector.setSelectedItemIndex(_lfoParamsPtr->LfoTarget->getIndex(), dontSendNotification);
    targetSelector.setJustificationType(Justification::centred);
    targetSelector.addListener(this);
    addAndMakeVisible(targetSelector);

    waveTypeSelector.addItemList(_lfoParamsPtr->LfoWaveType->getAllValueStrings(), 1);
    waveTypeSelector.setSelectedItemIndex(_lfoParamsPtr->LfoWaveType->getIndex(), dontSendNotification);
    waveTypeSelector.setJustificationType(Justification::centred);
    waveTypeSelector.addListener(this);
    addAndMakeVisible(waveTypeSelector);

    amountSlider.setRange(_lfoParamsPtr->LfoAmount->range.start,
                          _lfoParamsPtr->LfoAmount->range.end, 0.01);
    amountSlider.setValue(_lfoParamsPtr->LfoAmount->get(), dontSendNotification);
    amountSlider.setPopupDisplayEnabled(true, true, this);
    amountSlider.setPopupMenuEnabled(true);
    amountSlider.addListener(this);
    addAndMakeVisible(amountSlider);

    speedSlider.setRange(_lfoParamsPtr->LfoSpeed->range.start,
                         _lfoParamsPtr->LfoSpeed->range.end, 0.01);
    speedSlider.setValue(_lfoParamsPtr->LfoSpeed->get(), dontSendNotification);
    speedSlider.setPopupDisplayEnabled(true, true, this);
    speedSlider.setPopupMenuEnabled(true);
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);

    Font paramLabelFont = Font(PARAM_LABEL_FLOAT_SIZE, Font::plain).withTypefaceStyle("Regular");

    targetLabel.setFont(paramLabelFont);
    targetLabel.setText("Target", dontSendNotification);
    targetLabel.setJustificationType(Justification::centred);
    targetLabel.setEditable(false, false, false);
    addAndMakeVisible(targetLabel);

    waveTypeLabel.setFont(paramLabelFont);
    waveTypeLabel.setText("WaveType", dontSendNotification);
    waveTypeLabel.setJustificationType(Justification::centred);
    waveTypeLabel.setEditable(false, false, false);
    addAndMakeVisible(waveTypeLabel);

    amountLabel.setFont(paramLabelFont);
    amountLabel.setText("Amount", dontSendNotification);
    amountLabel.setJustificationType(Justification::centred);
    amountLabel.setEditable(false, false, false);
    addAndMakeVisible(amountLabel);

    speedLabel.setFont(paramLabelFont);
    speedLabel.setText("Speed", dontSendNotification);
    speedLabel.setJustificationType(Justification::centred);
    speedLabel.setEditable(false, false, false);
    addAndMakeVisible(speedLabel);

    startTimerHz(30.0f);

}

LfoParametersComponent::~LfoParametersComponent() {}

void LfoParametersComponent::timerCallback() {
    targetSelector.setSelectedItemIndex(_lfoParamsPtr->LfoTarget->getIndex(), dontSendNotification);
    waveTypeSelector.setSelectedItemIndex(_lfoParamsPtr->LfoWaveType->getIndex(), dontSendNotification);
    amountSlider.setValue(_lfoParamsPtr->LfoAmount->get(), dontSendNotification);
    speedSlider.setValue(_lfoParamsPtr->LfoSpeed->get(), dontSendNotification);
}

void LfoParametersComponent::sliderValueChanged(Slider *slider) {
    if (slider == &amountSlider) {
        *_lfoParamsPtr->LfoAmount = (float) amountSlider.getValue();
    }
    if (slider == &speedSlider) {
        *_lfoParamsPtr->LfoSpeed = (float) speedSlider.getValue();
    }
}

void LfoParametersComponent::paint(Graphics &g) {
    Font panelNameFont = Font(PANEL_NAME_FONT_SIZE, Font::plain).withTypefaceStyle("Italic");
    {
        float x = 0.0f, y = 0.0f, width = (float) getWidth(), height = (float) getHeight();
        g.setColour(PANEL_COLOUR);
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
    }

    {
        Rectangle<int> bounds = getLocalBounds();
        Rectangle<int> textArea = bounds.removeFromTop(PANEL_NAME_HEIGHT).reduced(LOCAL_MARGIN);
        String text("LFO");
        Colour textColour = Colours::white;
        g.setColour(textColour);
        g.setFont(panelNameFont);
        g.drawText(text, textArea, Justification::centred, true);
    }
}

void LfoParametersComponent::resized() {
    float rowSize = 2.0f;
    float divide = 1.0f / rowSize;
    int labelHeight = 20;

    Rectangle<int> bounds = getLocalBounds();
    bounds.removeFromTop(PANEL_NAME_HEIGHT);
    Rectangle<int> upperArea = bounds.removeFromTop(bounds.getHeight() * 0.5);
    {
        Rectangle<int> area = upperArea.removeFromLeft(getWidth() * divide);
        targetLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        targetSelector.setBounds(
                area.removeFromTop(labelHeight * 2).reduced(LOCAL_MARGIN * 2));
    }
    {
        Rectangle<int> area = upperArea.removeFromLeft(getWidth() * divide);
        amountLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        amountSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    Rectangle<int> lowerArea = bounds;
    {
        Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        waveTypeLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        waveTypeSelector.setBounds(
                area.removeFromTop(labelHeight * 2).reduced(LOCAL_MARGIN * 2));
    }
    {
        Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        speedLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        speedSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
}

void LfoParametersComponent::comboBoxChanged(ComboBox *comboBoxThatHasChanged) {
    if (comboBoxThatHasChanged == &targetSelector) {
        *_lfoParamsPtr->LfoTarget = targetSelector.getSelectedItemIndex();
    }
    if (comboBoxThatHasChanged == &waveTypeSelector) {
        *_lfoParamsPtr->LfoWaveType = waveTypeSelector.getSelectedItemIndex();
    }
}
