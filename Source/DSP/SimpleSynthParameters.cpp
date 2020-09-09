//
// Created by zigen on 2020/09/10.
//

#include "SimpleSynthParameters.h"


OscillatorParameters::OscillatorParameters(AudioParameterFloat *sineWaveLevel,
                                           AudioParameterFloat *sawWaveLevel,
                                           AudioParameterFloat *triWaveLevel,
                                           AudioParameterFloat *squareWaveLevel,
                                           AudioParameterFloat *noiseLevel)
        : SineWaveLevel(sineWaveLevel),
          SawWaveLevel(sawWaveLevel),
          TriWaveLevel(triWaveLevel),
          SquareWaveLevel(squareWaveLevel),
          NoiseLevel(noiseLevel) {}

void OscillatorParameters::addAllParameters(AudioProcessor &processor) {
    processor.addParameter(SineWaveLevel->paramID, (double) SineWaveLevel->get());
    processor.addParameter(SawWaveLevel->paramID, (double) SawWaveLevel->get());
    processor.addParameter(TriWaveLevel->paramID, (double) TriWaveLevel->get());
    processor.addParameter(SquareWaveLevel->paramID, (double) SquareWaveLevel->get());
    processor.addParameter(NoiseLevel->paramID, (double) NoiseWaveLevel->get());
}

void OscillatorParameters::saveParameters(XmlElement &xml) {
    xml.setAttribute(SineWaveLevel->paramID, (double) SineWaveLevel->get());
    xml.setAttribute(SawWaveLevel->paramID, (double) SawWaveLevel->get());
    xml.setAttribute(TriWaveLevel->paramID, (double) TriWaveLevel->get());
    xml.setAttribute(SquareWaveLevel->paramID, (double) SquareWaveLevel->get());
    xml.setAttribute(NoiseLevel->paramID, (double) NoiseWaveLevel->get());
}

void OscillatorParameters::loadParameters(XmlElement &xml) {
    *SineWaveLevel = (float) xml.getDoubleAttribute(SineWaveLevel->paramID, 1.0);
    *SawWaveLevel = (float) xml.getDoubleAttribute(SawWaveLevel->paramID, 1.0);
    *TriWaveLevel = (float) xml.getDoubleAttribute(TriWaveLevel->paramID, 1.0);
    *SquareWaveLevel = (float) xml.getDoubleAttribute(SquareWaveLevel->paramID, 1.0);
    *NoiseLevel = (float) xml.getDoubleAttribute(NoiseWaveLevel->paramID, 1.0);
}
