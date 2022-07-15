/*
  ==============================================================================

    PowerButton.h
    Created: 1 Mar 2022 9:11:09pm
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
class PowerButton  : public CustomButton
{
public:
    /******************************************
    * Name:
    *  PowerButton
    * Description:
    *  Constructor for the PowerButton class. Set up shape by
    *  incomplete curve with a vertical line at its top center
    *  to represent the power button.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    PowerButton();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PowerButton)
};
