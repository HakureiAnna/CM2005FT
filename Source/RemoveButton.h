/*
  ==============================================================================

    RemoveButton.h
    Created: 1 Mar 2022 9:49:15pm
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
class RemoveButton  : public CustomButton
{
public:
    // constructors & destructors
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
    RemoveButton();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RemoveButton)
};
