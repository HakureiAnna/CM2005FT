/*
  ==============================================================================

    WaveformDisplayPlayhead.h
    Created: 4 Mar 2022 3:25:49pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

#include "OtoDecksLookAndFeel.h"
#include "Track.h"

//==============================================================================
/*
*/
class WaveformDisplayPlayhead  : public juce::Component,
    public MouseListener
{
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  WaveformDisplayPlayhead
    * Description:
    *  Constructor for the WaveformDisplayPlayhead class.
    *  Set up custom LookAndFeel and add self as mouse listener.
    * Parameters:
    *  track: pointer to associated track
    * Output:
    *  N/A
    *******************************************/
    WaveformDisplayPlayhead(Track *track);

    /******************************************
    * Name:
    *  ~WaveformDisplayPlayhead
    * Description:
    *  Destructor for WaveformDisplayPlayhead class. 
    *  Release reference to custom LookAndFeel.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    ~WaveformDisplayPlayhead() override;

    // base class overrides
    /******************************************
    * Name:
    *  paint
    * Description:
    *  override for base class paint method. Draw 
    *  playhead at the correct position over the 
    *  time-domain waveform display.
    * Parameters:
    *  g: reference to Graphics used for drawing.
    * Output:
    *  N/A
    *******************************************/
    void paint (juce::Graphics& g) override;

    // MouseListener overrides
    /******************************************
    * Name:
    *  mouseDown
    * Description:
    *  callback for when mouse is clicked in this component area. 
    *  Update track position using mouse horizontal position.
    * Parameters:
    *  event: reference to MouseEvent used to retrieve mouse position.
    * Output:
    *  N/A
    *******************************************/
    void mouseDown(const MouseEvent& event) override;

    /******************************************
    * Name:
    *  mouseDrag
    * Description:
    *  callback for when mouse is dragged over this component's area.
    *  Update track position using mouse horizontal position.
    * Parameters:
    *  event: reference to MouseEvent used to retrieve mouse position.
    * Output:
    *  N/A
    *******************************************/
    void mouseDrag(const MouseEvent& event) override;

    // getters & setters
    /******************************************
    * Name:
    *  setPosition
    * Description:
    *  Used to set relative position used for drawing. Called by
    *  timer callback in deck player component to update playhead during 
    *  playback
    * Parameters:
    *  position: relative position (0.0 - 1.0)
    * Output:
    *  N/A
    *******************************************/
    void setPosition(double position);

    /******************************************
    * Name:
    *  setPositonWithMouseX
    * Description:
    *  Update position using the x position of the mouse to compute
    *  relative position from component width.
    * Parameters:
    *  x: mouse x position
    * Output:
    *  N/A
    *******************************************/
    void setPositionWithMouseX(int x);

    // public constants
    static const int N_WINDOW = 128;    // divide component width into n divisions

private:
    // functionality members
    Track* track;   // pointer to associated track
    double position;    // current position to draw playhead at (relative; 0.0-1.0)

    // GUI members
    OtoDecksLookAndFeel lookAndFeel;    // custom LookAndFeel

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplayPlayhead)
};
