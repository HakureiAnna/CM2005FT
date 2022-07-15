/*
  ==============================================================================

    PlayButton.h
    Created: 1 Mar 2022 8:50:46pm
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
class PlayButton  : public CustomButton
{
public:
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
    PlayButton();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayButton)
};
