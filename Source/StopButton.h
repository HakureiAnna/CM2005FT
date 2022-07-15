/*
  ==============================================================================

    StopButton.h
    Created: 1 Mar 2022 9:10:57pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

#include "CustomButton.h"

//==============================================================================
/*
*/
class StopButton  : public CustomButton
{
public:
    // constructors & destructors
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
    StopButton();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StopButton)
};
