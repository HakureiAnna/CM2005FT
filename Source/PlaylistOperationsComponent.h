/*
  ==============================================================================

    PlaylistOperationsComponent.h
    Created: 3 Mar 2022 8:57:00pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

#include "LoadButton.h"
#include "RemoveButton.h"
#include "DeckComponent.h"
#include "TrackCollection.h"

//==============================================================================
/*
*/
class PlaylistOperationsComponent  : public juce::Component,
    public ChangeListener
{
public:
    // constructors & destructors
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
    PlaylistOperationsComponent(TrackCollection& tracklist, DeckComponent& deck,
        TableListBox& parent, int id);

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
    ~PlaylistOperationsComponent() override;

    // base class overrides
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
    void resized() override;

    // ChangeListener overrides
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
    void changeListenerCallback(ChangeBroadcaster* src) override;

    // event handlers
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
    void loadButtonClicked();

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
    void removeButtonClicked();


    // public constants
    static const int PADDING = 2;   // padding between buttons and component edge
    static const int SPACING = 10;  // space between buttons

private:
    // functionality members
    TrackCollection& tracklist; // reference to global TrackCollection
    Track* track;   // pointer to associated track
    int id;     // id of associated track, needed to load deck player component

    // GUI members
    LoadButton btnLoad;     // load button
    RemoveButton btnRemove; // remove button
    DeckComponent& deck;    // reference to deck component
    TableListBox& parent;   // reference to parent table list box
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistOperationsComponent)
};
