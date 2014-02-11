/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
const float defaultDelay = 0.5f;
const float defaultGain = 0.5f;

// Input buffer
float lastSamples[4] = {0,0,0,0};

// Output buffer
float lastOutputs[4] = {0,0,0,0};

//==============================================================================
A3AudioProcessor::A3AudioProcessor()
    : delayBuffer (2, 12000)
{
    // Set up some default values..
    gain = defaultGain;
    delay = defaultDelay;
    
    lastUIWidth = 400;
    lastUIHeight = 200;
    
    lastPosInfo.resetToDefault();
    delayPosition = 0;
}

A3AudioProcessor::~A3AudioProcessor()
{
}

//==============================================================================

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
        case delayParam:    return 0;
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
        case gainParam:     gain = newValue;  break;
        case delayParam:    delay = newValue;  break;
        default:            break;
    }
}

float A3AudioProcessor::getParameterDefaultValue (int index)
{
    switch (index)
    {
        case gainParam:     return defaultGain;
        case delayParam:    return defaultDelay;
        default:            break;
    }
    
    return 0.0f;
}

const String A3AudioProcessor::getParameterName (int index)
{
    switch (index)
    {
        case gainParam:     return "gain";
        case delayParam:    return "delay";
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

void A3AudioProcessor::reset()
{
    // Use this method as the place to clear any delay lines, buffers, etc, as it
    // means there's been a break in the audio's continuity.
    delayBuffer.clear();
}


void A3AudioProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    int channel;
    const int numSamples = buffer.getNumSamples();
    float in;
    
    // Low-Pass
    for (channel = 0; channel < getNumInputChannels(); ++channel) {
        float* channelData = buffer.getSampleData(channel);

        for (int i = 0; i < numSamples; ++i) {
            in = channelData[i];
           
            channelData[i] = gain * (in +
                                     2 * cos(delay) * lastSamples[channel * 2 + !(i % 2)] -
                                     .5 * lastSamples[channel * 2 + i % 2]);
            // channelData[i] = gain * (in
            //                        + 2 * lastSamples[channel * 2 + i % 2]
            //                        + lastSamples[channel * 2 + !(i % 2)]);
            
            lastSamples[channel * getNumInputChannels() + (i % 2)] = in;
            lastOutputs[channel * getNumInputChannels() + (i % 2)] = channelData[i];
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
    xml.setAttribute ("delay", delay);
    
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
            delay = (float) xmlState->getDoubleAttribute ("delay", delay);
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
