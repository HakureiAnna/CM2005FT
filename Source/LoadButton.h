/*
  ==============================================================================

    LoadButton.h
    Created: 3 Mar 2022 8:57:31pm
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
class LoadButton  : public CustomButton
{
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  LoadButton
    * Description:
    *  Constructor for the LoadButton class, sets up
    *  the shape to reprsent load operation
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    LoadButton();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoadButton)
};
