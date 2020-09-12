//
// Created by zigen on 2020/09/13.
//

#include "FilterParametersComponent.h"

namespace {
    const Colour PANEL_COLOUR = juce::Colour(36, 36, 36);
    const float PANEL_NAME_FONT_SIZE = 24.0f;
    const float PARAM_LABEL_FLOAT_SIZE = 16.0f;
    const int PANEL_NAME_HEIGHT = 42;
    const int LOCAL_MARGIN = 2;
}

FilterParametersComponent::FilterParametersComponent(FilterParameters *filterParams) :
        _filterParamsPtr(filterParams),
        typeSelector("FilterType"),
        frequencySlider(Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox),
        qSlider(Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextEntryBoxPosition::NoTextBox) {

    typeSelector.addItemList(_filterParamsPtr->Type->getAllValueStrings(), 1);
    typeSelector.setSelectedItemIndex(_filterParamsPtr->Type->getIndex(), dontSendNotification);
    typeSelector.setJustificationType(Justification::centred);
    typeSelector.addListener(this);
    addAndMakeVisible(typeSelector);

    frequencySlider.setRange(_filterParamsPtr->Frequency->range.start,
                             _filterParamsPtr->Frequency->range.end, 0.01);
    frequencySlider.setValue(_filterParamsPtr->Frequency->get(), dontSendNotification);
    frequencySlider.setPopupDisplayEnabled(true, true, this);
    frequencySlider.setPopupMenuEnabled(true);
    frequencySlider.addListener(this);
    addAndMakeVisible(frequencySlider);

    qSlider.setRange(_filterParamsPtr->Q->range.start,
                     _filterParamsPtr->Q->range.end, 0.01);
    qSlider.setValue(_filterParamsPtr->Q->get(), dontSendNotification);
    qSlider.setPopupDisplayEnabled(true, true, this);
    qSlider.setPopupMenuEnabled(true);
    qSlider.addListener(this);
    addAndMakeVisible(qSlider);

    Font paramLabelFont = Font(PARAM_LABEL_FLOAT_SIZE, Font::plain).withTypefaceStyle("Regular");


    typeLabel.setFont(paramLabelFont);
    typeLabel.setText("Type", dontSendNotification);
    typeLabel.setJustificationType(Justification::centred);
    typeLabel.setEditable(false, false, false);
    addAndMakeVisible(typeLabel);

    frequencyLabel.setFont(paramLabelFont);
    frequencyLabel.setText("Frequency", dontSendNotification);
    frequencyLabel.setJustificationType(Justification::centred);
    frequencyLabel.setEditable(false, false, false);
    addAndMakeVisible(frequencyLabel);

    qLabel.setFont(paramLabelFont);
    qLabel.setText("Q", dontSendNotification);
    qLabel.setJustificationType(Justification::centred);
    qLabel.setEditable(false, false, false);
    addAndMakeVisible(qLabel);

    startTimerHz(30.0f);

}

FilterParametersComponent::~FilterParametersComponent() {}

void FilterParametersComponent::timerCallback() {
    typeSelector.setSelectedItemIndex(_filterParamsPtr->Type->getIndex(), dontSendNotification);
    frequencySlider.setValue(_filterParamsPtr->Frequency->get(), dontSendNotification);
    qSlider.setValue(_filterParamsPtr->Q->get(), dontSendNotification);
}

void FilterParametersComponent::sliderValueChanged(Slider *slider) {
    if (slider == &frequencySlider) {
        *_filterParamsPtr->Frequency = (float) frequencySlider.getValue();
    }
    if (slider == &qSlider) {
        *_filterParamsPtr->Q = (float) qSlider.getValue();
    }
}

void FilterParametersComponent::paint(Graphics &g) {
    Font panelNameFont = Font(PANEL_NAME_FONT_SIZE, Font::plain).withTypefaceStyle("Italic");
    {
        float x = 0.0f, y = 0.0f, width = (float) getWidth(), height = (float) getHeight();
        g.setColour(PANEL_COLOUR);
        g.fillRoundedRectangle(x, y, width, height, 10.0f);
    }

    {
        Rectangle<int> bounds = getLocalBounds();
        Rectangle<int> textArea = bounds.removeFromTop(PANEL_NAME_HEIGHT).reduced(LOCAL_MARGIN);
        String text("Filter");
        Colour textColour = Colours::white;
        g.setColour(textColour);
        g.setFont(panelNameFont);
        g.drawText(text, textArea, Justification::centred, true);
    }
}

void FilterParametersComponent::resized() {
    float rowSize = 2.0f;
    float divide = 1.0f / rowSize;
    int labelHeight = 20;

    Rectangle<int> bounds = getLocalBounds();
    bounds.removeFromTop(PANEL_NAME_HEIGHT);
    Rectangle<int> upperArea = bounds.removeFromTop(bounds.getHeight() * 0.5);
    {
        Rectangle<int> area = upperArea.removeFromLeft(getWidth() * divide);
        typeLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        typeSelector.setBounds(
                area.removeFromTop(labelHeight * 2).reduced(LOCAL_MARGIN * 2));
    }
    Rectangle<int> lowerArea = bounds;
    {
        Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        frequencyLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        frequencySlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
    {
        Rectangle<int> area = lowerArea.removeFromLeft(getWidth() * divide);
        qLabel.setBounds(area.removeFromTop(labelHeight).reduced(LOCAL_MARGIN));
        qSlider.setBounds(area.reduced(LOCAL_MARGIN));
    }
}

void FilterParametersComponent::comboBoxChanged(ComboBox *comboBoxThatHasChanged) {
    if (comboBoxThatHasChanged == &typeSelector) {
        *_filterParamsPtr->Type = typeSelector.getSelectedItemIndex();
    }
}

