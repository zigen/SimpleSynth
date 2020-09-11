//
// Created by zigen on 2020/09/10.
//

#ifndef SIMPLESYNTH_SIMPLEVOICE_H
#define SIMPLESYNTH_SIMPLEVOICE_H

#include "AmpEnvelope.h"
#include "SimpleSound.h"
#include "SimpleSynthParameters.h"
#include "WaveForms.h"

class SimpleVoice : public SynthesiserVoice {
 public:
  SimpleVoice(OscillatorParameters *oscParams, LfoParameters *lfoParams, AmpEnvelopeParameters *ampEnvParams, AudioParameterBool *velocitySenseParam);

  virtual ~SimpleVoice();

  virtual bool canPlaySound(SynthesiserSound *sound) override;

  virtual void startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;
  virtual void stopNote(float velocity, bool allowTailOff) override;
  virtual void controllerMoved(int controllerNumber, int newControllerValue) override;
  virtual void pitchWheelMoved(int newPitchWheelValue) override;
  virtual void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;

 private:
  float calcModulationFactor(float angle);

  float currentAngle, lfoAngle, angleDelta;
  float level, lastLevel, levelDiff;
  float pitchBend;

  WaveForms waveForms;
  AmpEnvelope ampEnv;

  OscillatorParameters *_oscParamsPtr;
  LfoParameters *_lfoParamsPtr;
  AmpEnvelopeParameters *_ampEnvParamsPtr;
  AudioParameterBool *_velocitySensParamPtr;
};

#endif  // SIMPLESYNTH_SIMPLEVOICE_H
