/*
  ==============================================================================

    RemoveButton.cpp
    Created: 1 Mar 2022 9:49:15pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RemoveButton.h"

/******************************************
* Name:
*  RemoveButton
* Description:
*  Constructor for the RemoveButton class. Setup a cross
*  shape to reprsent the remove operation.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
RemoveButton::RemoveButton() :
    CustomButton("btnRemove") {
    // set up shape as a 'X' to represent the 
    // remove operation.
    Path p;
    p.startNewSubPath(0, 0);
    p.lineTo(0.25, 0);
    p.lineTo(0.5, 0.35);
    p.lineTo(0.75, 0);
    p.lineTo(1.0, 0);
    p.lineTo(0.65, 0.5);
    p.lineTo(1, 1);
    p.lineTo(0.75, 1);
    p.lineTo(0.5, 0.65);
    p.lineTo(0.25, 1);
    p.lineTo(0, 1);
    p.lineTo(0.35, 0.5);
    p.lineTo(0, 0);
    setShape(p, true, true, true);
}