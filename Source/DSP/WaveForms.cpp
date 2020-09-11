//
// Created by zigen on 2020/09/10.
//

#include "WaveForms.h"

namespace {
const float HALF_PI = MathConstants<float>::halfPi;
const float ONE_PI = MathConstants<float>::pi;
const float TWO_PI = MathConstants<float>::twoPi;
}  // namespace

float WaveForms::sine(float angle) {
  if (angle > TWO_PI) {
    angle = fmodf(angle, TWO_PI);
  }
  return sinf(angle);
}

float WaveForms::saw(float angle) {
  if (angle > TWO_PI) {
    angle = fmodf(angle, TWO_PI);
  }

  if (angle <= ONE_PI) {
    return (angle / ONE_PI);
  } else {
    return -2.0f + (angle / ONE_PI);
  }
}

float WaveForms::triangle(float angle) {
  if (angle > TWO_PI) {
    angle = fmodf(angle, TWO_PI);
  }

  if (angle <= HALF_PI) {
    return (angle / HALF_PI);
  } else if (angle > HALF_PI && angle <= (ONE_PI + HALF_PI)) {
    return 2.0f - (2.0f * angle / ONE_PI);
  } else {
    return -4.0f + (angle / HALF_PI);
  }
}

float WaveForms::square(float angle) {
  if (angle > TWO_PI) {
    angle = fmodf(angle, TWO_PI);
  }

  if (angle <= ONE_PI) {
    return 1.0f;
  } else {
    return -1.0f;
  }
}

float WaveForms::noise() { return (whiteNoise.nextFloat() * 2.0f - 1.0f); }
