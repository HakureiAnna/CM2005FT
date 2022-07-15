/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 18 Jan 2022 12:03:01pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

class OtoDecksLookAndFeel : public LookAndFeel_V4 {
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  OtoDecksLookAndFeel
    * Description:
    *  Constructor for the OtoDecksLookAndFeel class. used to set colours for the custom colour ids
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    OtoDecksLookAndFeel();

    // enum representing custom colour ids (not used by juce)
    enum ColourIds {
        normalColourId = 0x20000001,    // button normal colour id
        highlightColourId = 0x20000002, // button highlight (hover) colour id
        downColourId = 0x20000004,      // botton down (pressed) colour id
        waveformColourId = 0x20000008,  // time-domain waveform colour id
        playheadColourId = 0x20000010   // time-domain waveform playhead colour id
    };

};