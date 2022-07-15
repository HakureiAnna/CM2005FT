/*
  ==============================================================================

    CustomButton.h
    Created: 1 Mar 2022 9:17:07pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

#include "OtoDecksLookAndFeel.h"

//==============================================================================
/*
*/
class CustomButton  : public ShapeButton
{
public:
    // constructors & destructors
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
    CustomButton(String bName, String tooltip="");


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
    ~CustomButton();

    // public constants
    static const int WIDTH = 1; // relative full width of the custom shape
    static const int HEIGHT = 1;    // relative full heihgt of the custom shape

private:
    // GUI related members
    OtoDecksLookAndFeel lookAndFeel;    // custom LookAndFeel

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomButton)
};
