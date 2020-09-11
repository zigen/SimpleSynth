//
// Created by zigen on 2020/09/09.
//

#include "PluginEditor.h"

#include "PluginProcessor.h"

namespace {
    const float KEY_HEIGHT = 80.0f;
    const float KEY_WIDTH = 32.0f;
    const int PANEL_MARGIN = 2;
}


PluginEditor::PluginEditor(PluginProcessor &p)
        : AudioProcessorEditor(p), processorRef(p),
          oscParametersComponent(&p.oscParameters),
          keyboardComponent(p.getKeyboardState(), MidiKeyboardComponent::Orientation::horizontalKeyboard) {
    setSize(500, 400);
    addAndMakeVisible(oscParametersComponent);
    addAndMakeVisible(keyboardComponent);

}
PluginEditor::~PluginEditor() {}

void PluginEditor::paint(juce::Graphics &g) {
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PluginEditor::resized() {
    Rectangle<int> bounds = getLocalBounds();

    keyboardComponent.setBounds(bounds.removeFromBottom(KEY_HEIGHT));

    Rectangle<int> upperArea = bounds.removeFromTop(bounds.getHeight() * 0.5);
    {
        oscParametersComponent.setBounds(upperArea.removeFromLeft(280).reduced(PANEL_MARGIN));
    }
}
