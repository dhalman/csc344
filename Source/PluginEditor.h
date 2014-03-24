/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_5E73A194AE4DDC61__
#define __JUCE_HEADER_5E73A194AE4DDC61__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "PluginProcessor.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Introjucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class Csc344finalAudioProcessorEditor  : public AudioProcessorEditor,
                                         public SliderListener,
                                         public ComboBoxListener
{
public:
    //==============================================================================
    Csc344finalAudioProcessorEditor (Csc344finalAudioProcessor* ownerFilter);

    ~Csc344finalAudioProcessorEditor();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void sliderValueChanged (Slider* sliderThatWasMoved);
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    Csc344finalAudioProcessor *getProcessor();


private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Slider> freq1;
    ScopedPointer<Slider> amp1;
    ScopedPointer<ComboBox> freqmod1;
    ScopedPointer<ComboBox> ampmod1;
    ScopedPointer<Slider> freq2;
    ScopedPointer<Slider> amp2;
    ScopedPointer<ComboBox> freqmod2;
    ScopedPointer<ComboBox> ampmod2;
    ScopedPointer<Slider> lfofreq1;
    ScopedPointer<Slider> lfoamp1;
    ScopedPointer<Slider> lfofreq2;
    ScopedPointer<Slider> lfoamp2;
    ScopedPointer<Slider> attacktime1;
    ScopedPointer<Slider> attacklevel1;
    ScopedPointer<Slider> decaytime1;
    ScopedPointer<Slider> sustainlevel1;
    ScopedPointer<Slider> releasetime1;
    ScopedPointer<Slider> attacktime2;
    ScopedPointer<Slider> attacklevel2;
    ScopedPointer<Slider> decaytime2;
    ScopedPointer<Slider> sustainlevel2;
    ScopedPointer<Slider> releasetime2;
    ScopedPointer<Slider> filteramp1;
    ScopedPointer<Slider> filterfreq1;
    ScopedPointer<Slider> filterreso1;
    ScopedPointer<Label> label;
    ScopedPointer<Label> label2;
    ScopedPointer<Label> label3;
    ScopedPointer<Label> label4;
    ScopedPointer<Label> label5;
    ScopedPointer<Label> label6;
    ScopedPointer<Label> label7;
    ScopedPointer<Label> label8;
    ScopedPointer<Label> label9;
    ScopedPointer<Label> label10;
    ScopedPointer<Label> label11;
    ScopedPointer<Label> label12;
    ScopedPointer<Label> label13;
    ScopedPointer<Label> label14;
    ScopedPointer<Label> label15;
    ScopedPointer<Label> label16;
    ScopedPointer<Label> label17;
    ScopedPointer<Label> label18;
    ScopedPointer<Label> label19;
    ScopedPointer<Label> label20;
    ScopedPointer<Label> label21;
    ScopedPointer<Label> label22;
    ScopedPointer<Label> label23;
    ScopedPointer<Label> label24;
    ScopedPointer<Label> label25;
    ScopedPointer<Label> label26;
    ScopedPointer<Label> label27;
    ScopedPointer<Label> label28;
    ScopedPointer<Label> label29;
    
    Csc344finalAudioProcessor *proc;

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Csc344finalAudioProcessorEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_5E73A194AE4DDC61__
