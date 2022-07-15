#include "MainComponent.h"

//==============================================================================
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
MainComponent::MainComponent():
    playerPool(formatManager),
    tracklist(formatManager),
    cmpDeck(formatManager, thumbCache, tracklist, playerPool),
    cmpPlaylist(tracklist, cmpDeck)
{
    // add and make visible sub components
    addAndMakeVisible(cmpDeck);
    addAndMakeVisible(cmpPlaylist);

    // initialize audio format manager with basic audio format support
    formatManager.registerBasicFormats();

    // size app window
    setSize(WIDTH_APP, HEIGHT_APP);

    // initialize audio system
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels(0, 1);
    }

    // load track list from config file
    tracklist.load();
}

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
MainComponent::~MainComponent()
{
    // shutdown audio system
    shutdownAudio();

    // save track list to config file
    tracklist.save();
}

//==============================================================================
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
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // prepare mixersource
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    // add available DJAudioPlayer instances as input to mixer source
    for (auto i = 0; i < playerPool.size(); ++i) {
        playerPool.getPlayer(i)->prepareToPlay(samplesPerBlockExpected, sampleRate);
        mixerSource.addInputSource(playerPool.getPlayer(i), false);
    }
}

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
void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // start audio chain processing by requesting sample from mixer source
    mixerSource.getNextAudioBlock(bufferToFill);
}

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
void MainComponent::releaseResources()
{
    // remove all inputs from and cleanup mixer source
    mixerSource.removeAllInputs();
    mixerSource.releaseResources();

    // clean up all DJAudioPlayers
    for (auto i = 0; i < playerPool.size(); ++i) {
        playerPool.getPlayer(i)->releaseResources();
    }
}

//==============================================================================
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
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

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
void MainComponent::resized()
{
    auto usableArea = getLocalBounds().reduced(PADDING);
    auto playlistArea = usableArea.removeFromBottom(HEIGHT_PLAYLIST);

    cmpDeck.setBounds(usableArea);
    cmpPlaylist.setBounds(playlistArea);
}
