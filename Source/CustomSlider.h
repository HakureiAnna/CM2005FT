/*
  ==============================================================================

    CustomSlider.h
    Created: 10 Mar 2022 1:45:05pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

//==============================================================================
/*
*/
class CustomSlider  : public Slider {
public:
    // constructors and destructors
    /******************************************
    * Name:
    *  CustomSlider
    * Description:
    *  constructor for the CustomSlider.
    * Parameters:
    *  style: the SliderStyle to use for this slider
    *  min: minimum value of the range for this slider
    *  max: maximum value of the range for this slider
    *  interval: minimum delta/ step when using the slider
    *  initialValue: value to initialize slider to (only applicable for single value slider)
    *  name: name of the slider, used when doing custom drawing (instead of using a Label)
    *  suffix: the suffix for the value (unit) used for custom drawing
    *  dp: decimal place to show value by during custom drawing
    * Output:
    *  N/A
    *******************************************/
    CustomSlider(SliderStyle style, double min, double max, double interval,
        double initialValue,
        String name, String suffix="", int dp=2);

    // function overrides
    /******************************************
    * Name:
    *  paint
    * Description:
    *  override of the paint function. Used to call paint() of base class and 
    *  perform custom drawing of name, value and suffix.
    * Parameters:
    *  g: the Graphics reference passed to perform drawing
    * Output:
    * n/A
    *******************************************/
    void paint (juce::Graphics& g) override;

    // public constants
    static const int WIDTH_TEXT=150; // horizontal space reserved for outputing text

private:
    // data members
    String name;    // name of the slider
    String suffix;  // suffix (unit) of value 
    int dp;         // decimal places

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSlider)
};
