/*
  ==============================================================================

    Track.cpp
    Created: 3 Mar 2022 1:58:15pm
    Author:  Anna

  ==============================================================================
*/

#include "Track.h"

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
Track::Track(String _fullPath, AudioFormatManager &formatManager):
    fullPath(_fullPath), loaded{ false } {
    // create URL from the full path
    auto audioURL = URL(File(fullPath));
    // generate a reader to obtain total track duration
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    duration = reader->lengthInSamples / reader->sampleRate;
    delete reader;
}

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
void Track::setPositionRelative(double position) {
    audioPlayer->setPositionRelative(position);
}

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
void Track::setSpeed(double ratio) {
    audioPlayer->setSpeed(ratio);
}

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
void Track::setVolume(double volume) {
    audioPlayer->setGain(volume);
}

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
void Track::setFrequencyRange(double fLow, double fHigh) {
    audioPlayer->setCutoffFrequency(fLow, fHigh);
}

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
void Track::setFrequencyDisplay(FrequencyDisplay* frequencyDisplay) {
    audioPlayer->setFrequencyDisplay(frequencyDisplay);
}

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
String Track::getFileName() {
    return fullPath.substring(fullPath.lastIndexOf(File::getSeparatorString())+1);
}

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
String Track::getFullPath() {
    return fullPath;
}

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
double Track::getDuration() {
    return duration;
}

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
String Track::getDurationAsString() {
    // compute individual seconds, minutes and hours
    int hrs = (int)duration / 3600;
    int min = (int)duration / 60;
    int sec = (int)duration % 60;

    // format duration as string
    return String::formatted("%02d:%02d:%02d", hrs, min, sec);
}

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
double Track::getPositionRelative() {
    return audioPlayer->getPositionRelative();
}

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
bool Track::isLoaded() {
    return loaded;
}

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
bool Track::isMatch(String keyword) {
    // convert filename to lowercase and return result of comparison to lowercase of keyword
    auto filename = getFileName().toLowerCase();
    return filename.contains(keyword.toLowerCase());
}

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
void Track::play() {
    audioPlayer->start();
}

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
void Track::pause() {
    audioPlayer->stop();
}

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
void Track::stop() {
    audioPlayer->rewind();
}

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
void Track::load(DJAudioPlayer *_player) {
    // associate DJAudioPlayer
    audioPlayer = _player;

    // load the track into the audio player
    audioPlayer->loadURL(URL{ File{fullPath} });
    audioPlayer->setPositionRelative(0.000001);

    // update flag
    loaded = true;


    // send message to all change listeners (playlist)
    sendChangeMessage();
}

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
int Track::unload() {
    // stop playback
    stop();

    // update flag
    loaded = false;

    // send message to all change listener (playlist)
    sendChangeMessage();

    // return player id for further clean up
    return audioPlayer->getID();
}

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
void Track::fastForward() {
    audioPlayer->fastForward();
}

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
void Track::fastReverse() {
    audioPlayer->fastReverse();
}
