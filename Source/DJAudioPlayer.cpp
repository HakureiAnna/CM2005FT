/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 18 Jan 2022 12:03:01pm
    Author:  Anna

  ==============================================================================
*/

#include "DJAudioPlayer.h"


/******************************************
* Name:
*  DJAudioPlayer
* Description:
*  constructor of the DJAudioPlayer class. Set sampleRate
*  to default setting so the LPF and HPF audio sources can be
*  initialized.
* Parameters:
*  _formatManager: reference to global AudioFormatManager
*  _id: ID of the associated track
* Output:
*  N/A
*******************************************/
DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager, int _id):
    formatManager(_formatManager), 
    id(_id), 
    sampleRate(DEFAULT_SAMPLE_RATE),
    frequencyDisplay(nullptr),
    speed(DEFAULT_SPEED)
{
    // initialize the LPF and HPF audio sources by setting their cutoff frequencies.
    lpfSource.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, MAX_CUTOFF_FREQUENCY));
    hpfSource.setCoefficients(IIRCoefficients::makeHighPass(sampleRate, MIN_CUTOFF_FREQUENCY));
}

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
DJAudioPlayer::~DJAudioPlayer() {
    // release reference to frequency display
    frequencyDisplay = nullptr;
}

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
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    // initialize all sub audio sources
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    lpfSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    hpfSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    // keep a copy of the sampling rate to use for HPF, LPF audio source changes later
    this->sampleRate = sampleRate;
}

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
void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) {
    // start the audio source chain processing by calling the last in the chain
    hpfSource.getNextAudioBlock(bufferToFill);

    // if associated with a frequency display, pass samples to it, so it can perform FFT
    if (frequencyDisplay != nullptr && bufferToFill.buffer->getNumChannels() > 0) {
        auto* channelData = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);
        for (auto i = 0; i < bufferToFill.numSamples; ++i) {
            frequencyDisplay->pushNextSample(channelData[i]);
        }
    }
}

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
void DJAudioPlayer::releaseResources() {
    // clean up for all sub audio sources
    transportSource.releaseResources();
    resampleSource.releaseResources();
    lpfSource.releaseResources();
    hpfSource.releaseResources();
}

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
void DJAudioPlayer::setCutoffFrequency(double fLow, double fHigh) {
    // range check, print error to debug output if failed
    if (fLow < MIN_CUTOFF_FREQUENCY || fHigh > MAX_CUTOFF_FREQUENCY || fLow > fHigh) {
        DBG("DJAudioPlayer::setCutoffFrequency: cutoff frequency must be between " <<
            MIN_CUTOFF_FREQUENCY << " and " << MAX_CUTOFF_FREQUENCY << newLine);
    }
    // otherwise, update HPF, LPF filter coefficients
    else {
        lpfSource.setCoefficients(IIRCoefficients::makeLowPass(sampleRate, fHigh));
        hpfSource.setCoefficients(IIRCoefficients::makeHighPass(sampleRate, fLow));
    }
}

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
void DJAudioPlayer::setFrequencyDisplay(FrequencyDisplay* _frequencyDisplay) {
    // associate with passed frequency display
    frequencyDisplay = _frequencyDisplay;
}

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
void DJAudioPlayer::setGain(double gain) {
    // range check, if failed, print error to debug output
    if (gain < 0 || gain > MAX_GAIN) {
        DBG("DJAudioPlayer::setGain: gain should be between 0 and " << MAX_GAIN << "\n");
    }
    // otherwise, update volume gain
    else {
        transportSource.setGain(gain);
    }
}

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
void DJAudioPlayer::setPosition(double posInSecs) {
    // range check, if failed print error to debug
    if (posInSecs < 0 || posInSecs > transportSource.getLengthInSeconds()) {
        DBG("DJAudioPlayer::setPosition: range check failed");
    }
    // otherwise, update playback position
    else {
        transportSource.setPosition(posInSecs);
    }
}

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
void DJAudioPlayer::setPositionRelative(double pos) {
    // range check, on fail, print error to debug
    if (pos < 0 || pos > 1) {
        DBG("DJAudioPlayer::setPositionRelative: ratio should be between 0 and 1\n");
    }
    // otherwise, update relative playback position
    else {
        double posInSecs = pos * transportSource.getLengthInSeconds();
        setPosition(posInSecs);
    }
}

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
void DJAudioPlayer::setSpeed(double ratio) {
    // range check, on fail, print error to debug
    if (ratio < MIN_SPEED || ratio > MAX_SPEED) {
        DBG("DJAudioPlayer::setSpeed: ratio should be between " << MIN_SPEED << 
            " and " << MAX_SPEED << newLine);
    }
    // otherwise set playback speed
    else {
        speed = ratio;
        resampleSource.setResamplingRatio(ratio);
    }
}

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
double DJAudioPlayer::getDuration() {
    return transportSource.getLengthInSeconds();
}

/******************************************
* Name:
*  getID
* Description:
*  getter for the associated track ID.
* Parameters:
*  N/A
* Output:
*  ID of the associated track.
*******************************************/
int DJAudioPlayer::getID() {
    return id;
}

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
double DJAudioPlayer::getPositionRelative() {
    // get current pos and total duration
    auto pos = transportSource.getCurrentPosition();
    auto total = transportSource.getLengthInSeconds();

    // compute relative position and return
    if (abs(total) < 1e-4) {
        return 0;
    }
    return pos / total;
}

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
void DJAudioPlayer::loadURL(URL audioURL) {
    // create reader using format manager
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    
    // if successfulc reation, pass into reader source and add as input to transport source.
    if (reader != nullptr) {    // good file!
        std::unique_ptr<AudioFormatReaderSource> newSource(
            new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }

}

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
void DJAudioPlayer::start() {
    DBG(transportSource.getCurrentPosition());
    transportSource.start();
}

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
void DJAudioPlayer::stop() {
    transportSource.stop();
    DBG(transportSource.getCurrentPosition());
}

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
void DJAudioPlayer::rewind() {
    transportSource.stop();
    transportSource.setPosition(0);
}

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
void DJAudioPlayer::fastForward() {
    setPosition(transportSource.getCurrentPosition() + speed);
}

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
void DJAudioPlayer::fastReverse() {
    setPosition(transportSource.getCurrentPosition() - speed);
}

const double DJAudioPlayer::MIN_GAIN=0.0;
const double DJAudioPlayer::MAX_GAIN = 2.0;
const double DJAudioPlayer::INTERVAL_GAIN=0.05;
const double DJAudioPlayer::DEFAULT_GAIN=1.0;

const double DJAudioPlayer::MIN_SPEED = 0.5;
const double DJAudioPlayer::MAX_SPEED = 10;
const double DJAudioPlayer::INTERVAL_SPEED = 0.1;
const double DJAudioPlayer::DEFAULT_SPEED = 1.0;

const double DJAudioPlayer::MIN_CUTOFF_FREQUENCY = 20;
const double DJAudioPlayer::MAX_CUTOFF_FREQUENCY = 20000;
const double DJAudioPlayer::INTERVAL_CUTOFF_FREQUENCY=1;