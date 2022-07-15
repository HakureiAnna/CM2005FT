/*
  ==============================================================================

    AddButton.h
    Created: 1 Mar 2022 9:49:02pm
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
class AddButton  : public CustomButton
{
public:

    // constructors & destructors
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
    AddButton();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AddButton)
};
