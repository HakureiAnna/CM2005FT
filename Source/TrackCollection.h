/*
  ==============================================================================

    TrackCollection.h
    Created: 3 Mar 2022 2:27:25pm
    Author:  Anna

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
using namespace juce;

#include "Track.h"
#include "PlayerPool.h"

class TrackCollection {
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  TrackCollection 
    * Description:
    *  constructor for the TrackCollection class.
    *  Sets up members.
    * Parameters:
    *  formatManager: reference to global AudioFormatManager
    * Output: 
    *  N/A
    *******************************************/
    TrackCollection(AudioFormatManager& formatManager);

    // getters & setters
    /******************************************
    * Name:
    *  getTrack
    * Description:
    *  getter for a Track in the collection. Track returned
    *  depends on if a search is performed. When search is active,
    *  returns the track that matches the search conditon and the id. 
    * When search is inactive, return track with given id
    * Parameters:
    *  i - ID of track to return
    * Output:
    *  pointer to request Track.
    *******************************************/
    Track* getTrack(int i);

    // methods
    /******************************************
    * Name:
    *  isKnownFormat
    * Description:
    *  Checks if the argument is a format that the
    *  AudioManager is able to process.
    * Parameters:
    *  format: format to check for
    * Output:
    *  If passed format is processable.
    *******************************************/
    bool isKnownFormat(String format);

    /******************************************
    * Name:
    *  size
    * Description:
    *  Returns the number of traks in the collection,
    *  or if search is active, the number of matching tracks
    *  to the search condition
    * Parameters:
    *  N/A
    * Output:
    *  No. of tracks or no. of matching tracks to search condition
    *******************************************/
    int size();

    /******************************************
    * Name:
    *  addTrack
    * Description:
    *  Check if the file extension of the path provided
    *  is processable by the format manager, if so, add
    *  track to the collection
    * Parameters:
    *  path: full path of track to add.
    * Output:
    *  N/A
    *******************************************/
    void addTrack(const String& path);

    /******************************************
    * Name:
    *  addTracks
    * Description:
    *  Adds an array of paths of tracks.
    *  First check, if the given track exist in the collection,
    *  If not, add the track to the collection
    * Parameters:
    *  path: array of full path of tracks to add
    * Output:
    *  N/A
    *******************************************/
    void addTracks(const StringArray& paths);

    /******************************************
    * Name:
    *  removeTrack
    * Description:
    *  remove track with given id from the collection.
    *  If search is active, return without doing anything.
    * Parameters:
    *  i: id of track to remove
    * Output:
    *  N/A
    *******************************************/
    void removeTrack(int i);

    /******************************************
    * Name:
    *  selectTracks
    * Description:
    *  perform search against all tracks in collection using
    *  isMatch of each track, on match, add track id to selectedTracks.
    * Parameters:
    * keyword: keyword used to select tracks
    * Output:
    *  no. of selected tracks
    *******************************************/
    int selectTracks(String keyword);

    /******************************************
    * Name:
    *  clearSelectedTracks 
    * Description:
    *  clear all selected tracks, and reset search active flag.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void clearSelectedTracks();

    /******************************************
    * Name:
    *  load
    * Description:
    *  Read config through ConfigManager and extract
    *  all tracks saved to restore the track list
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void load();

    /******************************************
    * Name:
    *  save
    * Description:    
    *  Parse all tracks in collection's full path
    *  into JSON format and pass to ConfigManager for
    *  saving to config file.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void save();

private:
    // functionality members
    bool tracksSearched;        // flag indicating if a search is performed
    AudioFormatManager& formatManager;  // reference to global AudioFormatManager
    OwnedArray<Track> tracks; // pointer array of all tracks in the collection
    std::vector<int> selectedTracks;    // vector of selected (matching search condition) track ids
};