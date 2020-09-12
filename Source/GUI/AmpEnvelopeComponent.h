//
// Created by zigen on 2020/09/13.
//

#ifndef SIMPLESYNTH_AMPENVELOPECOMPONENT_H
#define SIMPLESYNTH_AMPENVELOPECOMPONENT_H


#include <JuceHeader.h>
#include "../DSP/SimpleSynthParameters.h"

class AmpEnvelopeParametersComponent : public Component, Slider::Listener, private Timer {
public:
    AmpEnvelopeParametersComponent(AmpEnvelopeParameters *ampEnvParams);

    virtual ~AmpEnvelopeParametersComponent();

    virtual void paint(Graphics &g) override;

    virtual void resized() override;

private:
    AmpEnvelopeParametersComponent();

    virtual void sliderValueChanged(Slider *slider) override;

    virtual void timerCallback() override;

    AmpEnvelopeParameters *_ampEnvParamsPtr;

    Slider attackSlider;
    Slider decaySlider;
    Slider sustainSlider;
    Slider releaseSlider;

    Label attackLabel;
    Label decayLabel;
    Label sustainLabel;
    Label releaseLabel;
};


#endif //SIMPLESYNTH_AMPENVELOPECOMPONENT_H
