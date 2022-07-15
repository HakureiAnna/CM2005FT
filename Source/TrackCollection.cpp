/*
  ==============================================================================

    TrackCollection.cpp
    Created: 3 Mar 2022 2:27:25pm
    Author:  Anna

  ==============================================================================
*/

#include "TrackCollection.h"
#include "ConfigManager.h"

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
TrackCollection::TrackCollection(AudioFormatManager& _formatManager) :
    formatManager(_formatManager),
    tracksSearched(false) {}

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
Track* TrackCollection::getTrack(int i) {
    return (tracksSearched ? tracks[selectedTracks[i]] : tracks[i]);
}

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
bool TrackCollection::isKnownFormat(String format) {
    for (auto i = 0; i < formatManager.getNumKnownFormats(); ++i) {
        for (auto f : formatManager.getKnownFormat(i)->getFileExtensions()) {
            if (f == format) {
                return true;
            }
        }
    }
    return false;
}

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
int TrackCollection::size() {
    return (tracksSearched ? selectedTracks.size() : tracks.size());
}

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
void TrackCollection::addTrack(const String &path) {
    if (isKnownFormat(File(path).getFileExtension())) {
        tracks.add(new Track(path, formatManager));
    }
}

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
void TrackCollection::addTracks(const StringArray &paths) {
    // iterate through all paths in the provided argument
    for (auto p : paths) {
        auto exists = false;
        // iterate over all existing tracks in collection
        for (auto i = 0; i < tracks.size(); ++i) {
            if (tracks[i]->getFullPath() == p) {
                exists = true;
                break;
            }
        }
        // if new path not found in collection, add it to collection
        if (!exists) {
            addTrack(p);
        }
    }
    DBG(tracks.size());
}

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
void TrackCollection::removeTrack(int i) {
    // if search is currently active, return
    if (tracksSearched) {
        return;
    }
    tracks.remove(i);
}

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
int TrackCollection::selectTracks(String keyword) {
    tracksSearched = true;
    selectedTracks.clear();
    // iterate over all tracks in collection
    for (auto i = 0; i < tracks.size(); ++i) {
        // if match keyword, add to selected tracks
        if (tracks[i]->isMatch(keyword)) {
            selectedTracks.push_back(i);
        }
    }
    return selectedTracks.size();
}

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
void TrackCollection::clearSelectedTracks() {
    tracksSearched = false;
    selectedTracks.clear();
}

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
void TrackCollection::load() {
    // read from config file
    var config = ConfigManager::load();
    if (config.isBool() && (bool)config == false) {
        return;
    }
    // extract relevant property
    auto trackList = config.getProperty("tracks", var()).getArray();
    // iterate over all tracks read from config, add to collection
    for (auto track : *trackList) {
        addTrack(track["path"]);
    }
}

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
void TrackCollection::save() {
    var TrackList;
    Array<var> trackList;
    var config(new DynamicObject());
    // iterate over all tracks in collection and add to JSON object in correct format
    for (auto i = 0; i < tracks.size(); ++i) {
        var curr(new DynamicObject());
        curr.getDynamicObject()->setProperty("path", tracks[i]->getFullPath());
        trackList.add(curr);
    }
    // save to JSON object
    config.getDynamicObject()->setProperty("tracks", trackList);
    // write to file using ConfigManager
    ConfigManager::save(config);
}