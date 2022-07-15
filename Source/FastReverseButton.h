/*
  ==============================================================================

    FastReverseButton.h
    Created: 4 Mar 2022 3:44:07pm
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
class FastReverseButton  : public CustomButton
{
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  FastReverseButton
    * Description:
    *  Constructor for FastReverseButton. Used to setup
    *  the custom shape for the fast reverse button.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    FastReverseButton();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FastReverseButton)
};
