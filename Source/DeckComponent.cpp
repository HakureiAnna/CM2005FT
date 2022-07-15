/*
  ==============================================================================

    DeckComponent.cpp
    Created: 1 Mar 2022 2:36:43pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckComponent.h"

//==============================================================================
/******************************************
* Name:
*  DeckComponent
* Description:
*  Constructor for the DeckComponent class. Setup members and viewport to enable
*  scrolling features.
* Parameters:
*  _formatManager: reference to global AudioFormatManager required to create new
*   DeckPlayerComponents
*  cache: reference to global AudioThumbnailCache required to draw waveform
*  tracklist: reference to global TrackCollection representing all loaded tracks
*  playerPool: reference to global PlayerPool to get DJAudioPlayer instances for use    *
* Output:
*  N/A
*******************************************/
DeckComponent::DeckComponent( AudioFormatManager& _formatManager, 
    AudioThumbnailCache& _cache, TrackCollection& _tracklist, PlayerPool& _playerPool):
    displayArea(this), tracklist(_tracklist), formatManager(_formatManager), 
    cache(_cache), playerPool{_playerPool}
{
    // add internal class instance to viewport and add it to this DeckComponent
    viewport.setViewedComponent(&displayArea, false);
    addAndMakeVisible(viewport);
}

/******************************************
* Name:
*  resized
* Description:
*  override of resized method to rescale subcomponents for proper display.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckComponent::resized()
{
    // set viewport to fill up the entire space
    viewport.setBoundsRelative(0, 0, 1, 1);
    displayArea.resized();
    auto rect = displayArea.getBounds();

    // size bounds to fit all DeckPlayerComponents
    rect.setWidth(DeckPlayerComponent::WIDTH_FIXED * deckPlayers.size());
    rect.setHeight(getLocalBounds().getHeight());

    // resize internal class instance to fit all DeckPlayerComponents
    displayArea.setBounds(rect);
}

/******************************************
* Name:
*  isInterestedInDragSource
* Description:
*  Implements virtual method of DragAndDropTarget. Always returns true since
*  this is the only DragAndDropTarget for dropping tracks
*  onto.
* Parameters:
*  src: Not used.
* Output:
*  N/A
*******************************************/
bool DeckComponent::isInterestedInDragSource(const SourceDetails& src) {
    return true;
}

/******************************************
* Name:
*  itemDropped
* Description:
*  Implements virtual method of DragAndDropTarget. When a track is dragged onto
*  this DeckComponent, create DeckPlayerComponent for it.
* Parameters:
*  src: id of the track to create a DeckPlayerComponent for.
* Output:
*  N/A
*******************************************/
void DeckComponent::itemDropped(const SourceDetails& src) {
    // extract id and create new DeckPlayerComponent for track with given id
    auto id = (int)src.description;
    loadPlayer(id);
}

/******************************************
* Name:
*  changeListenerCallback
* Description:
*  Implements the virtual method of ChangeListener, used to perform
*  teardown when removing a DeckPlayerCompoennt.
* Parameters:
*  src: Source of the change, in this case a DeckPlayerComponent.
* Output:
*  N/A
*******************************************/
void DeckComponent::changeListenerCallback(ChangeBroadcaster* src) {
    // extract DeckPlayerComponent and get relevant track
    auto deckPlayer = (DeckPlayerComponent*)src;
    auto track = deckPlayer->getTrack();

    // release DJAudioPlayer instance back to pool
    playerPool.releasePlayer(track->unload());

    // remove DeckComponentPlayer from both internal class instance and pointer array
    displayArea.removeChildComponent(deckPlayer);
    deckPlayers.removeObject(deckPlayer, true);

    // call resized to update display
    resized();
}

/******************************************
* Name:
*  loadPlayer
* Description:
*  Create new DeckPlayerComponent and load it.
* Parameters:
*  id - ID of track to load.
* Output:
*  N/A
*******************************************/
void DeckComponent::loadPlayer(int id) {
    // obtain track from TrackCollection
    auto track = tracklist.getTrack(id);

    // if track is not loaded...
    if (!track->isLoaded()) {
        // get an available DJAudioPlayer from PlayerPool
        auto audioPlayer = playerPool.getAvailablePlayer();

        // if no DJAudioPlayer available, return
        if (!audioPlayer) {
            AlertWindow::showMessageBoxAsync(MessageBoxIconType::WarningIcon,
                "Error",
                "No deck players are available, please close one of the existing deck players before loading a new track.",
                "OK");
            return;
        }

        // associate obtained DJAudioPlayer with track
        track->load(audioPlayer);

        // create new DeckPlayerComponent
        auto player = new DeckPlayerComponent(track, formatManager, cache);

        // add DeckComponent as listener to new DeckPlayerComponent
        player->addChangeListener(this);

        // add player to display area and pointer area
        deckPlayers.add(player);
        displayArea.addAndMakeVisible(player);

        // call resized to refresh display
        resized();
    }
}

/******************************************
* Name:
*  DeckDisplayAreaComponent
* Description:
*  Constructor for the DeckDisplayAreaComponent class. Simply keeps a copy of the
*  parent DeckComponent to get access to all the DeckPlayerComponents.
* Parameters:
*  parent: the parent DeckComponent
* Output:
*  N/A
*******************************************/
DeckComponent::DeckDisplayAreaComponent::DeckDisplayAreaComponent(DeckComponent *_parent): 
    parent(_parent) {}

/******************************************
* Name:
*  resized
* Description:
*  override of base class method. Properly position and size the
*  DeckPlayerComponents when resized.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckComponent::DeckDisplayAreaComponent::resized() {
    // get bounds for the DeckComponent
    auto area = getLocalBounds();

    // get number of loaded DeckPlayerComponents
    auto n = parent->deckPlayers.size();

    // compute new width to fit all players
    auto w = DeckPlayerComponent::WIDTH_FIXED;
    auto h = area.getHeight();
    // update bounds for each player
    for (auto i = 0; i < n; ++i) {
        parent->deckPlayers[i]->setBounds(i * w, 0, w, h);
    }
}