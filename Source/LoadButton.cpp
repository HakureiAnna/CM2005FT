/*
  ==============================================================================

    LoadButton.cpp
    Created: 3 Mar 2022 8:57:31pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LoadButton.h"

//==============================================================================
/******************************************
* Name:
*  LoadButton
* Description:
*  Constructor for the LoadButton class, sets up
*  the shape to reprsent load operation
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
LoadButton::LoadButton(): CustomButton("btnLoad",
    "Load track in new deck.")
{
    // set up a CD like shape consisting of two circles
    // to represent the load operation
    auto r_inner = 0.4;
    auto r_outer = 1;
    Path p = p;
    auto pi = MathConstants<float>::pi;
    p.addEllipse(0, 0, r_outer, r_outer);

    auto offset = (r_outer - r_inner) / 2;
    p.addEllipse(offset, offset, r_inner, r_inner);
    setShape(p, true, true, true);
}