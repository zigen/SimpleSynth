//
// Created by zigen on 2020/09/09.
//

#ifndef SIMPLESYNTH_PLUGINPROCESSOR_H
#define SIMPLESYNTH_PLUGINPROCESSOR_H

#include <JuceHeader.h>
#include <juce_audio_processors/juce_audio_processors.h>

#include "DSP/SimpleSynthParameters.h"

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

    const StringArray LFO_TARGETS{"None", "WaveLevel", "WaveAngle"};
    const StringArray LFO_WAVE_TYPES{"Sine", "Saw", "Tri", "Square", "Noise"};
    const StringArray FILTER_TYPES{"Low-Pass", "High-Pass", "Band-Pass"};

    OscillatorParameters oscParameters;
    LfoParameters lfoParameters;
    AmpEnvelopeParameters ampEnvParameters;
    FilterParameters filterParameters;
    ReverbParameters reverbParameters;
    AudioParameterFloat *driveParameter;
    AudioParameterFloat *masterVolumeParameter;
    AudioParameterInt *voiceSizeParameter;
    AudioParameterBool *velocitySenseParameter;

    MidiKeyboardState &getKeyboardState() { return keyboardState; }

private:
    juce::Synthesiser synth;

    dsp::ProcessSpec spec;
    dsp::WaveShaper<float> clipper, limitter;

    static float clippingFunction(float inputValue);

    void changeVoiceSize();

    dsp::Gain<float> drive, masterVolume;
    dsp::Reverb reverb;
    dsp::ProcessorDuplicator<dsp::IIR::Filter<float>, dsp::IIR::Coefficients<float>> iirFilter;

    MidiKeyboardState keyboardState;
};

#endif  // SIMPLESYNTH_PLUGINPROCESSOR_H
