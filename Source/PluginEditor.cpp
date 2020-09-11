//
// Created by zigen on 2020/09/09.
//

#include "PluginEditor.h"

#include "PluginProcessor.h"

PluginEditor::PluginEditor(PluginProcessor &p) : AudioProcessorEditor(p), processorRef(p) { setSize(500, 400); }

PluginEditor::~PluginEditor() {}

void PluginEditor::paint(juce::Graphics &g) {
  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
  g.setColour(juce::Colours::white);
  g.setFont(15.0f);
  g.drawFittedText("Hello world!", getLocalBounds(), juce::Justification::centred, 1);
}

void PluginEditor::resized() {}
