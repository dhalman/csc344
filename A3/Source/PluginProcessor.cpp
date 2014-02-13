/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <complex.h>

#define NUM_POLES 4

const float defaultfrequency = 100;
const float defaultGain = .5f;
double cutoff;

// Input buffer
double lastSamples[2 * NUM_POLES] = {0,0,0,0,0,0,0,0};

// Output buffer
double lastOutputs[2 * NUM_POLES] = {0,0,0,0,0,0,0,0};

std::complex<double> sPoles[NUM_POLES];
std::complex<double> zPoles[NUM_POLES];
std::complex<double> coefs[NUM_POLES];

int pyth[NUM_POLES] = {4, 6, 4, 1};

double resonance = .5;
double gainFactor;


const std::complex<double> imag = std::sqrt(std::complex<double>(-1));

//==============================================================================
A3AudioProcessor::A3AudioProcessor()
    : delayBuffer (2, 12000)
{
    // Set up some default values..
    gain = defaultGain;
    frequency = defaultfrequency;
    
    lastUIWidth = 400;
    lastUIHeight = 200;
    
    lastPosInfo.resetToDefault();
    delayPosition = 0;

    for (int i = 0; i < NUM_POLES; ++i) {
        //sPoles[i] = imag * cos(acos(imag / resonance) / (double)NUM_POLES + (i + 1) * 2 * 3.14 / NUM_POLES);
        sPoles[i] = imag * cos((1.0 / 4.0) * acos((imag/0.5)) + (((i) * double_Pi) / 4));
    }
    
    setParameter(freqParam, defaultfrequency);
    calcCoefs();
    
    std::cout<<"SampleRate: " << getSampleRate() << std::endl;
    printPoles(coefs);
}

A3AudioProcessor::~A3AudioProcessor()
{
}

//==============================================================================
void A3AudioProcessor::printPoles(std::complex<double> *poles) {
    std::cout<<"\nCutoff: "<<cutoff<<" Radians, "<<frequency<<" Hz"<<std::endl;
    std::cout<<"SampleRate: "<<getSampleRate()<<std::endl;
    std::cout<<"GainFactor: "<<gainFactor<<std::endl;
    std::cout<<"Poles:"<<std::endl;
    
    for (int i = 0; i < NUM_POLES; ++i) {
        std::cout<<" "<<poles[i].real()<<" + J"<<poles[i].imag()<<std::endl;
    }
    
}

void A3AudioProcessor::calcCoefs() {
    gainFactor = 1;
    
    for (int i = 0; i < NUM_POLES; ++i) {
        zPoles[i] = (1.0 + (sPoles[i] * cutoff / 2.0)) / (1.0 - (sPoles[i] * cutoff / 2.0));
    }
    
    coefs[0] = -1.0 * (zPoles[0] + zPoles[1] + zPoles[2] + zPoles[3]);
    
    coefs[1] = (zPoles[0] * zPoles[1]) + (zPoles[0] * zPoles[2]) +
               (zPoles[0] * zPoles[3]) + (zPoles[1] * zPoles[2]) +
               (zPoles[1] * zPoles[3]) + (zPoles[2] * zPoles[3]);
    
    coefs[2] = -1.0 * ((zPoles[0] * zPoles[1] * zPoles[2]) +
                       (zPoles[0] * zPoles[1] * zPoles[3]) +
                       (zPoles[0] * zPoles[2] * zPoles[3]) +
                       (zPoles[1] * zPoles[2] * zPoles[3]));
    
    coefs[3] = zPoles[0] * zPoles[1] * zPoles[2] * zPoles[3];
    
    for (int i = 0; i < 4; ++i) {
        gainFactor += coefs[i].real();
    }
}

int A3AudioProcessor::getNumParameters()
{
    return totalNumParams;
}

float A3AudioProcessor::getParameter (int index)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case gainParam:     return 0;
        case freqParam:     return 0;
        default:            return 0.0f;
    }
}

void A3AudioProcessor::setParameter (int index, float newValue)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case gainParam:
            gain = newValue;
            break;
        case freqParam:
            frequency = newValue;
            cutoff = (newValue / ((getSampleRate() ?: 44100) / 2.0)) * double_Pi;
            calcCoefs();
            break;
        default:
            break;
    }
}

float A3AudioProcessor::getParameterDefaultValue (int index)
{
    switch (index)
    {
        case gainParam:     return defaultGain;
        case freqParam:    return defaultfrequency;
        default:            break;
    }
    
    return 0.0f;
}

const String A3AudioProcessor::getParameterName (int index)
{
    switch (index)
    {
        case gainParam:     return "gain";
        case freqParam:     return "frequency";
        default:            break;
    }
    
    return String::empty;
}

const String A3AudioProcessor::getParameterText (int index)
{
    return String (getParameter (index), 2);
}

//==============================================================================
void A3AudioProcessor::prepareToPlay (double sampleRate, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate (sampleRate);
    keyboardState.reset();
    delayBuffer.clear();
}

void A3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
}

void A3AudioProcessor::reset() {
    // Use this method as the place to clear any frequency lines, buffers, etc, as it
    // means there's been a break in the audio's continuity.
    delayBuffer.clear();
}

// Return the index of the specified delay value within the buffer
int A3AudioProcessor::getDelayIndex(int bufferIndex, int delayValue) {
    int delayIndex = bufferIndex - delayValue;
    
    // Handle wrap-around
    return delayIndex < 0 ? NUM_POLES + delayIndex : delayIndex;
}

void A3AudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages) {
    int channel, bufferIndex;
    const int numSamples = buffer.getNumSamples();
    double in;
    
    // Low-Pass
    for (channel = 0; channel < getNumInputChannels(); ++channel) {
        float* channelData = buffer.getSampleData(channel);

        for (int i = 0; i < numSamples; ++i) {
            channelData[i] *= gainFactor * gain;
           
            //channelData[i] = (i%30) * (1/30.0);
            //in = channelData[i];
            //std::cout<<"Input["<<i<<"]: "<<in<<" ("<<(i%30)*(1/30.0)<<")"<<std::endl;;

            bufferIndex = i % NUM_POLES;
            //std::cout<<"BufferIndex: "<<bufferIndex<<std::endl;;

            
            for (int j = 0; j < NUM_POLES; ++j) {
                channelData[i] -=
                // lastSamples[offset + getDelayIndex(bufferIndex, j+1)] -
                
                lastOutputs[channel + getNumInputChannels() * getDelayIndex(bufferIndex, j+1)] * coefs[j].real();
               
                //    std::cout<<" -= lastOutputs["<<getDelayIndex(bufferIndex, j+1)<<"] * coefs["<<j<<"] (";
                //std::cout<<lastOutputs[offset + getDelayIndex(bufferIndex, j+1)]<<" * ";
                //std::cout<<coefs[j].real()<<")"<<std::endl;;

            }

            //channelData[i] *= gainFactor * gain;
            //std::cout<<" *= GainFactor: "<<gainFactor<<std::endl;
            //lastSamples[offset + bufferIndex] = in;
            lastOutputs[channel + getNumInputChannels() * bufferIndex] = channelData[i];
            //std::cout<<" Output["<<i<<"]: "<<channelData[i]<<std::endl;
        }
    }

    // In case we have more outputs than inputs, we'll clear any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i) {
        buffer.clear (i, 0, buffer.getNumSamples());
    }
}

//==============================================================================
AudioProcessorEditor* A3AudioProcessor::createEditor()
{
    return new A3AudioProcessorEditor (this);
}

//==============================================================================
void A3AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // Here's an example of how you can use XML to make it easy and more robust:
    
    // Create an outer XML element..
    XmlElement xml ("MYPLUGINSETTINGS");
    
    // add some attributes to it..
    xml.setAttribute ("uiWidth", lastUIWidth);
    xml.setAttribute ("uiHeight", lastUIHeight);
    xml.setAttribute ("gain", gain);
    xml.setAttribute ("frequency", frequency);
    
    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}

void A3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("MYPLUGINSETTINGS"))
        {
            // ok, now pull out our parameters..
            lastUIWidth  = xmlState->getIntAttribute ("uiWidth", lastUIWidth);
            lastUIHeight = xmlState->getIntAttribute ("uiHeight", lastUIHeight);
            
            gain  = (float) xmlState->getDoubleAttribute ("gain", gain);
            frequency = (float) xmlState->getDoubleAttribute ("frequency", frequency);
        }
    }
}

const String A3AudioProcessor::getInputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

const String A3AudioProcessor::getOutputChannelName (const int channelIndex) const
{
    return String (channelIndex + 1);
}

bool A3AudioProcessor::isInputChannelStereoPair (int /*index*/) const
{
    return true;
}

bool A3AudioProcessor::isOutputChannelStereoPair (int /*index*/) const
{
    return true;
}

bool A3AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool A3AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool A3AudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double A3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new A3AudioProcessor();
}
