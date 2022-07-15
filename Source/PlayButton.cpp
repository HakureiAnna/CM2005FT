/*
  ==============================================================================

    PlayButton.cpp
    Created: 1 Mar 2022 8:50:46pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayButton.h"

//==============================================================================
/******************************************
* Name:
*  PlayButton
* Description:
*  PlayButton constructor. Sets up shape for the play
*  operation.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
PlayButton::PlayButton(): 
    CustomButton("btnPlay")
{
    // set up shape as right facing triangle to represent
    // play operation.
    Path p;
    p.startNewSubPath(0, 1);
    p.lineTo(1, 0.5);
    p.lineTo(0, 0);
    p.lineTo(0, 1);
    setShape(p, true, true, true);
}
