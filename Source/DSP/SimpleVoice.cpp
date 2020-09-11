//
// Created by zigen on 2020/09/10.
//

#include "SimpleVoice.h"

namespace {
const float HALF_PI = MathConstants<float>::halfPi;
const float ONE_PI = MathConstants<float>::pi;
const float TWO_PI = MathConstants<float>::twoPi;
}  // namespace

SimpleVoice::SimpleVoice(OscillatorParameters *oscParams, LfoParameters *lfoParams, AmpEnvelopeParameters *ampEnvParams,
                         AudioParameterBool *velocitySenseParam)
    : _oscParamsPtr(oscParams),
      _lfoParamsPtr(lfoParams),
      _ampEnvParamsPtr(ampEnvParams),
      _velocitySensParamPtr(velocitySenseParam),
      ampEnv(ampEnvParams->Attack->get(), ampEnvParams->Decay->get(), ampEnvParams->Sustain->get(), ampEnvParams->Release->get()),
      currentAngle(0.0f),
      lfoAngle(0.0f),
      angleDelta(0.0f),
      level(0.0f),
      lastLevel(0.0f),
      levelDiff(0.0f),
      pitchBend(0.0f) {}

SimpleVoice::~SimpleVoice() {}

bool SimpleVoice::canPlaySound(SynthesiserSound *sound) { return dynamic_cast<const SimpleSound *>(sound) != nullptr; }

void SimpleVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) {
  DBG("[StartNote] NoteNumber: " + juce::String(midiNoteNumber) + ", Velocity: " + juce::String(velocity));
  if (SimpleSound *soundForPlay = dynamic_cast<SimpleSound *>(sound)) {
    if (_velocitySensParamPtr->get()) {
      if (velocity <= 0.01f) {
        velocity = 0.01f;
      }
      level = velocity * 0.4f;
    } else {
      level = 0.8f;
    }
    levelDiff = level - lastLevel;
    pitchBend = ((float)currentPitchWheelPosition - 8192.0f) / 8192.0f;
    float cyclesPerSecond = (float)MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    float cyclesPerSample = (float)cyclesPerSecond / (float)getSampleRate();
    angleDelta = cyclesPerSample * TWO_PI;
    ampEnv.attackStart();
  }
}

void SimpleVoice::stopNote(float velocity, bool allowTailOff) {
  lastLevel = level;
  if (allowTailOff) {
    ampEnv.releaseStart();
  } else {
    if (ampEnv.isHolding()) {
      ampEnv.releaseStart();
    }
    clearCurrentNote();
  }
}

void SimpleVoice::controllerMoved(int controllerNumber, int newControllerValue) { juce::ignoreUnused(controllerNumber, newControllerValue); }

void SimpleVoice::pitchWheelMoved(int newPitchWheelValue) { pitchBend = ((float)newPitchWheelValue - 8192.0f) / 8192.0f; }

void SimpleVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
  if (SimpleSound *playingSound = dynamic_cast<SimpleSound *>(getCurrentlyPlayingSound().get())) {
    if (angleDelta != 0.0f) {
      while (--numSamples >= 0) {
        float modulationFactor = calcModulationFactor(lfoAngle);

        float currentSample = 0.0f;
        {
          currentSample += waveForms.sine(currentAngle) * _oscParamsPtr->SineWaveLevel->get();
          currentSample += waveForms.saw(currentAngle) * _oscParamsPtr->SawWaveLevel->get();
          currentSample += waveForms.triangle(currentAngle) * _oscParamsPtr->TriWaveLevel->get();
          currentSample += waveForms.square(currentAngle) * _oscParamsPtr->SquareWaveLevel->get();
          currentSample += waveForms.noise() * _oscParamsPtr->NoiseLevel->get();
        }

        if (_lfoParamsPtr->LfoTarget->getCurrentChoiceName() == "WaveLevel") {
          currentSample *= modulationFactor;
        }

        levelDiff *= 0.99f;
        currentSample *= level - levelDiff;
        currentSample *= ampEnv.getValue();

        for (int channelNum = outputBuffer.getNumChannels(); --channelNum >= 0;) {
          outputBuffer.addSample(channelNum, startSample, currentSample);
        }

        if (ampEnv.isReleasing()) {
          if (ampEnv.getValue() <= 0.005f) {
            ampEnv.releaseEnd();
            clearCurrentNote();
            angleDelta = 0.0f;
            currentAngle = 0.0f;
            lfoAngle = 0.0f;
            levelDiff = 0.0f;
            break;
          }
        }
        if (_lfoParamsPtr->LfoTarget->getCurrentChoiceName() == "WaveAngle") {
          currentAngle += angleDelta * pow(2.0f, pitchBend) * modulationFactor;
        } else {
          currentAngle += angleDelta * pow(2.0f, pitchBend);
        }
        lfoAngle += (_lfoParamsPtr->LfoSpeed->get() / (float)getSampleRate()) * TWO_PI;
        if (fabsf(levelDiff) <= 0.005f) {
          levelDiff = 0.0f;
        }
        if (currentAngle > TWO_PI) {
          currentAngle -= TWO_PI;
        }

        if (lfoAngle > TWO_PI) {
          lfoAngle -= TWO_PI;
        }

        ampEnv.setParameters(_ampEnvParamsPtr->Attack->get(), _ampEnvParamsPtr->Decay->get(), _ampEnvParamsPtr->Sustain->get(),
                             _ampEnvParamsPtr->Release->get());

        ampEnv.cycle((float)getSampleRate());
        ++startSample;
      }
    }
  }
}

float SimpleVoice::calcModulationFactor(float angle) {
  float factor = 0.0f;
  juce::String waveTypeName = _lfoParamsPtr->LfoWaveType->getCurrentChoiceName();
  if (waveTypeName == "Sine") {
    factor = waveForms.sine(angle);
  } else if (waveTypeName == "Saw") {
    factor = waveForms.saw(angle);
  } else if (waveTypeName == "Tri") {
    factor = waveForms.triangle(angle);
  } else if (waveTypeName == "Square") {
    factor = waveForms.square(angle);
  } else if (waveTypeName == "Noise") {
    factor = waveForms.noise();
  }

  factor = ((factor * _lfoParamsPtr->LfoAmount->get()) / 2.0f) + 0.5f;
  return factor;
}