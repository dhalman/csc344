/*
 ==============================================================================
 
 This file was auto-generated by the Jucer!
 
 It contains the basic startup code for a Juce application.
 
 ==============================================================================
 */

#ifndef __PLUGINEDITOR_H_4ACCBAA__
#define __PLUGINEDITOR_H_4ACCBAA__

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/** This is the editor component that our filter will display.
 */
class A3AudioProcessorEditor  : public AudioProcessorEditor,
public SliderListener,
public Timer
{
public:
    A3AudioProcessorEditor (A3AudioProcessor* ownerFilter);
    ~A3AudioProcessorEditor();
    
    //==============================================================================
    void timerCallback() override;
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged (Slider*) override;
    
private:
    MidiKeyboardComponent midiKeyboard;
    Label infoLabel, gainLabel, frequencyLabel, resonanceLabel;
    Slider gainSlider, frequencySlider, resonanceSlider;
    ScopedPointer<ResizableCornerComponent> resizer;
    ComponentBoundsConstrainer resizeLimits;
    
    AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;
    
    A3AudioProcessor* getProcessor() const
    {
        return static_cast <A3AudioProcessor*> (getAudioProcessor());
    }
    
    void displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos);
};


#endif  // __PLUGINEDITOR_H_4ACCBAA__
