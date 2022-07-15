/*
  ==============================================================================

    FastFowardButton.h
    Created: 4 Mar 2022 3:43:50pm
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
class FastFowardButton  : public CustomButton
{
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  FastForwardButton
    * Description:
    *  constructor to setup shape for fast forward button
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    FastFowardButton();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FastFowardButton)
};
