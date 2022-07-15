/*
  ==============================================================================

    DeckComponent.h
    Created: 1 Mar 2022 2:36:43pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

#include "DeckPlayerComponent.h"
#include "TrackCollection.h"
#include "PlayerPool.h"

//==============================================================================
/*
*/
class DeckComponent  : public Component,
    public DragAndDropTarget,
    public ChangeListener
{
public:
    // constructors & destructors
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
    DeckComponent(AudioFormatManager& _formatManager, AudioThumbnailCache& cache, 
        TrackCollection& tracklist, PlayerPool& playerPool);

    // base class overides
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
    void resized() override;

    // DragAndDropTarget overrides
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
    bool isInterestedInDragSource(const SourceDetails& src) override;

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
    void itemDropped(const SourceDetails& src) override;

    // ChangeListener overrides
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
    void changeListenerCallback(ChangeBroadcaster* src) override;

    // methods
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
    void loadPlayer(int id);

private:
    // internal class to support scrollbars through ViewPort
    class DeckDisplayAreaComponent : public Component {
    public:
        // constructors & destructors
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
        DeckDisplayAreaComponent(DeckComponent *parent);

        // base class overrides
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
        void resized() override;

    private:
        DeckComponent* parent;  // pointer to parent

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckDisplayAreaComponent)
    };

    // functionality members
    AudioFormatManager& formatManager;  // reference to global AudioFormatManager
    AudioThumbnailCache& cache; // reference to global AudioThumbnailCache
    TrackCollection& tracklist; // reference to global TrackCollection
    PlayerPool& playerPool; // reference to global PlayerPool

    // GUI members
    DeckDisplayAreaComponent displayArea;  // instance of internal class used to display
                                            // DeckPlayerComponents
    Viewport viewport;  // instance of Viewport component to provide
                        // scrollbar support for DeckPlayerComponents
                        // within the DeckComponent
    OwnedArray<DeckPlayerComponent> deckPlayers;    // array of pointers to child
                                                    // DeckPlayerComponents
    
    // make internal class a friend to allow it to access private members
    friend DeckDisplayAreaComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckComponent)
};