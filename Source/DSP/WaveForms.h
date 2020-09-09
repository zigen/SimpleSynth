//
// Created by zigen on 2020/09/10.
//

#ifndef SIMPLESYNTH_WAVEFORMS_H
#define SIMPLESYNTH_WAVEFORMS_H

#include <JuceHeader.h>

class WaveForms {
public:
    float sine(float angle);

    float saw(float angle);

    float square(float angle);

    float triangle(float angle);

    float noise();

private:
    Random whiteNoise;
};


#endif //SIMPLESYNTH_WAVEFORMS_H
