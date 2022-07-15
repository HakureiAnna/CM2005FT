/*
  ==============================================================================

    FrequencyDisplay.h
    Created: 9 Mar 2022 3:43:13pm
    Author:  Anna

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;
using namespace juce::dsp;

//==============================================================================
/*
*/
class FrequencyDisplay  : public juce::Component
{
public:
    // constructors & destructors
    /******************************************
    * Name:
    *  FrequencyDisplay
    * Description:
    *  Constructor for the FrequencyDisplay class. initialize members.
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    FrequencyDisplay();

    // base class overrides
    /******************************************
    * Name:
    *  paint
    * Description :
    *  override of base class paint method. Used to draw the frequency domain
    *  waveform.
    * Parameters :
    *  g: reference to Graphics used for drawing
    * Output :
    *  N/A
    *******************************************/
    void paint (juce::Graphics& g) override;

    // methods
    /******************************************
    * Name:
    *  pushNextSample
    * Description:
    *  called by the getNextAudioBlock of each DJAudioPlayer 
    *  in order to load samples into the buffer for FFT processing.
    * Parameters:
    *  sample: a single sample to load into the buffer
    * Output:
    *  N/A
    *******************************************/
    void pushNextSample(float sample);

    /******************************************
    * Name:
    *  drawNextTrace
    * Description:
    *  perform FFT and normalize the output levels
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void drawNextTrace();

    /******************************************
    * Name:
    *  updateFFT
    * Description:
    *  called from deck player component timer callback to 
    *  perform FFT and redraw frequency data
    * Parameters:
    *  N/A
    * Output:
    *  N/A
    *******************************************/
    void updateFFT();

private:
    // functionality members
    // FFT related members
    static const int FFT_ORDER = 11;
    static const int SIZE_FFT = 1 << FFT_ORDER;
    static const int SIZE_SCOPE = 512;
    FFT fft;
    WindowingFunction<float> window;
    float fifo[SIZE_FFT];
    float fftData[2 * SIZE_FFT];
    int fifoId = 0;
    bool nextFFTBlockReady = false;
    float scopeData[SIZE_SCOPE];
    
    // colour gradient for drawing
    ColourGradient gradient;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FrequencyDisplay)
};
