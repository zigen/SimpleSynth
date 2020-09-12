//
// Created by zigen on 2020/09/09.
//

#ifndef SIMPLESYNTH_PLUGINEDITOR_H
#define SIMPLESYNTH_PLUGINEDITOR_H

#include "PluginProcessor.h"
#include "GUI/ParametersComponent.h"
#include "GUI/AmpEnvelopeComponent.h"
#include "GUI/OscillatorParametersComponent.h"
#include "GUI/LfoParametersComponent.h"
#include "GUI/FilterParametersComponent.h"

class PluginEditor : public juce::AudioProcessorEditor {
public:
    explicit PluginEditor(PluginProcessor &);

    ~PluginEditor() override;

    void paint(juce::Graphics &) override;

    void resized() override;

private:
    PluginProcessor &processorRef;

    MidiKeyboardComponent keyboardComponent;
    OscillatorParametersComponent oscParametersComponent;
    AmpEnvelopeParametersComponent ampEnvParametersComponent;
    LfoParametersComponent lfoParametersComponent;
    FilterParametersComponent filterParametersComponent;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};

#endif  // SIMPLESYNTH_PLUGINEDITOR_H
