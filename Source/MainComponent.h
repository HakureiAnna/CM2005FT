#pragma once
#include <JuceHeader.h>
using namespace juce;

#include "DJAudioPlayer.h"
#include "PlaylistComponent.h"
#include "DeckComponent.h"
#include "TrackCollection.h"
#include "PlayerPool.h"

class MainComponent : public juce::AudioAppComponent,
    public DragAndDropContainer
{
public:
    //==============================================================================
    // constructors & destructors
    /******************************************
    * Name:
    *  MainComponent
    * Description:
    *  Constructor for MainComponent class. add and make visible subcomponents.
    *  initialize audio format manager. set application window size and initialize
    *  audio system. load tracklist from config file.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    MainComponent();

    /******************************************
    * Name:
    *  ~MainComponent
    * Description:
    *  Destructor for MainComponent. shutdown audio system and save
    *  tracklist to config file.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    ~MainComponent() override;

   // base class overrides
    /******************************************
    * Name:
    *  prepareToPlay
    * Description:
    *  override for base class prepareToPlay. Initializes the audio system by
    *  preparing the mixer source and adding all the available DJAudioPlayers as 
    *  input to the mixer source.
    * Parameters:
    *  samplesPerBlockExpected: no. of samples each getNextAudioBlock will process
    *  sampleRate: audio sampling rate
    * Output:
    *  N/A
    *******************************************/
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /******************************************
    * Name:
    * getNextAudioBlock
    * Description:
    *  override of base class getNextAudioBlock. start the audio processing chain
    *  going by requesting for sample from the mixer source which in turn will request
    *  sample from each connected DJAudioPlayer.
    * Parameters:
    *  bufferToFill: file descriptor containing information for the read and write audio 
    *   buffers.
    * Output:
    *  N/A
    *******************************************/
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    /******************************************
    * Name:
    *  releaseResources
    * Description:
    *  override of base class releaseResources, perform audio system cleanup.
    *  Remove all input source from mixer source and call its clean up method.
    *  Call cleanup of each available DJAudioPlayer instance.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void releaseResources() override;

    /******************************************
    * Name:
    *  paint
    * Description:
    *  override of base class paint method. Paints background.
    * Parameters:
    *  g: reference to Graphics used for drawing
    * Output:
    *  N/A
    *******************************************/
    void paint(juce::Graphics& g) override;

    /******************************************
    * Name:
    *  resized
    * Description:
    *  override for base class resized. Perform scaling
    *  for all subcomponents.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void resized() override;

    // public constants
    static const int WIDTH_APP = 1024;  // app window width
    static const int HEIGHT_APP = 1124; // app window height
    static const int HEIGHT_PLAYLIST = 256; // playlist height
    static const int PADDING = 5;   // padding between window edge and subcomponents

private:
    //==============================================================================
        
    // functionality components
    MixerAudioSource mixerSource; // mixer source
    PlayerPool playerPool;  // pool of DJAudioPlayer isntances
    TrackCollection tracklist;  // track list 

    // GUI components
    AudioFormatManager formatManager;   // audio format manager to load resources with
    AudioThumbnailCache thumbCache{ 100 };  // thumbnail cache for waveform display
    PlaylistComponent cmpPlaylist;  // playlist component
    DeckComponent cmpDeck;  // deck component
    TooltipWindow tooltipWindow; // require an instance of this to make Tooltips work int he app.

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
