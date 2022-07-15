/*
  ==============================================================================

    StopButton.cpp
    Created: 1 Mar 2022 9:10:57pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "StopButton.h"

//==============================================================================
/******************************************
* Name:
*  StopButton
* Description:
*  Constructor for the StopButton class. Sets up shape with
*  a square to represent the stop operation.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
StopButton::StopButton() : CustomButton("btnStop")
{
    // set up shape as a filled square to represent the
    // stop operation.
    Path p;
    p.startNewSubPath(0.25, 0.25);
    p.lineTo(0.25, 0.75);
    p.lineTo(0.75, 0.75);
    p.lineTo(0.75, 0.25);
    p.lineTo(0.25, 0.25);
    setShape(p, true, true, true);
}