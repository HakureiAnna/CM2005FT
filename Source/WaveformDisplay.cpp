/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 2 Feb 2022 1:35:12pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
/******************************************
* Name:
*  WaveformDisplay
* Description:
*  Constructor of the WaveformDisplay class. set up custom LookAndFeel,
*  initialize and add GUI components, add this as a change listener to the
*  audio thumbnail cache.
* Parameters:
*  formatManagerToUse: reference to global AudioFormatManager
*  cacheToUse: reference to global AudioThumbnailCache
*  track: pointer to associated track
* Output:
*  N/A
*******************************************/
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse, Track* _track) :
    audioThumb(1000, formatManagerToUse, cacheToUse),
    fileLoaded(false),
    track(_track),
    playhead(_track)
{
    // set custom LookAndFeel
    setLookAndFeel(&lookAndFeel);
    
    // add and make visible the playhead component
    addAndMakeVisible(playhead);

    // add this as change listener to the thumbnail
    audioThumb.addChangeListener(this);
}

/******************************************
* Name:
*  ~WaveformDisplay
* Description:
*  Destructor for the WaveformDisplay class.
*  Sets the LookAndFeel to nullptr to release
*  the reference.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
WaveformDisplay::~WaveformDisplay() {
    // release reference to custom LookAndFeel
    setLookAndFeel(nullptr);
}

/******************************************
* Name:
*  paint
* Description:
*  override of base class paint method
* Parameters:
*  g: reference to Graphics used for drawing the
*    time-domain waveform
* Output:
*  N/A
*******************************************/
void WaveformDisplay::paint (juce::Graphics& g)
{
    // get, set background colour and draw
    auto& lookAndFeel = getLookAndFeel();
    g.fillAll (lookAndFeel.findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    // draw border
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    // draw waveform if file is loaded
    g.setColour(lookAndFeel.findColour(OtoDecksLookAndFeel::waveformColourId));
    if (fileLoaded) {
        audioThumb.drawChannel(g,
            getLocalBounds(),
            0,
            audioThumb.getTotalLength(),
            0,
            1.0f);
    }
    // write text if file is not loaded (irrelevant but kept as legacy code)
    else {
        g.setFont(20.0f);
        g.drawText("File not loaded...", getLocalBounds(),
            juce::Justification::centred, true);   // draw some placeholder text
    }
}

/******************************************
* Name:
*  resized
* Description:
*  override of base class resized function to
*  properly scale subcomponents.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void WaveformDisplay::resized()
{   // resize playhead to fill entire component space
    playhead.setBounds(getLocalBounds());
}

/******************************************
* Name:
*  changeListenerCallback
* Description:
*  Used to associate this with the audio thumbnail cache
*  to repaint when notified that the thumbnail is changed (ready).
* Parameters:
*  source: Not Used.
* Output:
*  N/A
*******************************************/
void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source) {
    repaint();
}

/******************************************
* Name:
*  repaintPlayhead
* Description:
*  relay function to repaint only the playhead when timer
*  in deck player component triggers.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void WaveformDisplay::repaintPlayhead() {
    // update playhead position and repaint ONLY the playhead
    playhead.setPosition(track->getPositionRelative());
    playhead.repaint();
}

/******************************************
* Name:
*  loadURL
* Description:
*  load the audio file at specified URL and start
*  loading the waveform in the audio thumbnail cache
* Parameters:
*  audioURL: url to audio file
* Output:
*  N/A
*******************************************/
void WaveformDisplay::loadURL(URL audioURL) {
    // load audio thumbnail
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
}