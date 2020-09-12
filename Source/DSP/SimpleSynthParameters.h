//
// Created by zigen on 2020/09/10.
//

#ifndef SIMPLESYNTH_SIMPLESYNTHPARAMETERS_H
#define SIMPLESYNTH_SIMPLESYNTHPARAMETERS_H

#include <JuceHeader.h>

class SynthParametersBase {
public:
    virtual ~SynthParametersBase() {};

    virtual void addAllParameters(AudioProcessor &processor) = 0;

    virtual void saveParameters(XmlElement &xml) = 0;

    virtual void loadParameters(XmlElement &xml) = 0;
};

class OscillatorParameters : public SynthParametersBase {
public:
    AudioParameterFloat *SineWaveLevel;
    AudioParameterFloat *SawWaveLevel;
    AudioParameterFloat *TriWaveLevel;
    AudioParameterFloat *SquareWaveLevel;
    AudioParameterFloat *NoiseLevel;

    OscillatorParameters(AudioParameterFloat *sineWaveLevel, AudioParameterFloat *sawWaveLevel,
                         AudioParameterFloat *triWaveLevel,
                         AudioParameterFloat *squareWaveLevel, AudioParameterFloat *noiseLevel);

    virtual void addAllParameters(AudioProcessor &processor) override;

    virtual void saveParameters(XmlElement &xml) override;

    virtual void loadParameters(XmlElement &xml) override;

private:
    OscillatorParameters() {};
};

class AmpEnvelopeParameters : public SynthParametersBase {
public:
    AudioParameterFloat *Attack;
    AudioParameterFloat *Decay;
    AudioParameterFloat *Sustain;
    AudioParameterFloat *Release;

    AmpEnvelopeParameters(AudioParameterFloat *attack, AudioParameterFloat *decay, AudioParameterFloat *sustain,
                          AudioParameterFloat *release);

    virtual void addAllParameters(AudioProcessor &processor) override;

    virtual void saveParameters(XmlElement &xml) override;

    virtual void loadParameters(XmlElement &xml) override;

private:
    AmpEnvelopeParameters() {};
};

class LfoParameters : public SynthParametersBase {
public:
    AudioParameterChoice *LfoTarget;
    AudioParameterChoice *LfoWaveType;
    AudioParameterFloat *LfoAmount;
    AudioParameterFloat *LfoSpeed;

    LfoParameters(AudioParameterChoice *lfoTarget, AudioParameterChoice *lfoWaveType, AudioParameterFloat *lfoAmount,
                  AudioParameterFloat *lfoSpeed);

    virtual void addAllParameters(AudioProcessor &processor) override;

    virtual void saveParameters(XmlElement &xml) override;

    virtual void loadParameters(XmlElement &xml) override;

private:
    LfoParameters() {};
};

class FilterParameters : public SynthParametersBase {
public:
    AudioParameterChoice *Type;
    AudioParameterFloat *Frequency;
    AudioParameterFloat *Q;

    FilterParameters(AudioParameterChoice *type, AudioParameterFloat *frequency, AudioParameterFloat *q);

    virtual void addAllParameters(AudioProcessor &processor) override;

    virtual void saveParameters(XmlElement &xml) override;

    virtual void loadParameters(XmlElement &xml) override;

private:
    FilterParameters() {};
};

class ReverbParameters : public SynthParametersBase {
public:
    AudioParameterFloat *RoomSize;
    AudioParameterFloat *Damping;
    AudioParameterFloat *WetLevel;
    AudioParameterFloat *DryLevel;
    AudioParameterFloat *Width;
    AudioParameterFloat *FreezeMode;

    ReverbParameters(AudioParameterFloat *roomSize, AudioParameterFloat *damping, AudioParameterFloat *wetLevel,
                     AudioParameterFloat *dryLevel,
                     AudioParameterFloat *width, AudioParameterFloat *freezeMode);

    virtual void addAllParameters(AudioProcessor &processor) override;

    virtual void saveParameters(XmlElement &xml) override;

    virtual void loadParameters(XmlElement &xml) override;

private:
    ReverbParameters() {};
};

#endif  // SIMPLESYNTH_SIMPLESYNTHPARAMETERS_H
