/*
  ==============================================================================

    FastFowardButton.cpp
    Created: 4 Mar 2022 3:43:50pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FastFowardButton.h"

//==============================================================================
/******************************************
* Name:
*  FastForwardButton
* Description:
*  constructor to setup shape for fast forward button
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
FastFowardButton::FastFowardButton(): CustomButton("btnFastForward")
{
    // set shape to two right facing triangles and a thin
    // vertical rectangle reprsenting fast forward operation
    Path p;
    p.startNewSubPath(0, 0);
    p.lineTo(0.4, 0.5);
    p.lineTo(0, 1);
    p.lineTo(0, 0);
    p.startNewSubPath(0.4, 0);
    p.lineTo(0.8, 0.5);
    p.lineTo(0.4, 1);
    p.lineTo(0.4, 0);
    p.addRectangle(0.8, 0.15, 0.2, 0.7);
    setShape(p, true, true, true);
}