//
// Created by zigen on 2020/09/09.
//
#include "PluginProcessor.h"

#include "DSP/SimpleSound.h"
#include "DSP/SimpleVoice.h"
#include "PluginEditor.h"

PluginProcessor::PluginProcessor()
        : AudioProcessor(BusesProperties().withOutput("Output", AudioChannelSet::stereo(), true)),
          oscParameters{
                  new AudioParameterFloat("SINEWAVE_LEVEL", "SineWave-Level", 0.0f, 1.0f, 1.0f),
                  new AudioParameterFloat("SAWWAVE_LEVEL", "SawWave-Level", 0.0f, 1.0f, 1.0f),
                  new AudioParameterFloat("TRIWAVE_LEVEL", "TriWave-Level", 0.0f, 1.0f, 1.0f),
                  new AudioParameterFloat("SQUAREWAVE_LEVEL", "SquareWave-Level", 0.0f, 1.0f, 1.0f),
                  new AudioParameterFloat("NOISE_LEVEL", "Noise-Level", 0.0f, 1.0f, 1.0f),
          },
          lfoParameters{
                  new AudioParameterChoice("LFO_TARGET", "Lfo-Target", LFO_TARGETS, 0),
                  new AudioParameterChoice("LFO_WAVE_TYPE", "Lfo-Wave-Type", LFO_WAVE_TYPES, 0),
                  new AudioParameterFloat("LFO_LEVEL", "Lfo-Level", 0.0f, 1.0f, 0.5f),
                  new AudioParameterFloat("LFO_SPEED", "Lfo-Speed", 0.0f, 20.0f, 0.2f),
          },

          ampEnvParameters{
                  new AudioParameterFloat("AMPENV_ATTACK", "Attack", 0.01f, 3.0f, 0.1f),
                  new AudioParameterFloat("AMPENV_DECAY", "Decay", 0.01f, 3.0f, 0.1f),
                  new AudioParameterFloat("AMPENV_SUSTAIN", "Sustain", 0.0f, 1.0f, 1.0f),
                  new AudioParameterFloat("AMPENV_RELEASE", "Release", 0.01f, 3.0f, 0.1f),
          },
          filterParameters{
                  new AudioParameterChoice("FILTER_TYPE", "Filter-Type", FILTER_TYPES, 0),
                  new AudioParameterFloat("FILTER_FREQUENCY", "Filter-Frequency", 20.0f, 20000.0f, 20000.0f),
                  new AudioParameterFloat("FILTER_Q", "Q", 0.3f, 20.0f, 1.0f),
          },
          reverbParameters{
                  new AudioParameterFloat("REVERB_ROOM_SIZE", "Room-Size", 0.0f, 1.0f, 0.0f),
                  new AudioParameterFloat("REVERB_DAMPING", "Damping", 0.0f, 1.0f, 0.0f),
                  new AudioParameterFloat("REVERB_WET_LEVEL", "TriWave-Level", 0.0f, 1.0f, 1.0f),
                  new AudioParameterFloat("REVERB_DRY_LEVEL", "SquareWave-Level", 0.0f, 1.0f, 1.0f),
                  new AudioParameterFloat("REVERB_WIDTH", "Noise-Level", 0.0f, 1.0f, 1.0f),
                  new AudioParameterFloat("REVERB_FREEZE_SIZE", "Noise-Level", 0.0f, 1.0f, 1.0f),
          },
          driveParameter(new AudioParameterFloat("DRIVE", "Drive", -24.f, 12.f, 0.0f)),
          masterVolumeParameter(new AudioParameterFloat("MASTER_VOLUME", "Volume", -36.f, 6.f, -3.0f)),
          voiceSizeParameter(new AudioParameterInt("VOICE_SIZE", "Voice-Size", 1, 128, 8)),
          velocitySenseParameter(new AudioParameterBool("VELOCITY_SENSE", "Velocity-Sense", true)) {
    oscParameters.addAllParameters(*this);
    lfoParameters.addAllParameters(*this);
    ampEnvParameters.addAllParameters(*this);
    filterParameters.addAllParameters(*this);
    reverbParameters.addAllParameters(*this);
    addParameter(masterVolumeParameter);
    addParameter(voiceSizeParameter);
    addParameter(velocitySenseParameter);
}

PluginProcessor::~PluginProcessor() {}

void PluginProcessor::prepareToPlay(double sampleRate, int samplePerBlock) {
    synth.clearSounds();
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

    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    spec.maximumBlockSize = samplePerBlock;

    iirFilter.prepare(spec);
    drive.prepare(spec);
    clipper.prepare(spec);
    clipper.functionToUse = clippingFunction;
    reverb.prepare(spec);
    limitter.prepare(spec);
    limitter.functionToUse = clippingFunction;

    masterVolume.prepare(spec);
}

void PluginProcessor::releaseResources() {}

bool PluginProcessor::isBusesLayoutSupported(const juce::AudioProcessor::BusesLayout &layouts) const { return false; }

void PluginProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
    if ((int) voiceSizeParameter->get() != synth.getNumVoices()) {
        changeVoiceSize();
    }
    ScopedNoDenormals noDenormals;
    auto totalNumInputsChannels = getTotalNumInputChannels();
    auto totalNumOutputsChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputsChannels; i < totalNumOutputsChannels; ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    for (int channel = 0; channel < totalNumOutputsChannels; ++channel) {
        auto *channelData = buffer.getWritePointer(channel);
        buffer.clear(channel, 0, buffer.getNumSamples());
    }
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    dsp::AudioBlock<float> audioBlock(buffer);
    dsp::ProcessContextReplacing<float> context(audioBlock);
    if (filterParameters.Type->getCurrentChoiceName() == "Low-Pass") {
        *iirFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(spec.sampleRate,
                                                                       filterParameters.Frequency->get(),
                                                                       filterParameters.Q->get());
    } else if (filterParameters.Type->getCurrentChoiceName() == "High-Pass") {
        *iirFilter.state = *dsp::IIR::Coefficients<float>::makeHighPass(spec.sampleRate,
                                                                        filterParameters.Frequency->get(),
                                                                        filterParameters.Q->get());
    } else if (filterParameters.Type->getCurrentChoiceName() == "Band-Pass") {
        *iirFilter.state = *dsp::IIR::Coefficients<float>::makeBandPass(spec.sampleRate,
                                                                        filterParameters.Frequency->get(),
                                                                        filterParameters.Q->get());
    }
    iirFilter.process(context);

    drive.setGainDecibels(driveParameter->get());
    drive.process(context);

    clipper.process(context);

    limitter.process(context);

    masterVolume.setGainDecibels(masterVolumeParameter->get());
    masterVolume.process(context);
}

juce::AudioProcessorEditor *PluginProcessor::createEditor() { return new PluginEditor(*this); }

bool PluginProcessor::hasEditor() const { return true; }

const juce::String PluginProcessor::getName() const { return JucePlugin_Name; }

bool PluginProcessor::acceptsMidi() const { return true; }

bool PluginProcessor::producesMidi() const { return false; }

bool PluginProcessor::isMidiEffect() const { return false; }

double PluginProcessor::getTailLengthSeconds() const { return .0; }

int PluginProcessor::getNumPrograms() { return 1; }

int PluginProcessor::getCurrentProgram() { return 0; }

void PluginProcessor::setCurrentProgram(int index) { juce::ignoreUnused(index); }

const juce::String PluginProcessor::getProgramName(int index) {
    juce::ignoreUnused(index);
    return {};
}

void PluginProcessor::changeProgramName(int index, const juce::String &newName) {}

void PluginProcessor::getStateInformation(juce::MemoryBlock &destData) {}

void PluginProcessor::setStateInformation(const void *data, int sizeInBytes) {}

float PluginProcessor::clippingFunction(float inputValue) {
    float threshold = tanhf(inputValue);
    float outputValue = inputValue;
    if (abs(inputValue) >= abs(threshold)) {
        outputValue = threshold;
    }
    return outputValue;
}

void PluginProcessor::changeVoiceSize() {
    while (synth.getNumVoices() != voiceSizeParameter->get()) {
        if (synth.getNumVoices() > voiceSizeParameter->get()) {
            synth.removeVoice(synth.getNumVoices() - 1);
        } else {
            synth.addVoice(new SimpleVoice(&oscParameters, &lfoParameters, &ampEnvParameters, velocitySenseParameter));
        }
    }
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() { return new PluginProcessor(); }
