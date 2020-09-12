//
// Created by zigen on 2020/09/13.
//

#ifndef SIMPLESYNTH_FILTERPARAMETERSCOMPONENT_H
#define SIMPLESYNTH_FILTERPARAMETERSCOMPONENT_H


#include <JuceHeader.h>
#include "../DSP/SimpleSynthParameters.h"

class FilterParametersComponent : public Component, Slider::Listener, ComboBox::Listener, private Timer {
public:
    FilterParametersComponent(FilterParameters *filterParams);

    virtual ~FilterParametersComponent();

    virtual void paint(Graphics &g) override;

    virtual void resized() override;

private:
    FilterParametersComponent();

    virtual void sliderValueChanged(Slider *slider) override;

    virtual void comboBoxChanged(ComboBox *comboBoxThatHasChanged) override;

    virtual void timerCallback() override;

    FilterParameters *_filterParamsPtr;

    ComboBox typeSelector;

    Slider frequencySlider;
    Slider qSlider;

    Label typeLabel;
    Label frequencyLabel;
    Label qLabel;
};

#endif //SIMPLESYNTH_FILTERPARAMETERSCOMPONENT_H
