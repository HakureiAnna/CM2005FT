/*
  ==============================================================================

    CustomSlider.cpp
    Created: 10 Mar 2022 1:45:05pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomSlider.h"

//==============================================================================
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
CustomSlider::CustomSlider(SliderStyle style, double min, double max, double interval,
    double initialValue,
    String _name, String _suffix, int _dp):
    name(_name),
    suffix(_suffix),
    dp(_dp)
{
    // set slider style and range.
    setSliderStyle(style);
    setRange(min, max, interval);

    // check if style is set to TwoValueHorizontal
    bool isTwo = style == SliderStyle::TwoValueHorizontal;

    // only set initial value if slider style is not TwoValueHorizontal,
    // this check is necessary to prevent assertion fail in debug mode
    if (!isTwo) {
        setValue(initialValue);
    }

    // set width and reserve space for text on left of slider ONLY when style is TwoValueHorizontal
    auto w = ( isTwo? WIDTH_TEXT : 0);
    auto textStyle = (isTwo ? Slider::TextBoxLeft : Slider::NoTextBox);
    setTextBoxStyle(textStyle, false, w, 0);
}

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
void CustomSlider::paint (juce::Graphics& g)
{
    // call base paint method to draw slider
    Slider::paint(g);
    
    // get total drawable area
    auto drawableArea = getLocalBounds();
    // get current font
    auto font = g.getCurrentFont();
    // compute horizontal space required for specific text
    auto w = font.getStringWidth(name);
    auto h = font.getHeight();
    std::string fmt;
    // set format string based on dp member
    switch (dp) {
    case 0:
        fmt = "%.0f";
        break;
    case 1:
        fmt = "%.1f";
        break;
    default:
        fmt = "%.2f";
    }
    auto textArea = Rectangle<float>();
    String value;
    String minVal, maxVal; 

    // perform different set up depending on style
    switch (getSliderStyle()) {
    // setup for drawing name: value suffix to the left of slider when stlye is TwoValueHorizontal
    case SliderStyle::TwoValueHorizontal:
        minVal = String::formatted(fmt, getMinValue());
        maxVal = String::formatted(fmt, getMaxValue());
        value = name + ": " + minVal + "-" + maxVal + suffix;
        w = font.getStringWidth(value);
        textArea = Rectangle<float>(0, 0, w, h);
        break;
    // setup for drawing name, value suffix to the center of slider when style is Rotary
    case SliderStyle::Rotary:
        textArea = Rectangle<float>(drawableArea.getCentreX() - w / 2,
            drawableArea.getCentreY() - h, w, h);
        g.drawText(name, textArea, Justification::topLeft);

        value = String::formatted(fmt, getValue()) + suffix;
        w = font.getStringWidth(value);
        textArea.setY(drawableArea.getCentreY() + h);
        textArea.setX(drawableArea.getCentreX() - w / 2);
        textArea.setWidth(w);
        break;
    }
    // custom drawing of text
    g.drawText(value, textArea, Justification::topLeft);

}