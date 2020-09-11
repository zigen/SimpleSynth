//
// Created by zigen on 2020/09/10.
//

#include "SimpleSynthParameters.h"

OscillatorParameters::OscillatorParameters(AudioParameterFloat *sineWaveLevel, AudioParameterFloat *sawWaveLevel, AudioParameterFloat *triWaveLevel,
                                           AudioParameterFloat *squareWaveLevel, AudioParameterFloat *noiseLevel)
    : SineWaveLevel(sineWaveLevel),
      SawWaveLevel(sawWaveLevel),
      TriWaveLevel(triWaveLevel),
      SquareWaveLevel(squareWaveLevel),
      NoiseLevel(noiseLevel) {}

void OscillatorParameters::addAllParameters(AudioProcessor &processor) {
  processor.addParameter(SineWaveLevel);
  processor.addParameter(SawWaveLevel);
  processor.addParameter(TriWaveLevel);
  processor.addParameter(SquareWaveLevel);
  processor.addParameter(NoiseLevel);
}

void OscillatorParameters::saveParameters(XmlElement &xml) {
  xml.setAttribute(SineWaveLevel->paramID, (double)SineWaveLevel->get());
  xml.setAttribute(SawWaveLevel->paramID, (double)SawWaveLevel->get());
  xml.setAttribute(TriWaveLevel->paramID, (double)TriWaveLevel->get());
  xml.setAttribute(SquareWaveLevel->paramID, (double)SquareWaveLevel->get());
  xml.setAttribute(NoiseLevel->paramID, (double)NoiseLevel->get());
}

void OscillatorParameters::loadParameters(XmlElement &xml) {
  *SineWaveLevel = (float)xml.getDoubleAttribute(SineWaveLevel->paramID, 1.0);
  *SawWaveLevel = (float)xml.getDoubleAttribute(SawWaveLevel->paramID, 1.0);
  *TriWaveLevel = (float)xml.getDoubleAttribute(TriWaveLevel->paramID, 1.0);
  *SquareWaveLevel = (float)xml.getDoubleAttribute(SquareWaveLevel->paramID, 1.0);
  *NoiseLevel = (float)xml.getDoubleAttribute(NoiseLevel->paramID, 1.0);
}

AmpEnvelopeParameters::AmpEnvelopeParameters(AudioParameterFloat *attack, AudioParameterFloat *decay, AudioParameterFloat *sustain,
                                             AudioParameterFloat *release)
    : Attack(attack), Decay(decay), Sustain(sustain), Release(release) {}

void AmpEnvelopeParameters::addAllParameters(AudioProcessor &processor) {
  processor.addParameter(Attack);
  processor.addParameter(Decay);
  processor.addParameter(Sustain);
  processor.addParameter(Release);
}

void AmpEnvelopeParameters::loadParameters(XmlElement &xml) {
  //    *Attack = xml.getDoubleAttribute()
}

void AmpEnvelopeParameters::saveParameters(XmlElement &xml) {
  xml.setAttribute(Attack->paramID, (double)Attack->get());
  xml.setAttribute(Decay->paramID, (double)Decay->get());
  xml.setAttribute(Sustain->paramID, (double)Sustain->get());
  xml.setAttribute(Release->paramID, (double)Release->get());
}

LfoParameters::LfoParameters(AudioParameterChoice *lfoTarget, AudioParameterChoice *lfoWaveType, AudioParameterFloat *lfoAmount,
                             AudioParameterFloat *lfoSpeed)
    : LfoTarget(lfoTarget), LfoWaveType(lfoWaveType), LfoAmount(lfoAmount), LfoSpeed(lfoSpeed) {}

void LfoParameters::addAllParameters(AudioProcessor &processor) {}

void LfoParameters::saveParameters(XmlElement &xml) {}

void LfoParameters::loadParameters(XmlElement &xml) {}

FilterParameters::FilterParameters(AudioParameterChoice *type, AudioParameterFloat *frequency, AudioParameterFloat *q)
    : Type(type), Frequency(frequency), Q(q) {}

void FilterParameters::addAllParameters(AudioProcessor &processor) {}

void FilterParameters::saveParameters(XmlElement &xml) {}

void FilterParameters::loadParameters(XmlElement &xml) {}

ReverbParameters::ReverbParameters(AudioParameterFloat *roomSize, AudioParameterFloat *damping, AudioParameterFloat *wetLevel,
                                   AudioParameterFloat *dryLevel, AudioParameterFloat *width, AudioParameterFloat *freezeMode)
    : RoomSize(roomSize), Damping(damping), WetLevel(wetLevel), DryLevel(dryLevel), Width(width), FreezeMode(freezeMode) {}

void ReverbParameters::addAllParameters(AudioProcessor &processor) {}

void ReverbParameters::saveParameters(XmlElement &xml) {}

void ReverbParameters::loadParameters(XmlElement &xml) {}
