/*
  ==============================================================================

    AddButton.cpp
    Created: 1 Mar 2022 9:49:02pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AddButton.h"

//==============================================================================
    /******************************************
    * Name:
    *  AddButton
    * Description:
    *  constructor of AddButton, sets up the shape
    *  for the right facing triangle to be drawn by the base
    *  class.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
AddButton::AddButton(): CustomButton("btnAdd")
{
    // set up shape as a '+' symbol to represent the add
    // operation
    Path p;
    p.startNewSubPath(0.4, 0);
    p.lineTo(0.6, 0);
    p.lineTo(0.6, 0.4);
    p.lineTo(1, 0.4);
    p.lineTo(1, 0.6);
    p.lineTo(0.6, 0.6);
    p.lineTo(0.6, 1);
    p.lineTo(0.4, 1);
    p.lineTo(0.4, 0.6);
    p.lineTo(0, 0.6);
    p.lineTo(0, 0.4);
    p.lineTo(0.4, 0.4);
    p.lineTo(0.4, 0);
    setShape(p, true, true, true);
}
