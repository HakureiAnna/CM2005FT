/*
  ==============================================================================

    FrequencyDisplay.cpp
    Created: 9 Mar 2022 3:43:13pm
    Author:  Anna

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FrequencyDisplay.h"

//==============================================================================
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
FrequencyDisplay::FrequencyDisplay() :
    fft(FFT_ORDER),
    window(SIZE_FFT, WindowingFunction<float>::hann),
    gradient(Colour::fromRGB(3, 2, 252), 0, 0, Colour::fromRGB(254, 0, 2), 1, 1, false)
{
    // set up more colours within the gradient to make the changes in level more obvious
    gradient.addColour(0.25, Colour::fromRGB(11, 84, 254));
    gradient.addColour(0.5, Colour::fromRGB(132, 50, 223));
    gradient.addColour(0.75, Colour::fromRGB(252, 15, 192));
}

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
void FrequencyDisplay::paint (juce::Graphics& g)
{
    // get component width and height
    auto width = getLocalBounds().getWidth();
    auto height = getLocalBounds().getHeight();
    // get width per slice in the scope data
    auto w = width / SIZE_SCOPE;
    // if width per slice is less than 1, fix to 1
    if (w < 1) {
        w = 1;
    }
    // paint background
    g.setColour(Colours::black);
    g.fillAll();

    // process frequency data piece by piece and paint output slice by slice
    for (int i = 1; i < SIZE_SCOPE; ++i)
    {
        // set colour according to level at current frequency range
        g.setColour(gradient.getColourAtPosition(scopeData[i]));
        auto y = (int)jmap(1-scopeData[i], 0.0f, 1.0f, 0.0f, (float)height);
        auto h = (int)jmap(scopeData[i], 0.0f, 1.0f, 0.0f, (float)height);
        if (y > 0 && h > 0)
        g.fillRect(i - 1, y, w, h);
    }

}

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
void FrequencyDisplay::pushNextSample(float sample) {
    // load one more sample into the fft data buffer and update
    // index as necessary
    if (fifoId == SIZE_FFT) {
        if (!nextFFTBlockReady) {
            zeromem(fftData, sizeof(fftData));
            memcpy(fftData, fifo, sizeof(fifo));
            nextFFTBlockReady = true;
        }

        fifoId = 0;
    }
    fifo[fifoId++] = sample;
}

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
void FrequencyDisplay::drawNextTrace() {
    // perform FFT using windowing function
    window.multiplyWithWindowingTable(fftData, SIZE_FFT);
    fft.performFrequencyOnlyForwardTransform(fftData);

    auto mindB = -100.0f;
    auto maxdB = 0.0f;

    // normalize all sample and take only the relevant frequency range (remove mirrored part)
    for (auto i = 0; i < SIZE_SCOPE; ++i) {
        auto skewedProportionX = 1.0f - std::exp(std::log(1.0f - 
            (float)i / (float)SIZE_SCOPE) * 0.2f);
        auto fftDataId = jlimit(0, SIZE_FFT / 2, 
            (int)(skewedProportionX * (float)SIZE_FFT * 0.5));
        auto level = jmap(jlimit(mindB, maxdB, Decibels::gainToDecibels(fftData[fftDataId])
            - Decibels::gainToDecibels((float)SIZE_FFT)), mindB, maxdB, 0.0f, 1.0f);
        scopeData[i] = level;
    }
}

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
void FrequencyDisplay::updateFFT() {
    if (nextFFTBlockReady) {
        // perform FFT and normalization
        drawNextTrace();
        // set flag to false to start gathering more input sample
        nextFFTBlockReady = false;
        // redraw the frequency visualization
        repaint();
    }
}
