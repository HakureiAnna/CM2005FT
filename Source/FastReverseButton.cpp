/*
  ==============================================================================

    FastReverseButton.cpp
    Created: 4 Mar 2022 3:44:07pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FastReverseButton.h"

//==============================================================================
    /******************************************
    * Name:
    *  FastReverseButton
    * Description:
    *  Constructor for FastReverseButton. Used to setup
    *  the custom shape for the fast reverse button.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
FastReverseButton::FastReverseButton(): CustomButton("btnFastReverse")
{
    // set shape to two left facing triangles with a 
    // thin vertical rectangle to the left to represent the
    // fast reverse operation
    Path p;
    p.startNewSubPath(0.2, 0.5);
    p.lineTo(0.6, 0);
    p.lineTo(0.6, 1);
    p.lineTo(0.2, 0.5);
    p.startNewSubPath(0.6, 0.5);
    p.lineTo(1, 0);
    p.lineTo(1, 1);
    p.lineTo(0.6, 0.5);
    p.addRectangle(0, 0.15, 0.2, 0.7);
    setShape(p, true, true, true);
}