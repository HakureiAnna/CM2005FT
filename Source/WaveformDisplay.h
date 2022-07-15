/*
  ==============================================================================

    WaveformDisplay.h
    Created: 2 Feb 2022 1:35:12pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

#include "OtoDecksLookAndFeel.h"
#include "WaveformDisplayPlayhead.h"
#include "Track.h"

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
    public ChangeListener
{
public:
    // constructors & destructors
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
    WaveformDisplay(AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse, Track *track);

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
    ~WaveformDisplay();

    // base class overides
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
    void paint (juce::Graphics& g) override;

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
    void resized() override;

    // ChangeListener overrides
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
    void changeListenerCallback(ChangeBroadcaster* source) override;

    // methods
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
    void repaintPlayhead();

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
    void loadURL(URL audioURL);

private:
    // functionality members
    bool fileLoaded;    // flag indicating if file has been loaded
    Track* track;   // pointer to associated track

    // GUI related members
    AudioThumbnail audioThumb;  // particular thumbnail that should be drawn
    OtoDecksLookAndFeel lookAndFeel;    // custom LookAndFeel
    WaveformDisplayPlayhead playhead;   // instance playhead component

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
