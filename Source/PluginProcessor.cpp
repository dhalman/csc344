/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
class SineWaveSound : public SynthesiserSound
{
public:
    SineWaveSound() {}
    
    bool appliesToNote (const int /*midiNoteNumber*/)           { return true; }
    bool appliesToChannel (const int /*midiChannel*/)           { return true; }
};

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
    
private:
    double output, attackLevel, attackTime, decayTime, sustainLevel, releaseTime;
    double attackDelta, decayDelta, releaseDelta;
    int state;
    double sampleRate;
    bool init = false;
};

/* A simple lfo with adjustable rate and depth */
class SynthLfo : public ReferenceCountedObject {
public:
    SynthLfo()
    : angle (0.0),
    angleDelta (0.0),
    depth (0.0),
    sampleRate (0),
    output (0.0)
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
private:
    double angle, angleDelta, depth, sampleRate, output;
    bool init;
};

/* A simple demo synth voice that just plays a little more than a sine wave.. */
class OscillatorVoice  : public SynthesiserVoice
{
public:
    OscillatorVoice()
    : angleDelta (0.0)
    {
        if (!env) {
            env = new SynthEnvelope();
            env1 = new SynthEnvelope();
            env->setSampleRate(getSampleRate());
            env1->setSampleRate(getSampleRate());
            
            // Init last (Requires sample rate and env times to be set).
            env->initEnvelope();
            env1->initEnvelope();
            
            lfo = new SynthLfo();
            lfo->setSampleRate(getSampleRate());
        }
    }
    
    SynthEnvelope *env = nullptr;
    SynthEnvelope *env1 = nullptr;
    SynthLfo *lfo = nullptr;
    
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast <SineWaveSound*> (sound) != 0;
    }
    
    void modifyLfo(double lfoPerSecond, double *lfoDelta) {
        double lfoPerSample = lfoPerSecond / getSampleRate();
        *lfoDelta = lfoPerSample * 2.0 * double_Pi;
    }
    
    
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound* /*sound*/, int /*currentPitchWheelPosition*/)
    {
        currentAngle = currentAngle1 = currentAngle2;
        level = .7;
        midiNumber = midiNoteNumber;
        
        lfo->setAngle(0);
        
        // env is output envelope
        env->setOutput(0);
        env->setState(0);
        env->setReleaseTime(.2);
        
        // env1 fires release over and over for a "diving" effect
        env1->setReleaseTime(2);
        env1->setOutput(1);
        env1->release();
        
        // Pure sine-wave bass note (midi# between 36 and 48) matches fundamental
        double cyclesPerSecond = MidiMessage::getMidiNoteInHertz(36 + midiNoteNumber % 24);
        double cyclesPerSample = cyclesPerSecond / getSampleRate();
        angleDelta = cyclesPerSample * 2.0 * double_Pi;
        
        // Fundamental note
        double cyclesPerSecond1 = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        double cyclesPerSample1 = cyclesPerSecond1 / getSampleRate();
        angleDelta1 = cyclesPerSample1 * 2.0 * double_Pi;
        
        // Saw wave
        double cyclesPerSecond2 = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        angleDelta2 = cyclesPerSecond2 / getSampleRate();
        
        // LFO
        baseLfoFreq = 8;
        lfo->setFrequency(baseLfoFreq);
        lfo->setDepth(1);
        
        std::cout << "MidiNote: " << midiNoteNumber << std::endl;
    }
    
    void stopNote (bool allowTailOff) {
        if (!allowTailOff) {
            env->setOutput(0);
        }
        
        env->release();
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
                // Sum 3 oscillator outputs
                const float currentSample =
                (float) (sin (currentAngle)  +
                         sin (currentAngle1) * env1->getOutput() +
                         sin (currentAngle2) * (1 - env1->getOutput()))
                 * env->getOutput();
                
                // Mono output
                for (int i = outputBuffer.getNumChannels(); --i >= 0;)
                    *outputBuffer.getSampleData(i, startSample) += currentSample;
                
                // Increment oscillators
                lfo->stepLfo();
                
                stepOscillator(nullptr, (1 + lfo->getOutput()) * .005 * env1->getOutput());
                
                currentAngle1 += angleDelta1 * env1->getOutput();
                
                currentAngle2 += angleDelta2 * env1->getOutput() / 2;
                
                if (currentAngle2 >= level / 4) {
                    currentAngle2 = level / 4 * -1;
                }
                
                // Push the envelope
                env->stepEnvelope();
                env1->stepEnvelope();
                
                // And mess with the lfo
                lfo->setFrequency((1 - env1->getOutput()) * baseLfoFreq);
                ++startSample;
            }
            
        }
        
        // Note is done playing when output is 0 and envelope is in release
        if (env->getState() == env->ENV_RELEASE && env->getOutput() <= 0) {
            clearCurrentNote();
            angleDelta = 0.0;
        }
    }
    
    void changeMode(int newMode) {
        if (newMode == SINE) {
            mode = SINE;
            angleDelta = oscillatorFreq / getSampleRate() * 2.0 * double_Pi;
        } else if (newMode == SAW) {
            mode = SAW;
            angleDelta = oscillatorFreq / getSampleRate();
        } else {
            // Do nothing if mode not supported
        }
    }
    
    void setCurrentAngle(double newAngle) {
        currentAngle = newAngle;
    }
    
    void stepOscillator(SynthEnvelope *se=nullptr, double offset=0) {
        // Don't mess with base angleDelta
        double tmpDelta = angleDelta;
        
        if (se != nullptr) {
            // Multiplying env output creates a linear pitch shift based on env shape
            // Max frequency is angleDelta * max env level
            tmpDelta *= se->getOutput();
        }
        
        currentAngle += tmpDelta + offset;
        
        // Reset saw if in saw mode
        if (mode == SAW && currentAngle >= level) {
            currentAngle = level * -1;
        }
        
        // Reset if no delta
        if (tmpDelta == 0) {
            // We're not oscillating, so remove DC offset
            currentAngle = 0;
        }
    }
    
    double getOutput() {
        return mode == SINE ? sin(currentAngle) : currentAngle;
    }
    
private:
    enum {
        SINE, SAW
    };
    
    double currentAngle, angleDelta, level;
    double currentAngle1, angleDelta1;
    double currentAngle2, angleDelta2;
    double baseLfoFreq;
    double oscillatorFreq;
    int midiNumber;
    int mode = SINE;
};

const float defaultGain = 1.0f;
const float defaultDelay = 0.5f;

//==============================================================================
Csc344finalAudioProcessor::Csc344finalAudioProcessor()
{
    // Initialise the synth...
    for (int i = 4; --i >= 0;)
        synth.addVoice (new OscillatorVoice());   // These voices will play our custom sine-wave sounds..
    
    synth.addSound (new SineWaveSound());
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
    return 0;
}

float Csc344finalAudioProcessor::getParameter (int index)
{
    return 0.0f;
}

void Csc344finalAudioProcessor::setParameter (int index, float newValue)
{
}

const String Csc344finalAudioProcessor::getParameterName (int index)
{
    return String::empty;
}

const String Csc344finalAudioProcessor::getParameterText (int index)
{
    return String::empty;
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
    synth.setCurrentPlaybackSampleRate (sampleRate);
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
    synth.renderNextBlock (buffer, midiMessages, 0, numSamples);
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
