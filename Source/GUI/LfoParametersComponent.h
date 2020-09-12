//
// Created by zigen on 2020/09/13.
//

#ifndef SIMPLESYNTH_LFOPARAMETERSCOMPONENT_H
#define SIMPLESYNTH_LFOPARAMETERSCOMPONENT_H

#include <JuceHeader.h>
#include "../DSP/SimpleSynthParameters.h"

class LfoParametersComponent : public Component, Slider::Listener, ComboBox::Listener, private Timer {
public:
    LfoParametersComponent(LfoParameters *lfoParams);

    virtual ~LfoParametersComponent();

    virtual void paint(Graphics &g) override;

    virtual void resized() override;

private:
    LfoParametersComponent();

    virtual void sliderValueChanged(Slider *slider) override;

    virtual void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;

    virtual void timerCallback() override;

    LfoParameters *_lfoParamsPtr;

    ComboBox targetSelector;
    ComboBox waveTypeSelector;

    Slider amountSlider;
    Slider speedSlider;

    Label targetLabel;
    Label waveTypeLabel;
    Label amountLabel;
    Label speedLabel;
};


#endif //SIMPLESYNTH_LFOPARAMETERSCOMPONENT_H
