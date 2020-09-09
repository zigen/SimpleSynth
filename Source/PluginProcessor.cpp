//
// Created by zigen on 2020/09/09.
//
#include "PluginEditor.h"
#include "PluginProcessor.h"
#include "DSP/SimpleVoice.h"
#include "DSP/SimpleSound.h"

PluginProcessor::PluginProcessor() : AudioProcessor() {}

PluginProcessor::~PluginProcessor() {}

void PluginProcessor::prepareToPlay(double sampleRate, int samplePerBlock) {
    synth.clearVoices();
    synth.clearVoices();
    synth.setCurrentPlaybackSampleRate(sampleRate);
    BigInteger canPlayNotes;
    canPlayNotes.setRange(0, 127, true);

    BigInteger canPlayChannels;
    canPlayChannels.setRange(1, 16, true);

    synth.addSound(new SimpleSound(canPlayNotes, canPlayChannels));

    int numVoices = voiceSizeParameter->get();
    for (int i = 0; i < numVoices; ++i) {
        synth.addVoice(new SimpleVoice(&oscParameters, &lfoParameters, &ampEnvParameters, velocitySenseParameter));
    }
}

void PluginProcessor::releaseResources() {}

bool PluginProcessor::isBusesLayoutSupported(const juce::AudioProcessor::BusesLayout &layouts) const { return false; }

void PluginProcessor::processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) {}

juce::AudioProcessorEditor *PluginProcessor::createEditor() {
    return new PluginEditor(*this);
}

bool PluginProcessor::hasEditor() const { return true; }

const juce::String PluginProcessor::getName() const {
    return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const { return true; }

bool PluginProcessor::producesMidi() const { return false; }

bool PluginProcessor::isMidiEffect() const { return false; }

double PluginProcessor::getTailLengthSeconds() const { return .0; }

int PluginProcessor::getNumPrograms() { return 1; }

int PluginProcessor::getCurrentProgram() { return 0; }

void PluginProcessor::setCurrentProgram(int index) {
    juce::ignoreUnused(index);
}

const juce::String PluginProcessor::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
}

void PluginProcessor::changeProgramName(int index, const juce::String &newName) {}

void PluginProcessor::getStateInformation(juce::MemoryBlock &destData) {}

void PluginProcessor::setStateInformation(const void *data, int sizeInBytes) {}


juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new PluginProcessor();
}