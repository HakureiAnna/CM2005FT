/*
  ==============================================================================

    OtoDecksLookAndFeel.cpp
    Created: 2 Mar 2022 1:37:11pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OtoDecksLookAndFeel.h"

//==============================================================================
/******************************************
* Name:
*  OtoDecksLookAndFeel
* Description:
*  Constructor for the OtoDecksLookAndFeel class. used to set colours for the custom colour ids
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
OtoDecksLookAndFeel::OtoDecksLookAndFeel()
{   
    // set colours for each defined custom colour id
    setColour(normalColourId, Colours::lightgrey);
    setColour(highlightColourId, Colours::white);
    setColour(downColourId, Colours::lightgreen);

    setColour(waveformColourId, Colours::orange);
    setColour(playheadColourId, Colours::green);
}
