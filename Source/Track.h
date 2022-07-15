/*
  ==============================================================================

    Track.h
    Created: 3 Mar 2022 1:58:15pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

#include "DJAudioPlayer.h"
#include "FrequencyDisplay.h"

class Track: public ChangeBroadcaster {
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  Track
    * Description:
    *  constructor of the Track class. Initializes the
    *  various properties. Get track duration using a reader
    *  obtained from the AudioFormatManager.
    * Parameters:
    *  fullPath: full path of the track
    *  formatManager: reference to global AudioFormatManager
    * Output:
    *  N/A
    *******************************************/
    Track(String fullPath, AudioFormatManager& formatManager);

    // getters & setters
    /******************************************
    * Name:
    *  setPositionRelative
    * Description:
    *  Setter for the relative (0.0-1.0) of the playback position
    *  by passing to the associated player.
    * Parameters:
    *  position: relative playback position (0.0-1.0)
    * Output:
    *  N/A
    *******************************************/
    void setPositionRelative(double position);

    /******************************************
    * Name:
    *  setSpeed
    * Description:
    *  setter for the playback speed by passing to 
    *  associated player.
    * Parameters:
    *  ratio: playback speed
    * Output:
    *  N/A
    *******************************************/
    void setSpeed(double ratio);

    /******************************************
    * Name:
    *  setVolume
    * Description:
    *  setter for the playback volume, passes to the
    *  player.
    * Parameters:
    *  volume: playback volume
    * Output:
    *  N/A
    *******************************************/
    void setVolume(double volume);

    /******************************************
    * Name:
    *  setFrequencyRange
    * Description:
    *  setter for the allowed bandwidth, passes to the 
    *  associated player.
    * Parameters:
    *  fLow: lower cutoff frequency
    *  fHigh: upper cutoff frequency
    * Output:
    *  N/A
    *******************************************/
    void setFrequencyRange(double fLow, double fHigh);

    /******************************************
    * Name:
    *  setFrequencyDisplay
    * Description:
    *  setter for the associated frequency display. Passes
    *  on to the associated player.
    * Parameters:
    *  frequencyDisplay: pointer to frequency display to associate
    * Output:
    *  N/A
    *******************************************/
    void setFrequencyDisplay(FrequencyDisplay* frequencyDisplay);

    /******************************************
    * Name:
    *  getFileName
    * Description:
    *  getter for only the filename of the track file path
    * Parameters:
    *  N/A
    * Output:
    *  filename of the track
    *******************************************/
    String getFileName();

    /******************************************
    * Name:
    *  getFullPath
    * Description:
    *  getter for the full path of the track
    * Parameters:
    *  N/A
    * Output:
    *  full path of the track
    *******************************************/
    String getFullPath();

    /******************************************
    * Name:
    *  getDuration
    * Description:
    *  getter for the total duration of the track
    * Parameters:
    *  N/A
    * Output:
    *  total duration of track
    *******************************************/
    double getDuration();

    /******************************************
    * Name:
    *  getDurationAsString
    * Description:
    *  getter for the total duration formatted as 
    *  "HH:MM:SS"
    * Parameters:
    *  N/A
    * Output:
    *  returns a formatted string of the total duration
    *******************************************/
    String getDurationAsString();

    /******************************************
    * Name:
    *  getPositionRelative
    * Description:
    *  getter for the relative playback position (0.0-1.0)
    * Parameters:
    *  N/A
    * Output:
    *  returns relative playback position
    *******************************************/
    double getPositionRelative();

    /******************************************
    * Name:
    *  isLoaded
    * Description:
    *  getter to check if the track is loaded in a deck player component
    * Parameters:
    *  N/A
    * Output:
    *  if track is loaded in a deck player  component
    *******************************************/
    bool isLoaded();

    // methods
    /******************************************
    * Name:
    *  isMatch
    * Description:
    *  check if the filename contains the keyword passed
    * Parameters:
    *  keyword: the keyword to search for in the filename
    * Output:
    *  if filename contains keyword
    *******************************************/
    bool isMatch(String keyword);

    /******************************************
    * Name:
    *  play
    * Description:
    *  Start the track playing in the underlying player.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void play();

    /******************************************
    * Name:
    *  pause
    * Description:
    *  pause the current playback through the associated player.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void pause();

    /******************************************
    * Name:
    *  stop
    * Description:
    *  stops the playback and return the start.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void stop();

    /******************************************
    * Name:
    *  load
    * Description:
    *  associate a DJAudioPlayer with the track and load
    *  the track specified in this instance. send a message
    *  so the playlist can enable/disable relevant buttons.
    * Parameters:
    *  player: the DJAudioPlayer to load the track in
    * Output:
    *  N/A
    *******************************************/
    void load(DJAudioPlayer* player);

    /******************************************
    * Name:
    *  unload
    * Description:
    *  stop playback, unset loaded flag, send message so
    *  playlist can enable/ disable relevant buttons.
    *  returns the associated player id for further cleanup.
    * Parameters:
    *  N/A
    * Output:
    *  id of the associated player.
    *******************************************/
    int unload();

    /******************************************
    * Name:
    *  fastForward
    * Description:
    *  forward playback position by an amount determined by 
    *  playback speed, passes to the player.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void fastForward();

    /******************************************
    * Name:
    *  fastReverse
    * Description:
    *  reverse playback position by an amount determined by 
    *  playback speed, passes to the player
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void fastReverse();

private:
    // functionality members
    bool loaded;    // flag indicating if the track is loaded in a deck player component
    double duration;    // total duration of track
    String fullPath;    // full path of track
    int playerId;       // associated DJAudioPlayer id
    DJAudioPlayer *audioPlayer; // pointer to associated DJAudioPlayer
};