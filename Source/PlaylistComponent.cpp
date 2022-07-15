/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 15 Feb 2022 2:44:09pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"
#include "PlaylistOperationsComponent.h"

//==============================================================================
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
PlaylistComponent::PlaylistComponent(TrackCollection& _tracklist, DeckComponent& _deck):
    tracklist(_tracklist), deck(_deck)
{
    // setup, add and display sub components
    lblTitle.setText("Playlist", dontSendNotification);
    lblTitle.setJustificationType(Justification::horizontallyCentred);
    addAndMakeVisible(lblTitle);

    btnAdd.onClick = [this] {addButtonClicked(); };
    addAndMakeVisible(btnAdd);

    tableComponent.getHeader().addColumn("Filename", 1, 400);
    tableComponent.getHeader().addColumn("Duration", 2, 200);
    tableComponent.getHeader().addColumn("Operations", 3, 200);
    tableComponent.setModel(this);
    addAndMakeVisible(tableComponent);

    lblSearch.setText("Search:", dontSendNotification);
    lblSearch.attachToComponent(&txtSearch, true);

    txtSearch.onTextChange = [this] {searchTextChanged(); };
    addAndMakeVisible(txtSearch);    

    btnRemove.setTooltip("Clear search term");
    btnRemove.onClick = [this] {removeButtonClicked(); };
    addAndMakeVisible(btnRemove);
}

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
void PlaylistComponent::paint (juce::Graphics& g)
{
    // draw background and border
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

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
void PlaylistComponent::resized()
{
    // rescale subcomponents or resize
    auto margin = (HEIGHT_PANEL - HEIGHT_BUTTON) / 2;
    auto drawableArea = getLocalBounds().reduced(PADDING);
    auto panelArea = drawableArea.removeFromTop(HEIGHT_PANEL).reduced(margin);

    btnAdd.setBounds(panelArea.removeFromRight(WIDTH_ADD_BUTTON));

    btnRemove.setBounds(panelArea.removeFromRight(WIDTH_REMOVE_BUTTON));
    txtSearch.setBounds(panelArea.removeFromRight(WIDTH_TEXTBOX_SEARCH));

    lblTitle.setBounds(panelArea);
    tableComponent.setBounds(drawableArea);
}    

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
int PlaylistComponent::getNumRows() {
    // return the total number of tracks or selected tracks (when searching)
    return tracklist.size();
}

/******************************************
* Name:
*  paintRowBackground
* Description:
*  Paint different background colour for each row depending
* on if the row is selected.
* Parameters:
*  rowNumber: current row number
*  width: width of row
*  height: height of row
*  rowIsSelected: if current row is selected
* Output:
*  N/A
*******************************************/
void PlaylistComponent::paintRowBackground(Graphics& g,
    int rowNumber,
    int width,
    int height,
    bool rowIsSelected) {
    // paint different background based on if row is selected
    if (rowIsSelected) {
        g.fillAll(Colours::orange);
    }
    else {
        g.fillAll(Colours::darkgrey);
    }
}

/******************************************
* Name:
*  paintCell
* Description:
*  Draw the content for each table cell.
* Parameters:
*  rowNumber: current row number
*  columnId: current column ID
*  width: width of the cell
*  height: height of the cell
*  rowIsSelected: flag indicating if the current row is selected
* Output:
*  N/A
*******************************************/
void PlaylistComponent::paintCell(Graphics& g,
    int rowNumber,
    int columnId,
    int width,
    int height,
    bool rowIsSelected) {
    // if rowNumber exceeds tracklist size, return
    if (rowNumber >= tracklist.size()) {
        return;
    }
    auto track = tracklist.getTrack(rowNumber);
    String output;
    // output different information based on column
    switch (columnId) {
    case ID_FILENAME:
        output = track->getFileName();
        break;
    case ID_DURATION:
        output = track->getDurationAsString();
        break;
    }
    g.drawText(output, 2, 0,
        width - 4, height, Justification::centredLeft, true);
}

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
Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
    int columnId,
    bool isRowSelected,
    Component* existingComponentToUpdate) {
    if (columnId == ID_OPERATIONS) {
        // if no operations subcomponent exist, create new, and assign it to pointer
        if (existingComponentToUpdate == nullptr) {

            auto btnContainer = new PlaylistOperationsComponent(tracklist, deck, tableComponent, rowNumber);
            existingComponentToUpdate = btnContainer;
        }
    }
    // return new/ existing operations subcomponent
    return existingComponentToUpdate;
}

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
bool PlaylistComponent::isInterestedInFileDrag(const StringArray& files) {
    // always return true to indicate interest in files dragged (ONLY file drag
    // and drop component)
    return true;
}

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
void PlaylistComponent::filesDropped(const StringArray& files, int x, int y) {
    // add tracks to track list
    tracklist.addTracks(files);

    // update table list component and redraw
    tableComponent.updateContent();
    tableComponent.repaint();
}

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
var PlaylistComponent::getDragSourceDescription(const SparseSet<int>& selectedRows) {
    // get first selected row and assign it to descriptor and return
    int desc;
    desc = selectedRows[0];
    return desc;
}

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
void PlaylistComponent::addButtonClicked() {
    // create and show file browser
    fileChooser = std::make_unique<FileChooser>("Select a file...");
    fileChooser->launchAsync(FileBrowserComponent::openMode |
        FileBrowserComponent::canSelectFiles,
        [this](const FileChooser& fileChooser) {
            // add track to track list
            tracklist.addTrack(fileChooser.getResult().getFullPathName());

            // update table list component after modifications to track list
            tableComponent.updateContent();
        });
}

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
void PlaylistComponent::removeButtonClicked() {
    // clear previous search result
    tracklist.clearSelectedTracks();

    // reset search box
    txtSearch.setText("", false);

    // update table list component to show all tracks
    tableComponent.updateContent();
    tableComponent.repaint();
}

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

void PlaylistComponent::searchTextChanged() {
    // get lowercase of search term
    auto keyword = txtSearch.getText().toLowerCase();

    // select tracks based on search term
    tracklist.selectTracks(keyword);

    // update table list component and redraw based on search result
    tableComponent.updateContent();
    tableComponent.repaint();
}