/*
  ==============================================================================

    PowerButton.cpp
    Created: 1 Mar 2022 9:11:09pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PowerButton.h"

//==============================================================================
/******************************************
* Name:
*  PowerButton
* Description:
*  Constructor for the PowerButton class. Set up shape by
*  incomplete curve with a vertical line at its top center
*  to represent the power button.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
PowerButton::PowerButton(): CustomButton("btnPower")
{
    // set up a shape that consistent of a curve with a
    // slight opening in the top center and a vertical line
    // across the opening to represent the power button.
    Path p;
    auto r_inner = 0.4;
    auto r_outer = 1;
    auto pi = MathConstants<float>::pi;
    auto n = 12;
    auto cutoff = n / 2;
    auto n2 = n * 2;
    auto pn =  pi/ n;
    auto c = 3*pi/2 - pn*3;
    auto x = r_outer * cos(c);
    auto y = r_outer * sin(c);
    p.startNewSubPath(x, y);

    // draw outer curve
    for (auto i = 0; i < n2 -cutoff; ++i) {
        c -= pn;
        x = r_outer * cos(c);
        y = r_outer * sin(c);
        p.lineTo(x, y);
    }
    // link to inner curve
    x = r_inner * cos(c);
    y = r_inner * sin(c);
    p.lineTo(x, y);
    // draw inner curve
    for (auto i = 0; i < n2 - cutoff; ++i) {
        c += pn;
        x = r_inner * cos(c);
        y = r_inner * sin(c);
        p.lineTo(x, y);
    }
    // close the curve shape
    x = r_outer * cos(c);
    y = r_outer * sin(c);

    // draw vertical line
    p.lineTo(x, y);
    Rectangle<float> r(-0.25, -1.2, 0.5, 1);
    p.addRectangle(r);
    setShape(p, true, true, true);
}

