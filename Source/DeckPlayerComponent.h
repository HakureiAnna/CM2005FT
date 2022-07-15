/*
  ==============================================================================

    DeckPlayerComponent.h
    Created: 1 Mar 2022 4:08:32pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

#include "PlayButton.h"
#include "PauseButton.h"
#include "StopButton.h"
#include "PowerButton.h"
#include "FastFowardButton.h"
#include "FastReverseButton.h"
#include "CustomSlider.h"
#include "FrequencyDisplay.h"
#include "WaveformDisplay.h"
#include "Track.h"

class DeckComponent;

//==============================================================================
/*
*/
class DeckPlayerComponent  : public  Component,
    public ChangeBroadcaster,
    public Timer
{
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  DeckPlayerComponent
    * Description:
    *  constructor for the DeckPlayerComponent. Used to initialize
    *  and setup the GUI components, start timer running.
    * Parameters:
    *  track: pointer to Track that this player will player
    *  _formatManager: reference of global AudioFormatManager
    *  _cache: reference of global AudioThumbnailCache
    * Output:
    *  N/A
    *******************************************/
    DeckPlayerComponent(Track *track, 
        AudioFormatManager& _formatManager,
        AudioThumbnailCache& _cache);

    /******************************************
    * Name:
    *  ~DeckPlayerComponent
    * Description:
    *  Destructor for the DeckPlayerComponent. Used to properly cleanup.
    *  Stops the timer and removes all attached ChangeListeners
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    ~DeckPlayerComponent();

    // base class overides
    /******************************************
    * Name:
    * paint
    * Description:
    *  override of the base class's paint method. Draws a border
    *  around the component.
    * Parameters:
    *  g: reference to Graphics used to perform drawing
    * Output:
    *  N/A
    *******************************************/
    void paint (juce::Graphics& g) override;

    /******************************************
    * Name:
    *  resized
    * Description:
    *  override of base class's resized method. Used to 
    *  properly resize subcomponents.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void resized() override;

    // Timer overides
    /******************************************
    * Name:
    *  timerCallback
    * Description :
    *  implementation of the virtual timerCallback method.
    *  The method checks if track has finished playing, reset 
    *  buttons and track if so and updates frequencyDisplay
    *  and waveformDisplay.
    * Parameters :
    *  N/A 
    * Output :
    *  N/A
    *******************************************/
    void timerCallback() override;

    // event handlers
    /******************************************
    * Name:
    *  playButtonClicked
    * Description:
    *  Event handler for when the play button is pressed.
    *  Starts the track playing, disables the play buton while
    *  enabling the pause and stop buttons.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void playButtonClicked();

    /******************************************
    * Name:
    *  pauseButtonClicked
    * Description:
    *  Event handler for when the pause button is pressed.
    *  Pauses a playing track, enables the play and stop button while
    *  disabling the pause button.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void pauseButtonClicked();

    /******************************************
    * Name:
    *  stopButtonClicked
    * Description:
    *  Event handler for when the stop button is pressed.
    *  Stops a playing track, disables the pause and stop buttons while
    *  enabling the play button.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void stopButtonClicked();

    /******************************************
    * Name:
    *  powerButtonPresed
    * Description:
    *  Event handler for when power button is pressed.
    *  Disassociate frequency display from track and send
    *  message to deck component to start clean up.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void powerButtonClicked();

    /******************************************
    * Name:
    *  fastForwardButtonClicked
    * Description:
    *  Event handler for when fast forward button is pressed.
    *  Fast forward track by an amount dependent on playback speed.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void fastForwardButtonClicked();

    /******************************************
    * Name:
    *  fastReverseButtonClicked
    * Description:
    *  Event handler for when fast reverse button is pressed.
    *  Fast reverse track by an amount dependent on playback speed.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void fastReverseButtonClicked();

    /******************************************
    * Name:
    *  volumeSliderChanged
    * Description:
    *  Event handler for when volume slider's value is changed.
    *  Updates the track's volume.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void volumeSliderChanged();

    /******************************************
    * Name: 
    *  speedSliderChanged
    * Description:
    *  Event handler for when the speed slider's value is changed.
    *  Updates the track's playback speed.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void speedSliderChanged();

    /******************************************
    * Name:
    *  filterSliderChanged
    * Description:
    *  Event handler for when filter slider's value is changed.
    *  Update the bandwidth range of the track.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void filterSliderChanged();

    // methods
    /******************************************
    * Name:
    *  getTrack
    * Description:
    *  Getter for the deck player component's associated track. Used
    *  in deck component for clean up.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    Track* getTrack();

    /******************************************
    * Name:
    *  updateButtons
    * Description:
    *  Updates the play, pause and stop button's enabledness.
    * Parameters:
    *  enablePlay: if to enable the play button
    *  enablePause: if to enable the pause button
    *  enableStop: if to enable the stop button
    * Output:
    *  N/A
    *******************************************/
    void updateButtons(bool enablePlay, bool enablePause, bool enableStop);

    // public constants
    static const int WIDTH_FIXED = 522; // fixed width for the deck player component
    static const int WIDTH_BUTTON = 40; // width of a button
    static const int HEIGHT_ROTARY_SLIDER = 100;    // height of a rotary slider
    static const int HEIGHT_SLIDER = 30;    // height of a horizontal slider
    static const int HEIGHT_BUTTON = 30;    // height of a button
    static const int PADDING = 5;   // padding between component edge and sub components
    static const int REFRESH_FREQUENCY = 60;    // refresh frequency of timer

private:
    // functionality members
    Track* track;   // pointer to associated track

    // GUI members
    Label lblTrack; // label to display track name
    FastReverseButton btnFastReverse;   // fast reverse button
    PlayButton btnPlay;     // play button
    PauseButton btnPause;   // pause button
    StopButton btnStop;     // stop button
    FastFowardButton btnFastForward;    // fast forward button
    PowerButton btnPower;   // power button
    CustomSlider sldFilter; // filter slider
    CustomSlider sldVolume; // volume slider
    CustomSlider sldSpeed;  // speed slider
    FrequencyDisplay frequencyDisplay;  // frequency display (FFT)
    WaveformDisplay waveformDisplay;    // waveform (time-domain) display


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckPlayerComponent)
};
