/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <thread>

//==============================================================================


//==============================================================================

// A simple linear envelope, allows custom parameters
class SynthEnvelope : public ReferenceCountedObject {
public:
    SynthEnvelope()
    : output (0),
    attackLevel (1),
    attackTime (0),
    decayTime (0),
    sustainLevel (1),
    releaseTime (0),
    state (ENV_ATTACK),
    sampleRate (0)
    {
        init = false;
    }
    
    SynthEnvelope(double newOutput, double newAttackLevel, double newAttackTime,
                  double newDecayTime, double newSustainLevel, double newReleaseTime,
                  double newSampleRate) {
        output = newOutput;
        attackLevel = newAttackLevel;
        attackTime = newAttackTime;
        decayTime = newDecayTime;
        sustainLevel = newSustainLevel;
        releaseTime = newReleaseTime;
        state = ENV_ATTACK;
        sampleRate = newSampleRate;
        
        initEnvelope();
    }
    
    enum {
        ENV_ATTACK, ENV_DECAY, ENV_SUSTAIN, ENV_RELEASE
    };
    
    // Perform after all initial values have been set.
    void initEnvelope() {
        attackDelta = 1 / (attackTime * sampleRate);
        decayDelta =  1 / (decayTime * sampleRate);
        releaseDelta = 1 / (releaseTime * sampleRate);
        
        if (sampleRate == 0) {
            std::cout << "Envelope Error: Sample rate not set." << std::endl;
            init = false;
        } else {
            init = true;
        }
    }
    
    void reset() {
        output = 0;
        state = ENV_ATTACK;
    }
    
    // Must be called before initEnvelope()
    void setSampleRate(double newSampleRate) {
        sampleRate = newSampleRate;
    }
    
    void setState(int newState) {
        state = newState;
    }
    
    void setOutput(double newOutput) {
        output = newOutput;
    }
    
    void setAttackTime(double newTime) {
        attackTime = newTime;
        attackDelta = 1 / (attackTime * sampleRate);
    }
    
    void setAttackLevel(double newLevel) {
        attackLevel = newLevel;
    }
    
    void setDecayTime(double newTime) {
        decayTime = newTime;
        decayDelta = 1 / (decayTime * sampleRate);
    }
    
    void setSustainLevel(double newLevel) {
        sustainLevel = newLevel;
    }
    
    void setReleaseTime(double newReleaseTime) {
        releaseTime = newReleaseTime;
        releaseDelta = 1 / (releaseTime * sampleRate);
    }
    
    void release() {
        state = ENV_RELEASE;
    }
    
    double getOutput() {
        return output;
    }
    
    int getState() {
        return state;
    }
    
    // Iterates through envelope shape. Returns false when complete.
    bool stepEnvelope() {
        if (!init) {
            initEnvelope();
        }
        
        switch (state) {
            case ENV_ATTACK:
                output += attackDelta;
                
                if (output >= attackLevel) {
                    output = attackLevel;
                    state = ENV_DECAY;
                }
                break;
                
            case ENV_DECAY:
                output -= decayDelta;
                
                if (output <= sustainLevel) {
                    output = sustainLevel;
                    state = ENV_SUSTAIN;
                }
                break;
                
            case ENV_SUSTAIN:
                // Do nothing really
                break;
                
            case ENV_RELEASE:
                output -= releaseDelta;
                
                if (output <= 0) {
                    output = 0;
                    
                    // We're done here
                    return false;
                }
                break;
                
            default:
                break;
        }
        
        return true;
    }
    
    double output;
private:
    double  attackLevel, attackTime, decayTime, sustainLevel, releaseTime;
    double attackDelta, decayDelta, releaseDelta;
    int state;
    double sampleRate;
    bool init = false;
};

/* A simple lfo with adjustable rate and depth */
class SynthLfo : public ReferenceCountedObject {
public:
    SynthLfo()
    : output (0.0),
      angle (0.0),
      angleDelta (0.0),
      depth (0.0),
      sampleRate (0)
    {
        init = false;
    }
    
    void setSampleRate(int newSampleRate) {
        sampleRate = newSampleRate;
        init = !!sampleRate;
    }
    
    void setAngle(double newAngle) {
        angle = newAngle;
    }
    
    void setFrequency(double newFrequency) {
        angleDelta = newFrequency / sampleRate * 2.0 * double_Pi;
    }
    
    void setDepth(double newDepth) {
        depth = newDepth;
    }
    
    void stepLfo() {
        angle += angleDelta;
        output = depth * sin(angle);
    }
    
    double getOutput() {
        if (!init) {
            std::cout << "LFO Not initialized. Sample rate not set." << std::endl;
            return 0;
        }
        
        return output;
    }
    
    double output;
private:
    double angle, angleDelta, depth, sampleRate;
    bool init;
};

/* A simple demo synth voice that just plays a little more than a sine wave.. */
class OscillatorVoice  : public SynthesiserVoice
{
public:
    OscillatorVoice(SynthLfo *l1, SynthLfo *l2, SynthEnvelope *e1, SynthEnvelope *e2)
    : angleDelta (0.0)
    {
        lfo1 = l1;
        lfo2 = l2;
        env1 = e1;
        env2 = e2;
        
        if (env1) {
            env1->setSampleRate(getSampleRate());
            env2->setSampleRate(getSampleRate());
            
            // Init last (Requires sample rate and env times to be set).
            env1->initEnvelope();
            env2->initEnvelope();

            lfo1->setSampleRate(getSampleRate());
            lfo2->setSampleRate(getSampleRate());
        }
        
        setFreqMod(NONE);
        setAmpMod(NONE);
    }
    
    SynthEnvelope *env1 = nullptr;
    SynthEnvelope *env2 = nullptr;
    SynthLfo *lfo1 = nullptr;
    SynthLfo *lfo2 = nullptr;
    
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast <WaveSound*> (sound) != 0;
    }
    
    void modifyLfo(double lfoPerSecond, double *lfoDelta) {
        double lfoPerSample = lfoPerSecond / getSampleRate();
        *lfoDelta = lfoPerSample * 2.0 * double_Pi;
    }
    
    
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/)
    {
        currentAngle = 0;
        midiNumber = midiNoteNumber;
        
        setFrequency(oscillatorFreq);
        setMode(mode);
    }
    
    void stopNote (bool allowTailOff) {
            clearCurrentNote();
            angleDelta = 0.0;
    }
    
    void pitchWheelMoved (int /*newValue*/)
    {
    }
    
    void controllerMoved (int /*controllerNumber*/, int /*newValue*/)
    {
    }
    
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
    {
        if (angleDelta != 0.0)
        {
            while (--numSamples >= 0)
            {
                // Mono output
                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    *outputBuffer.getSampleData(i, startSample) += getOutput();
               
                // Increment oscillators
                stepModifiers();
                stepOscillator();
                
                ++startSample;
            }
        }
    }
    
    void stepModifiers() {
        if (lfo1) {
            lfo1->stepLfo();
        }
        if (lfo2) {
            lfo2->stepLfo();
        }
        if (env1) {
            env1->stepEnvelope();
        }
        if (env2) {
            env2->stepEnvelope();
        }
    }
    
    void setMode(int newMode) {
        if (newMode == SINE) {
            mode = SINE;
            angleDelta = oscillatorFreq / getSampleRate() * 2.0 * double_Pi;
        } else if (newMode == SAW) {
            mode = SAW;
            angleDelta = 2 * level * oscillatorFreq / getSampleRate();
        } else {
            // Do nothing if mode not supported
        }
    }
    
    void setCurrentAngle(double newAngle) {
        currentAngle = newAngle;
    }
    
    void stepOscillator() {
        // Don't mess with base angleDelta
        double tmpDelta = angleDelta;
        
        if (freqMod != nullptr) {
            // Multiplying env output creates a linear pitch shift based on env shape
            // Max frequency is angleDelta * max env level
            if (freqModIndex == LFO1 || freqModIndex == LFO2) {
                // Add lfo offset
                tmpDelta += *freqMod;
            } else if (freqModIndex == ENV1 || freqModIndex == ENV2) {
                // Multiply by env output
                tmpDelta *= *freqMod;
            }
        }
        
        currentAngle += tmpDelta;
        
        // Reset saw if in saw mode and period is up
        if (mode == SAW && currentAngle >= level) {
            currentAngle = level * -1;
        }
    }
    
    void setFrequency(double newFrequency) {
        oscillatorFreq = newFrequency;
        //angleDelta = newFrequency / getSampleRate() * 2.0 * double_Pi;
    }
    
    void setAmplitude(double newAmplitude) {
        level = newAmplitude;
    }
    
    double getOutput() {
        double tmpLevel = level;

        if (ampMod != nullptr) {
            tmpLevel *= *ampMod;
        }
        
        return tmpLevel * (mode == SINE ? sin(currentAngle) : currentAngle);
    }
    
    void setFreqMod(int index) {
        freqModIndex = index;
        std::cout<<"Freq mod index: "<<index<<std::endl;

        if (index == 0) {
            freqMod = &lfo1->output;
        } else if (index == 1) {
            freqMod = &lfo2->output;
        } else if (index == 2) {
            freqMod = &env1->output;
        } else if (index == 3) {
            freqMod = &env2->output;
        } else {
            freqMod = nullptr;
        }
    }
    
    void setAmpMod(int index) {
        ampModIndex = index;
        std::cout<<"Amp mod index: "<<index<<std::endl;
        if (index == 0) {
            ampMod = &lfo1->output;
        } else if (index == 1) {
            ampMod = &lfo2->output;
        } else if (index == 2) {
            ampMod = &env1->output;
        } else if (index == 3) {
            ampMod = &env2->output;
        } else {
            ampMod = nullptr;
        }
    }
    
    enum {
        SINE, SAW
    };
    
    
    enum {
        LFO1, LFO2, ENV1, ENV2, NONE
    };
private:
    double currentAngle, angleDelta, level;
    double oscillatorFreq;
    int midiNumber;
    int mode = SINE;
    int freqModIndex, ampModIndex;
    double *freqMod = nullptr, *ampMod = nullptr;
};

OscillatorVoice *sinVoice, *sawVoice;
SynthLfo *lfo1, *lfo2;
SynthEnvelope *env1, *env2;


//==============================================================================
Csc344finalAudioProcessor::Csc344finalAudioProcessor()
{
    env1 = new SynthEnvelope();
    env2 = new SynthEnvelope();
    lfo1 = new SynthLfo();
    lfo2 = new SynthLfo();
    
    sinVoice = new OscillatorVoice(lfo1, lfo2, env1, env2);
    sawVoice = new OscillatorVoice(lfo1, lfo2, env1, env2);
    
    sinVoice->setAmplitude(.5);
    sawVoice->setAmplitude(0);
    
    sinVoice->setMode(sinVoice->SINE);
    sawVoice->setMode(sawVoice->SAW);
    
    sinSynth.addVoice(sinVoice);
    sawSynth.addVoice(sawVoice);
 
    sinSynth.addSound(new WaveSound());
    sawSynth.addSound(new WaveSound());
}

Csc344finalAudioProcessor::~Csc344finalAudioProcessor()
{
}

//==============================================================================
const String Csc344finalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int Csc344finalAudioProcessor::getNumParameters()
{

    return 25;
}

float Csc344finalAudioProcessor::getParameter (int index)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case sinFreq:     return 0;
        case sinAmp:     return 0;
        case sawFreq:     return 0;
        case sawAmp:   return 0;
        case sinFreqMod:     return 0;
        case sinAmpMod:     return 0;
        case sawFreqMod:     return 0;
        case sawAmpMod:   return 0;
        case lfo1Freq:     return 0;
        case lfo1Amp:     return 0;
        case lfo2Freq:     return 0;
        case lfo2Amp:   return 0;
        case env1AT:     return 0;
        case env1AL:     return 0;
        case env1DT:     return 0;
        case env1SL:   return 0;
        case env1RT:     return 0;
        case env2AT:     return 0;
        case env2AL:     return 0;
        case env2DT:     return 0;
        case env2SL:   return 0;
        case env2RT:     return 0;
        case filterFreq:     return 0;
        case filterAmp:   return 0;
        case filterReso:     return 0;
        default:            return 0.0f;
         
    }
}

void Csc344finalAudioProcessor::setParameter (int index, float newValue)
{
    // This method will be called by the host, probably on the audio thread, so
    // it's absolutely time-critical. Don't use critical sections or anything
    // UI-related, or anything at all that may block in any way!
    switch (index)
    {
        case sinFreq:
            setSinFreq(newValue);
            break;
        case sinAmp:
            setSinAmp(newValue);
            break;
        case sawFreq:
            setSawFreq(newValue);
            break;
        case sawAmp:
            setSawAmp(newValue);

            break;
        case sinFreqMod:
            setSinFreqMod(newValue);
            
            break;
        case sinAmpMod:
            setSinAmpMod(newValue);
            
            break;
        case sawFreqMod:
            setSawFreqMod(newValue);
            
            break;
        case sawAmpMod:
            setSawAmpMod(newValue);
            
            break;
        case lfo1Freq:
            setLfo1Freq(newValue);
            
            break;
        case lfo1Amp:
            setLfo1Amp(newValue);
            
            break;
        case lfo2Freq:
            setLfo2Freq(newValue);
            
            break;
        case lfo2Amp:
            setLfo2Amp(newValue);
            
            break;
        case env1AT:
            setEnv1AttackTime(newValue);
            
            break;
        case env1AL:
            setEnv1AttackLevel(newValue);

            break;
        case env1DT:
            setEnv1DecayTime(newValue);

            break;
        case env1SL:
            setEnv1SustainLevel(newValue);

            break;
        case env1RT:
            setEnv1ReleaseTime(newValue);

            break;
        case env2AT:
            setEnv2AttackTime(newValue);
            
            break;
        case env2AL:
            setEnv2AttackLevel(newValue);
            
            break;
        case env2DT:
            setEnv2DecayTime(newValue);
            
            break;
        case env2SL:
            setEnv2SustainLevel(newValue);
            
            break;
        case env2RT:
            setEnv2ReleaseTime(newValue);
            
            break;
        case filterFreq:
            setLowPassFreq(newValue);
            
            break;
        case filterAmp:
            setLowPassAmp(newValue);
            
            break;
        case filterReso:
            setLowPassReso(newValue);
            
            break;
        default:
            break;
    }
}

float Csc344finalAudioProcessor::getParameterDefaultValue (int index)
{
    switch (index)
    {
        case sinFreq:       return 400;
        case sinAmp:        return 1;
        case sawFreq:       return 400;
        case sawAmp:        return 0;
        case sinFreqMod:    return 0;
        case sinAmpMod:     return 0;
        case sawFreqMod:    return 0;
        case sawAmpMod:     return 0;
        case lfo1Freq:      return 0;
        case lfo1Amp:       return 0;
        case lfo2Freq:      return 0;
        case lfo2Amp:       return 0;
        case env1AT:        return 0;
        case env1AL:        return 0;
        case env1DT:        return 0;
        case env1SL:        return 0;
        case env1RT:        return 0;
        case env2AT:        return 0;
        case env2AL:        return 0;
        case env2DT:        return 0;
        case env2SL:        return 0;
        case env2RT:        return 0;
        case filterFreq:    return 20000;
        case filterAmp:     return 0;
        case filterReso:    return 0;
        default:            return 0.0f;
    }
}

const String Csc344finalAudioProcessor::getParameterName (int index)
{
    switch (index)
    {
        case sinFreq:       return "Sin Frequency";
        case sinAmp:        return "Sin Amplitude";
        case sawFreq:       return "Saw Frequency";
        case sawAmp:        return "Saw amplitude";
        case sinFreqMod:    return "Sin Frequency Modifier";
        case sinAmpMod:     return "Sin Amplitude Modifier";
        case sawFreqMod:    return "Saw Frequency Modifier";
        case sawAmpMod:     return "Saw Amplitude Modifier";
        case lfo1Freq:      return "Lfo1 Frequency";
        case lfo1Amp:       return "Lfo1 Amplitude";
        case lfo2Freq:      return "Lfo2 Frequency";
        case lfo2Amp:       return "Lfo2 Amplitude";
        case env1AT:        return "Env1 Attack Time";
        case env1AL:        return "Env1 Attack Level";
        case env1DT:        return "Env1 Decay Time";
        case env1SL:        return "Env1 Sustain Level";
        case env1RT:        return "Env1 Release Time";
        case env2AT:        return "Env2 Attack Time";
        case env2AL:        return "Env2 Attack Level";
        case env2DT:        return "Env2 Decay Time";
        case env2SL:        return "Env2 Sustain Level";
        case env2RT:        return "Env2 Release Time";
        case filterFreq:    return "Filter Frequency";
        case filterAmp:     return "Filter Amplitude";
        case filterReso:    return "Filter Resonance";
        default:            break;
    }
    
    return String::empty;
}

const String Csc344finalAudioProcessor::getParameterText (int index)
{
    return String (getParameter (index), 2);
}

const String Csc344finalAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String Csc344finalAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool Csc344finalAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool Csc344finalAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool Csc344finalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Csc344finalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Csc344finalAudioProcessor::silenceInProducesSilenceOut() const
{
    return false;
}

double Csc344finalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Csc344finalAudioProcessor::getNumPrograms()
{
    return 0;
}

int Csc344finalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Csc344finalAudioProcessor::setCurrentProgram (int index)
{
}

const String Csc344finalAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void Csc344finalAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Csc344finalAudioProcessor::prepareToPlay (double sampleRate, int /*samplesPerBlock*/)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    sinSynth.setCurrentPlaybackSampleRate (sampleRate);
    sawSynth.setCurrentPlaybackSampleRate (sampleRate);
    keyboardState.reset();
}

void Csc344finalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    keyboardState.reset();
}

void Csc344finalAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int numSamples = buffer.getNumSamples();

    // Now pass any incoming midi messages to our keyboard state object, and let it
    // add messages to the buffer if the user is clicking on the on-screen keys
    keyboardState.processNextMidiBuffer (midiMessages, 0, numSamples, true);
    
    // and now get the synth to process these midi events and generate its output.
    sinSynth.renderNextBlock (buffer, midiMessages, 0, numSamples);
    sawSynth.renderNextBlock (buffer, midiMessages, 0, numSamples);
}

AudioProcessorEditor* Csc344finalAudioProcessor::createEditor()
{
    return new Csc344finalAudioProcessorEditor (this);
}

//==============================================================================
void Csc344finalAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Csc344finalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Csc344finalAudioProcessor();
}

void Csc344finalAudioProcessor::setSinFreq(double newVal){
    sinVoice->setFrequency(newVal);
}

void Csc344finalAudioProcessor::setSinAmp(double newVal){
    sinVoice->setAmplitude(newVal);
}

void Csc344finalAudioProcessor::setSawFreq(double newVal){
    sawVoice->setFrequency(newVal);
}

void Csc344finalAudioProcessor::setSawAmp(double newVal){
    sawVoice->setAmplitude(newVal);
}

void Csc344finalAudioProcessor::setLfo1Freq(double newVal){
    lfo1->setFrequency(newVal);
}

void Csc344finalAudioProcessor::setLfo1Amp(double newVal){
    lfo1->setDepth(newVal);
}

void Csc344finalAudioProcessor::setLfo2Freq(double newVal){
    lfo2->setFrequency(newVal);
}

void Csc344finalAudioProcessor::setLfo2Amp(double newVal){
    lfo2->setDepth(newVal);
}

void Csc344finalAudioProcessor::setEnv1AttackTime(double newVal){
    env1->setAttackTime(newVal);
}

void Csc344finalAudioProcessor::setEnv1AttackLevel(double newVal){
    env1->setAttackLevel(newVal);
}

void Csc344finalAudioProcessor::setEnv1DecayTime(double newVal){
    env1->setDecayTime(newVal);
}

void Csc344finalAudioProcessor::setEnv1SustainLevel(double newVal){
    env1->setSustainLevel(newVal);
}

void Csc344finalAudioProcessor::setEnv1ReleaseTime(double newVal){
    env1->setReleaseTime(newVal);
}

void Csc344finalAudioProcessor::setEnv2AttackTime(double newVal){
    env2->setAttackTime(newVal);
}

void Csc344finalAudioProcessor::setEnv2AttackLevel(double newVal){
    env2->setAttackLevel(newVal);
}

void Csc344finalAudioProcessor::setEnv2DecayTime(double newVal){
    env2->setDecayTime(newVal);
}

void Csc344finalAudioProcessor::setEnv2SustainLevel(double newVal){
    env2->setSustainLevel(newVal);
}

void Csc344finalAudioProcessor::setEnv2ReleaseTime(double newVal){
    env2->setReleaseTime(newVal);
}

void Csc344finalAudioProcessor::setLowPassAmp(double newVal){
    std::cout<<"test"<<std::endl;
}

void Csc344finalAudioProcessor::setLowPassFreq(double newVal){
    std::cout<<"test"<<std::endl;
}

void Csc344finalAudioProcessor::setLowPassReso(double newVal){
    std::cout<<"test"<<std::endl;
}
void Csc344finalAudioProcessor::setSinFreqMod(double newVal){
    sinVoice->setFreqMod(newVal);
}
void Csc344finalAudioProcessor::setSinAmpMod(double newVal){
    sinVoice->setAmpMod(newVal);
}
void Csc344finalAudioProcessor::setSawFreqMod(double newVal){
    sawVoice->setFreqMod(newVal);
}
void Csc344finalAudioProcessor::setSawAmpMod(double newVal){
    sawVoice->setAmpMod(newVal);
}


