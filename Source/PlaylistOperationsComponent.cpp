/*
  ==============================================================================

    PlaylistOperationsComponent.cpp
    Created: 3 Mar 2022 8:57:00pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistOperationsComponent.h"

//==============================================================================
/******************************************
* Name:
*  PlaylistOperationsComponent
* Description:
*  Constructor for PlaylistOperationsComponent. initialize, add and show subcomponents.
* Parameters:
*  tracklist: reference to global tracklist
*  deck: reference to DeckCompoennt
*  parent: reference to parent TableListBox
*  id: id of associated track
* Output:
*  N/A
*******************************************/
PlaylistOperationsComponent::PlaylistOperationsComponent(TrackCollection& _tracklist, 
    DeckComponent& _deck, TableListBox &_parent, int _id):
    tracklist(_tracklist), deck(_deck), parent(_parent), id(_id)
{
    // add and make visible subcomponents
    btnLoad.onClick = [this] {loadButtonClicked(); };
    addAndMakeVisible(btnLoad);

    btnRemove.onClick = [this] {removeButtonClicked(); };
    addAndMakeVisible(btnRemove);

    track = tracklist.getTrack(id);
    track->addChangeListener(this);
}

/******************************************
* Name:
*  ~PlaylistOperationsComponent
* Description:
*  Destructor for PlaylistOperationsComponent class. Removes self as
*  change listener from associated track.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
PlaylistOperationsComponent::~PlaylistOperationsComponent()
{
    // remove self as change listener to associated track.
    track->removeChangeListener(this);
}

/******************************************
* Name:
*  resized
* Description:
*  override of base class resized method. Scales
*  subcomponents upon resize.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void PlaylistOperationsComponent::resized()
{
    // scale subcomponents upon resize.
    auto drawableArea = getLocalBounds().reduced(PADDING);
    auto h = drawableArea.getHeight();
    btnLoad.setBounds(drawableArea.removeFromLeft(h));
    drawableArea.removeFromLeft(SPACING);
    btnRemove.setBounds(drawableArea.removeFromLeft(h));
}

/******************************************
* Name:
*  changeListenerCallback
* Description:
*  Implementation of virtual method of ChangeListener. Sets enabled state
*  of load and remove buttons depending on if track is loaded in a deck player
*  component
* Parameters:
*  src: Not Used.
* Output:
*  N/A
*******************************************/
void PlaylistOperationsComponent::changeListenerCallback(ChangeBroadcaster* src) {
    // get track and check if its loaded
    auto track = tracklist.getTrack(id);
    // update load and remove buttons depending on if associated track is loaded
    btnLoad.setEnabled(!track->isLoaded());
    btnRemove.setEnabled(!track->isLoaded());
}

/******************************************
* Name:
*  loadButtonPressed
* Description:
*  event handler for when load button is pressed. create new deck player
*  component for associated track.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void PlaylistOperationsComponent::loadButtonClicked() {
    // create new deck player component for associated track
    deck.loadPlayer(id);
}

/******************************************
* Name:
*  removeButtonClicked
* Description:
*  event handler for when remove button is clicked. Removes
*  associated track from track list and update parent table display.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void PlaylistOperationsComponent::removeButtonClicked() {
    // remove associated track from tracklist    
    tracklist.removeTrack(id);

    // update parent table list box and redraw
    parent.updateContent();
}