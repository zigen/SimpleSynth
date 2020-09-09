//
// Created by zigen on 2020/09/10.
//

#ifndef SIMPLESYNTH_SIMPLEVOICE_H
#define SIMPLESYNTH_SIMPLEVOICE_H

#include "SimpleSynthParameters.h"
#include "WaveForms.h"

class SimpleVoice : public SynthesiserVoice {

public:
    SimpleVoice(OscillatorParameters *oscParams, LfoParameters *lfoParams,
                AmpEnvelopeParameters *ampEnvParams, AudioParameterBool *velocitySenseParam);

    virtual ~SimpleVoice();

    virtual bool canPlaySound(SynthesiserSound *sound) override;

    virtual void
    startNote(int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;
};


#endif //SIMPLESYNTH_SIMPLEVOICE_H
