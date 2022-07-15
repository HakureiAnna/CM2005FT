/*
  ==============================================================================

    WaveformDisplayPlayhead.cpp
    Created: 4 Mar 2022 3:25:49pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplayPlayhead.h"

//==============================================================================
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
WaveformDisplayPlayhead::WaveformDisplayPlayhead(Track* _track): position(0),
    track(_track)
{
   // set custom look and feel 
    setLookAndFeel(&lookAndFeel);

    // add self as mouse listener
    addMouseListener(this, false);
}

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
WaveformDisplayPlayhead::~WaveformDisplayPlayhead()
{
    // release reference to custom LookAndFeel
    setLookAndFeel(nullptr);

    // remove mouse listener
    removeMouseListener(this);
}

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
void WaveformDisplayPlayhead::paint (juce::Graphics& g)
{
    // get and set playhead colour
    Colour c = getLookAndFeel().findColour(OtoDecksLookAndFeel::playheadColourId);
    g.setColour(Colour::fromRGBA(c.getRed(), c.getGreen(), c.getBlue(), 127));
    auto windowWidth = getWidth()/ N_WINDOW;
    
    // draw playhead
    g.fillRect(position * getWidth() - windowWidth/2, 0, windowWidth, getHeight());
}

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
void WaveformDisplayPlayhead::mouseDown(const MouseEvent& event) {
    // update playhead position with mouse x
    setPositionWithMouseX(event.x);
}

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
void WaveformDisplayPlayhead::mouseDrag(const MouseEvent& event) {
    // update playhead position with mouse x
    setPositionWithMouseX(event.x);
}

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
void WaveformDisplayPlayhead::setPosition(double pos) {
    // set relative position
    position = pos;
}

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
void WaveformDisplayPlayhead::setPositionWithMouseX(int x) {
    // compute relative position from mouses x and component width
    position = (float)x / getWidth();

    // update track position
    track->setPositionRelative(position);
}