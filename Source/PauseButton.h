/*
  ==============================================================================

    PauseButton.h
    Created: 1 Mar 2022 9:10:46pm
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
class PauseButton  : public CustomButton
{
public:
    // constructors & destructors
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
    PauseButton();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PauseButton)
};
