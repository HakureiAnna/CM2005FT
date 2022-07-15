/*
  ==============================================================================

    PlaylistComponent.h
    Created: 15 Feb 2022 2:44:09pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
using namespace juce;

#include "AddButton.h"
#include "TrackCollection.h"
#include "DeckComponent.h"
#include "RemoveButton.h"

//==============================================================================
class PlaylistComponent  : public Component,
    public TableListBoxModel,
    public FileDragAndDropTarget
{
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  PlaylistComponent
    * Description:
    *  Constructor for the PlaylistComponent. initialize and add
    *  GUI components.
    * Parameters:
    *  tracklist: reference to global TrackCollection
    *  deck: reference to DeckComponent
    * Output:
    *  N/A
    *******************************************/
    PlaylistComponent(TrackCollection& tracklist, DeckComponent& deck);

    // base class overrides
    /******************************************
    * Name:
    *  paint
    * Description:
    *  override to base class paint method. Fill with bagrkound and
    *  draw border around compoennt.
    * Parameters:
    *  g: reference to Graphics used for drawing.
    * Output:
    *  N/A
    *******************************************/
    void paint (juce::Graphics& g) override;

    /******************************************
    * Name:
    *  resized
    * Description:
    *  override of base class resized method. Conduct
    *  rescaling for subcomponents.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void resized() override;

    // TableListBoxModel overrides
    /******************************************
    * Name:
    *  getNumRows
    * Description:
    *  Implementation for virtual method of TableListBoxModel.
    *  returns the number of rows to draw in the TableListBox.
    * Parameters:
    *  N/A
    * Output:
    *  number of rows to draw in the TableListBox
    *******************************************/
    int getNumRows() override;

    /******************************************
    * Name:
    *  paintRowBackground
    * Description:
    *  Paint different background colour for each row depending 
    * on if the row is selected.
    * Parameters:
    *  g: reference to Graphics used for drawing
    *  rowNumber: current row number
    *  width: width of row
    *  height: height of row
    *  rowIsSelected: if current row is selected
    * Output:
    *  N/A
    *******************************************/
    void paintRowBackground(Graphics& g,
        int rowNumber,
        int width, 
        int height,
        bool rowIsSelected) override;

    /******************************************
    * Name:
    *  paintCell
    * Description:
    *  Draw the content for each table cell.
    * Parameters:  
    *  g: reference to Graphics used for drawing
    *  rowNumber: current row number
    *  columnId: current column ID
    *  width: width of the cell
    *  height: height of the cell
    *  rowIsSelected: flag indicating if the current row is selected
    * Output:
    *  N/A
    *******************************************/
    void paintCell(Graphics& g,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected) override;

    /******************************************
    * Name:
    *  refreshComponentForCell
    * Description:
    *  Allows Modifying of subcomponent for current cell if necessary.
    * Parameters:
    *  rowNumber: current row number
    *  columnId: current column ID
    *  exisitngComponentToUpdate: pointer to subcomponent in current cell
    * Output:
    *  N/A
    *******************************************/
    Component* refreshComponentForCell(int rowNumber,
        int columnId,
        bool isRowSelected,
        Component* existingComponentToUpdate) override;

    // FileDragAndDropTarget overrides
    /******************************************
    * Name:
    *  isInterestedInFileDrag
    * Description:
    *  Returns if this component is interested in the array
    *  of files provided as argument. Always returns true as
    *  this is the ONLY component in this app that reacts to file
    *  drag and drop.
    * Parameters:
    *  files: array of full path of files dropped onto the component
    * Output:
    *  indicates if the component is interested in the files dropped on it.
    *******************************************/
    bool isInterestedInFileDrag(const StringArray& files) override;

    /******************************************
    * Name:
    *  filesDropped
    * Description:
    *  Handler to act on the files that are dropped on the component, adding
    *  them to track list if they are audio files that can be loaded.
    * Parameters:
    *  files: array of full path of files dropped on the component
    *  x: Not Used.
    *  y: Not Used.
    * Output:
    *  N/A
    *******************************************/
    void filesDropped(const StringArray& files, int x, int y) override;

    // DragAndDropContainer subclass handler
    /******************************************
    * Name:
    *  getDragSourceDescription
    * Description:
    *  used to provide the descriptor used by the DragAndDropTarget.
    * Parameters:
    * selectedRows: list of selected rows thar are dragged
    * Output:
    *  Descriptor of the id of the selected rows
    *******************************************/
    var getDragSourceDescription(const SparseSet<int>& selectedRows);

    // event listeners
    /******************************************
    * Name:
    *  addButtonClicked
    * Description:
    *  event handler for when the add button is clicked. Display file browser
    *  to try to load audio files into the track list.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void addButtonClicked();

    /******************************************
    * Name:
    *  removeButtonClicked
    * Description:
    *  event handler for the remove button (search clear button), clears
    *  the search box and displays all the tracks in the tracklist
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void removeButtonClicked();

    /******************************************
    * Name:
    *  searchTextChanged
    * Description:
    *  event handler for when the search text editor's text has changed.
    *  performs case-insenstive text with the track list to display only
    *  tracks that match the search term.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void searchTextChanged();
    
    // public constants
    static const int HEIGHT_BUTTON = 24;    // height of button
    static const int HEIGHT_PANEL = 34;     // height of panel for search box and buttons
    static const int WIDTH_ADD_BUTTON = 40; // width of add button
    static const int WIDTH_REMOVE_BUTTON = 20;  // width of remove button
    static const int WIDTH_TEXTBOX_SEARCH = 200;    // width of search box
    static const int PADDING = 5;       // padding between component edge and subcomponents
    static const int ID_FILENAME = 1;   // column id for filename output
    static const int ID_DURATION = 2;   // column id for duration output
    static const int ID_OPERATIONS = 3; // column id for operations

private:
    // functionality members
    TrackCollection& tracklist; // reference to global TrackCollection

    // GUI members
    Label lblTitle; // label used to display playlist title
    AddButton btnAdd;   // add button
    RemoveButton btnRemove; // remove button (clear search)
    TableListBox tableComponent;    // tablelist component to display track list
    DeckComponent& deck;    // reference to deck component
    Label lblSearch;        // label for search box
    TextEditor txtSearch;   // search box
    std::unique_ptr<FileChooser> fileChooser;   // smart pointer to file browser

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
