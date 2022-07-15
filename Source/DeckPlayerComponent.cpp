/*
  ==============================================================================

    DeckPlayerComponent.cpp
    Created: 1 Mar 2022 4:08:32pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckPlayerComponent.h"
#include "DJAudioPlayer.h"

//==============================================================================
/******************************************
* Name:
*  DeckPlayerComponent
* Description:
*  constructor for the DeckPlayerComponent. Used to initialize
*  and setup the GUI components, start timer running.
* Parameters:
*  track: pointer to Track that this player will player
*  _formatManager: reference of global AudioFormatManager
*  _cache: reference of global AudioThumbnailCache
* Output:
*  N/A
*******************************************/
DeckPlayerComponent::DeckPlayerComponent(
    Track* _track,
    AudioFormatManager& _formatManager,
    AudioThumbnailCache& _cache) :
    track(_track),
    waveformDisplay(_formatManager, _cache, track),
    sldFilter(Slider::TwoValueHorizontal, DJAudioPlayer::MIN_CUTOFF_FREQUENCY,
        DJAudioPlayer::MAX_CUTOFF_FREQUENCY, DJAudioPlayer::INTERVAL_CUTOFF_FREQUENCY,
        DJAudioPlayer::MIN_CUTOFF_FREQUENCY, "BW", "Hz", 0),
    sldVolume(Slider::Rotary, DJAudioPlayer::MIN_GAIN, DJAudioPlayer::MAX_GAIN, 
        DJAudioPlayer::INTERVAL_GAIN, DJAudioPlayer::DEFAULT_GAIN, "Volume", "", 2),
    sldSpeed(Slider::Rotary, DJAudioPlayer::MIN_SPEED, DJAudioPlayer::MAX_SPEED, 
        DJAudioPlayer::INTERVAL_SPEED, DJAudioPlayer::DEFAULT_SPEED, "Speed", "x", 1)
{
    setName(_track->getFileName());
    lblTrack.setJustificationType(Justification::horizontallyCentred);
    lblTrack.setText(track->getFileName(), dontSendNotification);
    addAndMakeVisible(lblTrack);

    btnFastReverse.onClick = [this] {fastReverseButtonClicked(); };
    addAndMakeVisible(btnFastReverse);

    btnPlay.onClick = [this] {playButtonClicked(); };
    addAndMakeVisible(btnPlay);

    btnPause.onClick = [this] {pauseButtonClicked(); };
    addAndMakeVisible(btnPause);

    btnStop.onClick = [this] {stopButtonClicked(); };
    addAndMakeVisible(btnStop);

    updateButtons(true, false, false);

    btnFastForward.onClick = [this] {fastForwardButtonClicked(); };
    addAndMakeVisible(btnFastForward);

    btnPower.onClick = [this] { powerButtonClicked();};
    addAndMakeVisible(btnPower);

    // frequency filter initialization
    sldFilter.setMinAndMaxValues(DJAudioPlayer::MIN_CUTOFF_FREQUENCY,
        DJAudioPlayer::MAX_CUTOFF_FREQUENCY);
    sldFilter.onValueChange = [this] {filterSliderChanged(); };
    addAndMakeVisible(sldFilter);

    // volume slider initialization
    sldVolume.onValueChange = [this] {volumeSliderChanged(); };
    addAndMakeVisible(sldVolume);

    // speed slider initialization
    sldSpeed.onValueChange = [this] {speedSliderChanged(); };
    addAndMakeVisible(sldSpeed);

    waveformDisplay.loadURL(URL{ File{track->getFullPath()} });
    addAndMakeVisible(waveformDisplay);

    track->setFrequencyDisplay(&frequencyDisplay);
    addAndMakeVisible(frequencyDisplay);

    startTimerHz(REFRESH_FREQUENCY);
}

/******************************************
* Name:
*  ~DeckPlayerComponent
* Description:
*  Destructor for the DeckPlayerComponent. Used to properly cleanup.
*  Stops the timer and removes all attached ChangeListeners
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
DeckPlayerComponent::~DeckPlayerComponent() {
    stopTimer();
    removeAllChangeListeners();
}

/******************************************
 * Name:
 * paint
 * Description:
 *  override of the base class's paint method. Draws a border
 *  around the component.
 * Parameters:
 *  g: reference to Graphics used to perform drawing
 * Output:
 *  N/A
 *******************************************/
void DeckPlayerComponent::paint (juce::Graphics& g)
{
    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}

/******************************************
 * Name:
 *  resized
 * Description:
 *  override of base class's resized method. Used to
 *  properly resize subcomponents.
 * Parameters:
 *  N/A
 * Output:
 *  N/A
 *******************************************/
void DeckPlayerComponent::resized()
{
    // get the full drawable area
    auto drawableArea = getLocalBounds().reduced(PADDING);
    // reserve space for top row buttons
    auto buttonsArea = drawableArea.removeFromTop(HEIGHT_BUTTON);
    // reserve space for rotary sliders
    auto rotarySlidersArea = drawableArea.removeFromBottom(WIDTH_FIXED/2);

    btnFastReverse.setBounds(buttonsArea.removeFromLeft(WIDTH_BUTTON).reduced(PADDING));
    btnPlay.setBounds(buttonsArea.removeFromLeft(WIDTH_BUTTON).reduced(PADDING));
    btnPause.setBounds(buttonsArea.removeFromLeft(WIDTH_BUTTON).reduced(PADDING));
    btnStop.setBounds(buttonsArea.removeFromLeft(WIDTH_BUTTON).reduced(PADDING));
    btnFastForward.setBounds(buttonsArea.removeFromLeft(WIDTH_BUTTON).reduced(PADDING));
    btnPower.setBounds(buttonsArea.removeFromRight(WIDTH_BUTTON).reduced(PADDING));
    lblTrack.setBounds(buttonsArea);

    // reserve and allocate space for frequency filter and position sliders
    auto freqSliderArea = drawableArea.removeFromBottom(HEIGHT_SLIDER);
    sldFilter.setBounds(freqSliderArea.reduced(PADDING));
  
    // compute space for rotary sliders
    auto w = rotarySlidersArea.getWidth() / 2;
    auto rotarySliderArea = rotarySlidersArea.removeFromLeft(w);
    sldVolume.setBounds(rotarySliderArea.reduced(PADDING));
    sldSpeed.setBounds(rotarySlidersArea.reduced(PADDING));

    frequencyDisplay.setBounds(drawableArea.removeFromTop(WIDTH_FIXED-PADDING*2-100));
    waveformDisplay.setBounds(drawableArea);
}

/******************************************
* Name:
*  timerCallback
* Description :
*  implementation of the virtual timerCallback method.
*  The method checks if track has finished playing, reset
*  buttons and track if so and updates frequencyDisplay
*  and waveformDisplay.
* Parameters :
*  N/A
* Output :
*  N/A
*******************************************/
void DeckPlayerComponent::timerCallback() {
    // check if track has finished playing...
    if (!track->getPositionRelative() >= 1.0) {
        // if so, stop the track and update buttons
        track->stop();
        updateButtons(true, false, false);
    }

    // repaint the playhead (ONLY)
    waveformDisplay.repaintPlayhead();
    // compute FFT and update frequency display
    frequencyDisplay.updateFFT();

}

/******************************************
* Name:
*  playButtonClicked
* Description:
*  Event handler for when the play button is pressed.
*  Starts the track playing, disables the play buton while
*  enabling the pause and stop buttons.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckPlayerComponent::playButtonClicked() {
    track->play();
    updateButtons(false, true, true);
}

/******************************************
* Name:
*  pauseButtonClicked
* Description:
*  Event handler for when the pause button is pressed.
*  Pauses a playing track, enables the play and stop button while
*  disabling the pause button.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckPlayerComponent::pauseButtonClicked() {
    track->pause();
    updateButtons(true, false, true);
}

/******************************************
* Name:
*  stopButtonClicked
* Description:
*  Event handler for when the stop button is pressed.
*  Stops a playing track, disables the pause and stop buttons while
*  enabling the play button.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckPlayerComponent::stopButtonClicked() {
    track->stop();
    updateButtons(true, false, false);
}

/******************************************
* Name:
*  powerButtonPresed
* Description:
*  Event handler for when power button is pressed.
*  Disassociate frequency display from track and send
*  message to deck component to start clean up.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckPlayerComponent::powerButtonClicked() {
    track->setFrequencyDisplay(nullptr);
    sendChangeMessage();
}

/******************************************
* Name:
*  fastForwardButtonClicked
* Description:
*  Event handler for when fast forward button is pressed.
*  Fast forward track by an amount dependent on playback speed.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckPlayerComponent::fastForwardButtonClicked() {
    track->fastForward();
}

/******************************************
* Name:
*  fastReverseButtonClicked
* Description:
*  Event handler for when fast reverse button is pressed.
*  Fast reverse track by an amount dependent on playback speed.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckPlayerComponent::fastReverseButtonClicked() {
    track->fastReverse();
}

/******************************************
* Name:
*  volumeSliderChanged
* Description:
*  Event handler for when volume slider's value is changed.
*  Updates the track's volume.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckPlayerComponent::volumeSliderChanged() {
    auto vol = sldVolume.getValue();
    track->setVolume(vol);
}

/******************************************
* Name:
*  speedSliderChanged
* Description:
*  Event handler for when the speed slider's value is changed.
*  Updates the track's playback speed.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckPlayerComponent::speedSliderChanged() {
    auto spd = sldSpeed.getValue();
    track->setSpeed(spd);
}

/******************************************
* Name:
*  filterSliderChanged
* Description:
*  Event handler for when filter slider's value is changed.
*  Update the bandwidth range of the track.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
void DeckPlayerComponent::filterSliderChanged() {
    auto fLow = sldFilter.getMinValue();
    auto fHigh = sldFilter.getMaxValue();
    track->setFrequencyRange(fLow, fHigh);
}

/******************************************
* Name:
*  getTrack
* Description:
*  Getter for the deck player component's associated track. Used
*  in deck component for clean up.
* Parameters:
*  N/A
* Output:
*  N/A
*******************************************/
Track* DeckPlayerComponent::getTrack() {
    return track;
}

/******************************************
* Name:
*  updateButtons
* Description:
*  Updates the play, pause and stop button's enabledness.
* Parameters:
*  enablePlay: if to enable the play button
*  enablePause: if to enable the pause button
*  enableStop: if to enable the stop button
* Output:
*  N/A
*******************************************/
void DeckPlayerComponent::updateButtons(bool enablePlay, bool enablePause, bool enableStop) {
    btnPlay.setEnabled(enablePlay);
    btnPause.setEnabled(enablePause);
    btnStop.setEnabled(enableStop);
}
