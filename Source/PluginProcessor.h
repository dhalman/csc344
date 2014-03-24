/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class WaveSound : public SynthesiserSound
{
public:
    WaveSound() {}
    
    bool appliesToNote (const int /*midiNoteNumber*/)           { return true; }
    bool appliesToChannel (const int /*midiChannel*/)           { return true; }
};

//==============================================================================


class Csc344finalAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Csc344finalAudioProcessor();
    ~Csc344finalAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const override { return true; };

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    
    MidiKeyboardState keyboardState;
    
    void setSinFreq(double newVal);
    
    void setSinAmp(double newVal);
    
    void setSawFreq(double newVal);
    
    void setSawAmp(double newVal);
    
    void setLfo1Freq(double newVal);
    
    void setLfo1Amp(double newVal);
    
    void setLfo2Freq(double newVal);
    
    void setLfo2Amp(double newVal);
    
    void setEnv1AttackTime(double newVal);
    
    void setEnv1AttackLevel(double newVal);
    
    void setEnv1DecayTime(double newVal);
    
    void setEnv1SustainLevel(double newVal);
    
    void setEnv1ReleaseTime(double newVal);
    
    void setEnv2AttackTime(double newVal);
    
    void setEnv2AttackLevel(double newVal);
    
    void setEnv2DecayTime(double newVal);
    
    void setEnv2SustainLevel(double newVal);
    
    void setEnv2ReleaseTime(double newVal);
    
    void setLowPassAmp(double newVal);
    
    void setLowPassFreq(double newVal);
    
    void setLowPassReso(double newVal);
    
    float getParameterDefaultValue(int index);
    
    enum Parameters
    {
        sinFreq = 0, sinAmp,
        sawFreq, sawAmp,
        sinFreqMod, sinAmpMod,
        sawFreqMod, sawAmpMod,
        lfo1Freq, lfo1Amp,
        lfo2Freq, lfo2Amp,
        env1AT, env1AL, env1DT, env1SL, env1RT,
        env2AT, env2AL, env2DT, env2SL, env2RT,
        filterFreq, filterAmp, filterReso,
        
        totalNumParams
    };


private:
    Synthesiser sinSynth, sawSynth;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Csc344finalAudioProcessor)
    
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
