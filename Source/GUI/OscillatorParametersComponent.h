//
// Created by zigen on 2020/09/13.
//

#ifndef SIMPLESYNTH_OSCILLATORPARAMETERSCOMPONENT_H
#define SIMPLESYNTH_OSCILLATORPARAMETERSCOMPONENT_H

#include <JuceHeader.h>
#include "../DSP/SimpleSynthParameters.h"

class OscillatorParametersComponent : public Component, Slider::Listener, private Timer {
public:
    OscillatorParametersComponent(OscillatorParameters *oscParams);

    virtual ~OscillatorParametersComponent();

    virtual void paint(Graphics &g) override;

    virtual void resized() override;

private:
    OscillatorParametersComponent();

    virtual void sliderValueChanged(Slider *slider) override;

    virtual void timerCallback() override;

    OscillatorParameters *_oscParamsPtr;

    Slider sineWaveLevelSlider;
    Slider sawWaveLevelSlider;
    Slider triWaveLevelSlider;
    Slider squareWaveLevelSlider;
    Slider noiseLevelSlider;

    Label sineWaveLevelLabel;
    Label sawWaveLevelLabel;
    Label triWaveLevelLabel;
    Label squareWaveLevelLabel;
    Label noiseLevelLabel;
};

#endif //SIMPLESYNTH_OSCILLATORPARAMETERSCOMPONENT_H
