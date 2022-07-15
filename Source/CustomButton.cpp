/*
  ==============================================================================

    CustomButton.cpp
    Created: 1 Mar 2022 9:17:07pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomButton.h"

//==============================================================================
/******************************************
* Name:
*  CustomButton
* Description:
*  Constructor of CustomButton class.
* Parameters:
*  bName: required parameter of ShapeButton base class constructor
*  tooltip: optional tooltip that is displayed when mouse is over button
* Output:
*  N/A
*******************************************/
CustomButton::CustomButton(String bName, String tooltip):
    ShapeButton(bName, Colours::white, Colours::white, Colours::white)
{
    // common configuration used by all custom buttons
    setLookAndFeel(&lookAndFeel);

    // get and set up colours for the button from the custom LookAndFeel
    setColours(
        getLookAndFeel().findColour(OtoDecksLookAndFeel::normalColourId),
        getLookAndFeel().findColour(OtoDecksLookAndFeel::highlightColourId),
        getLookAndFeel().findColour(OtoDecksLookAndFeel::downColourId));

    // default outline and border for the button
    setOutline(getLookAndFeel().findColour(TextButton::buttonColourId), 1);
    setBorderSize(BorderSize<int>(2));

    // set tooltip
    setTooltip(tooltip);
}


/******************************************
* Name:
*  ~CustomButton
* Description:
*  Destructor for CustomButton. This is necessary to set LookAndFeel to nullptr in
*  order to avoid dangling references.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
CustomButton::~CustomButton() {
    // release reference to custom LookAndFeel
    setLookAndFeel(nullptr);
}