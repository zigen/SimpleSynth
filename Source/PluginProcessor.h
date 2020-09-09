//
// Created by zigen on 2020/09/09.
//

#ifndef SIMPLESYNTH_PLUGINPROCESSOR_H
#define SIMPLESYNTH_PLUGINPROCESSOR_H

#include <JuceHeader.h>
#include <juce_audio_processors/juce_audio_processors.h>

class PluginProcessor : public juce::AudioProcessor {
public:
    PluginProcessor();

    ~PluginProcessor() override;

    void prepareToPlay(double sampleRate, int samplePerBlock) override;

    void releaseResources() override;

    bool isBusesLayoutSupported(const BusesLayout &layouts) const override;

    void processBlock(juce::AudioBuffer<float> &, juce::MidiBuffer &) override;

    juce::AudioProcessorEditor *createEditor() override;

    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;

    bool producesMidi() const override;

    bool isMidiEffect() const override;

    double getTailLengthSeconds() const override;

    int getNumPrograms() override;

    int getCurrentProgram() override;

    void setCurrentProgram(int index) override;

    const juce::String getProgramName(int index) override;

    void changeProgramName(int index, const juce::String &newName) override;

    void getStateInformation(juce::MemoryBlock &destData) override;

    void setStateInformation(const void *data, int sizeInBytes) override;


private:
    juce::Synthesiser synth;
};


#endif //SIMPLESYNTH_PLUGINPROCESSOR_H
