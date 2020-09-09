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

    OscillatorParameters(AudioParameterFloat *sineWaveLevel,
                         AudioParameterFloat *sawWaveLevel,
                         AudioParameterFloat *triWaveLevel,
                         AudioParameterFloat *squareWaveLevel,
                         AudioParameterFloat *noiseLevel);

    virtual void addAllParameters(AudioProcessor &processor) override;

    virtual void saveParameters(XmlElement &xml);

    virtual void loadParameters(XmlElement &xml);

private:
    OscillatorParameters() {};
};


#endif //SIMPLESYNTH_SIMPLESYNTHPARAMETERS_H
