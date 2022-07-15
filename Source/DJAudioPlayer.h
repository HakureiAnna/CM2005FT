/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 18 Jan 2022 12:03:01pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;

#include "FrequencyDisplay.h"

class DJAudioPlayer: public AudioSource {
public:
    // constructors and destructors
    /******************************************
    * Name:
    *  DJAudioPlayer
    * Description:
    *  constructor of the DJAudioPlayer class. Set sampleRate
    *  to default setting so the LPF and HPF audio sources can be  
    *  initialized.
    * Parameters:
    *  _formatManager: reference to global AudioFormatManager
    *  _id: ID of this player
    * Output:
    *  N/A
    *******************************************/
    DJAudioPlayer(AudioFormatManager& _formatManager, int id);

    /******************************************
    * Name:
    *  ~DJAudioPlayer
    * Description:
    *  destructor of the DJAudioPlayer class, release the reference 
    *  to the associated frequency display.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    ~DJAudioPlayer();

    // base class overrides
    /******************************************
    * Name:
    *  prepareToPlay
    * Description:
    *  override of the base class prepareToPlay method. Prepares
    *  the various linked audio sources in the player, transport, resampling,
    *  LPF and HPF sources. Stores the passed sampleRate to use for later
    *  changes to the bandwidth in the filters.
    * Parameters:
    *  samplesPerBlockExpected: no. of samples to return on each getNextAudioBlock call
    *  sampleRate: audio sampling rate
    * Output:
    *  N/A
    *******************************************/
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;

    /******************************************
    * Name:
    *  getNextAudioBlock
    * Description:
    *  overide of the base class's getNextAudioBlock metod. Only need to pass the 
    *  call to the last audio source in the processing chain, that is the HPF audio source.
    *  Also, if there's an associated frequency display, push the processing completed samples
    *  to it, so it can perform FFT on it.
    * Parameters:
    *  bufferToFill: a descriptor representing the read and write audio buffers.
    * Output:
    *  N/A
    *******************************************/
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    /******************************************
    * Name:
    *  releaseResources
    * Description:
    *  override of the base class releaseResources method. Used to clean up on termination
    *  and thus calls the relevant methods of the transport, resampling, LPF and HPF audio
    *  sources.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void releaseResources() override;

    // getters and setters
    /******************************************
    * Name:
    *  setCutoffFrequency
    * Description:
    *  setter for the bandwidth lower and upper limits. Updates the
    *  LPF and HPF audio sources, by creating new coefficients.
    * Parameters:
    *  fLow - lower bandwidth limit
    *  fHigh - higher bandwidth limit
    * Output:
    *  N/A
    *******************************************/
    void setCutoffFrequency(double fLow, double fHigh);

    /******************************************
    * Name:
    *  setFrequencyDisplay
    * Description:
    *  setter for setting up associated frequency display.
    * Parameters:
    *  frequencyDisplay: pointer to frequency display to associate with.
    * Output:
    *  N/A
    *******************************************/
    void setFrequencyDisplay(FrequencyDisplay* freqeuncyDisplay);

    /******************************************
    * Name:
    *  setGain
    * Description:
    *  setter for the volume gain, passes the new gain to the
    *  transport source.
    * Parameters:
    *  gain: volume 'multiplier'
    * Output:
    *  N/A
    *******************************************/
    void setGain(double gain);

    /******************************************
    * Name:
    *  setPosiiton
    * Description:
    *  setter for the playback position. Passes position on to
    *  transport source.
    * Parameters:
    *  posInSecs: position in seconds
    * Output:
    *  N/A
    *******************************************/
    void setPosition(double posInSecs);

    /******************************************
    * Name:
    *  setPositionRelative
    * Description:
    *  setter for position but in relative units (0.0-1.0). Uses the
    *  setPosition method.
    * Parameters:
    *  pos: relative playback position (0.0 - 1.0)
    * Output:
    *  N/A
    *******************************************/
    void setPositionRelative(double pos);

    /******************************************
    * Name:
    *  setSpeed
    * Description:
    *  setter for playback speed. Sets the playback speed by passing
    *  the speed ratio on the resampling audio source.
    * Parameters:
    *  ratio: playback speed ratio
    * Output:
    *  N/A
    *******************************************/
    void setSpeed(double ratio);

    /******************************************
    * Name:
    *  getDuration
    * Description:
    *  Getter for the total track duration using the transport source.
    * Parameters:
    *  N/A
    * Output:
    *  total duration of associated track.
    *******************************************/
    double getDuration();

    /******************************************
    * Name:
    *  getID
    * Description:
    *  getter player ID.
    * Parameters:
    *  N/A
    * Output:
    *  ID of the player
    *******************************************/
    int getID();

    /******************************************
    * Name:
    *  getPositionRelative
    * Description:
    *  getter for the relative playback position. Returns a value
    *  between 0.0 and 1.0.
    * Parameters:
    *  N/A
    * Output:
    *  Relative playback position (0.0-1.0)
    *******************************************/
    double getPositionRelative();

    // methods
    /******************************************
    * Name:
    *  loadURL
    * Description:
    *  loads the track from the specified path by creating a 
    *  reader using the format manager, which is then bind to a 
    *  AudioFormatReaderSource and used as input to the transport source.
    * Parameters:
    *  audioURL: full path of the audio track in URL format
    * Output:
    *  N/A
    *******************************************/
    void loadURL(URL audioURL);

    /******************************************
    * Name:
    *  start
    * Description:
    *  Used to start playback, passes to transport source.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void start();

    /******************************************
    * Name:
    *  stop
    * Description:
    *  Used to pause playback, passes to the transport source.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void stop();

    /******************************************
    * Name:
    *  rewind
    * Description:
    *  Used to stop and rewind to start using the transport source.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void rewind();

    /******************************************
    * Name:
    *  fastForward
    * Description:
    *  Used to fast forward playback position by amount determined 
    *  by the playback speed.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void fastForward();

    /******************************************
    * Name:
    *  fastReverse
    * Description:
    *  Used to fast reverse playback position by amount determined
    *  by the playback speed.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void fastReverse();

    // public constants
    static const double MIN_GAIN;   // lower limit of volume gain
    static const double MAX_GAIN;   // upper limit of volume gain
    static const double INTERVAL_GAIN;  // step/ interval for volume gain change
    static const double DEFAULT_GAIN;   // initial volume gain
    static const double MIN_SPEED;  // lower limit of playback speed
    static const double MAX_SPEED;  // upper limit of playback speed
    static const double INTERVAL_SPEED; // step/ interval for playback speed change
    static const double DEFAULT_SPEED; // initial playback speed
    static const double MIN_CUTOFF_FREQUENCY;   // lower limit of bandwidth range
    static const double MAX_CUTOFF_FREQUENCY;   // upper limit of bandwidth range
    static const double INTERVAL_CUTOFF_FREQUENCY;  // step/ interval for bandwidth change
    static const int DEFAULT_SAMPLE_RATE = 44100;   // default sampling rate


private:
    // functionality members
    int id; // id of this player
    AudioFormatManager& formatManager;  // reference to global AudioFormatManager
    std::unique_ptr<AudioFormatReaderSource> readerSource;  // reader audio source
    AudioTransportSource transportSource;   // transport audio source
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 }; // resampling audio source
    IIRFilterAudioSource lpfSource{ &resampleSource, false };   // LPF audio source
    IIRFilterAudioSource hpfSource{ &lpfSource, false };    // HPF audio source
    double sampleRate;  // copy of sampling rate for setting filter coefficinets
    double speed; // playback speed

    // GUI members
    FrequencyDisplay* frequencyDisplay; // pointer to associated frequency display

};