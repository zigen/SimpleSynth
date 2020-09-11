//
// Created by zigen on 2020/09/10.
//

#ifndef SIMPLESYNTH_AMPENVELOPE_H
#define SIMPLESYNTH_AMPENVELOPE_H

class AmpEnvelope {
 public:
  enum class AMPENV_STATE {
    ATTACK = 0,
    DECAY,
    SUSTAIN,
    RELEASE,
    WAIT,
  };

  AmpEnvelope(float attackTime, float decayTime, float sustain, float releaseTime);

  ~AmpEnvelope();

  AMPENV_STATE getState();

  float getValue();

  void setParameters(float attackTime, float decayTime, float sustain, float releaseTime);

  void attackStart();

  void releaseStart();

  void releaseEnd();

  bool isHolding();

  bool isReleasing();

  void cycle(float sampleRate);

 private:
  AmpEnvelope();

  AMPENV_STATE _ampState;
  float _attackTime, _decayTime, _sustainValue, _releaseTime;
  float _value, _valueOnReleaseStart;
  float _sampleRate;
};

#endif  // SIMPLESYNTH_AMPENVELOPE_H
