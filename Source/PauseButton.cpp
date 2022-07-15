/*
  ==============================================================================

    PauseButton.cpp
    Created: 1 Mar 2022 9:10:46pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PauseButton.h"

//==============================================================================
/******************************************
* Name:
*  PauseButton
* Description:
*  Constructor for the PauseButton class. Sets up the
*  shape for the pause operation.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
PauseButton::PauseButton(): CustomButton("btnPause")
{
    // set up shape as two thin vertical rectangles to 
    // represent the pause operation
    Path p;
    Rectangle<float> r(0, 0, 0.4, 1);
    p.addRectangle(r);
    r.setX(0.6);
    p.addRectangle(r);
    setShape(p, true, true, true);
}