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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"
#include "PluginProcessor.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
Csc344finalAudioProcessorEditor::Csc344finalAudioProcessorEditor (Csc344finalAudioProcessor* ownerFilter)
: AudioProcessorEditor (ownerFilter)
{
    proc = ownerFilter;
    
    addAndMakeVisible (freq1 = new Slider ("Frequency1"));
    freq1->setTooltip (TRANS("Frequency1"));
    freq1->setRange (20, 20000, 1);
    freq1->setSliderStyle (Slider::Rotary);
    freq1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    freq1->addListener (this);
    freq1->setSkewFactor (.5);
    
    addAndMakeVisible (amp1 = new Slider ("Amplitude1"));
    amp1->setRange (0, 1, 0.01);
    amp1->setSliderStyle (Slider::Rotary);
    amp1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    amp1->addListener (this);
    
    addAndMakeVisible (freqmod1 = new ComboBox ("FreqMod1"));
    freqmod1->setEditableText (false);
    freqmod1->setJustificationType (Justification::centredLeft);
    freqmod1->setTextWhenNothingSelected (TRANS("Select Modifier:"));
    freqmod1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    freqmod1->addItem (TRANS("LFO1"), 1);
    freqmod1->addItem (TRANS("LFO2"), 2);
    freqmod1->addItem (TRANS("Envelope1"), 3);
    freqmod1->addItem (TRANS("Envelope2"), 4);
    freqmod1->addListener (this);
    
    addAndMakeVisible (ampmod1 = new ComboBox ("AmpMod1"));
    ampmod1->setEditableText (false);
    ampmod1->setJustificationType (Justification::centredLeft);
    ampmod1->setTextWhenNothingSelected (TRANS("Select Modifier:"));
    ampmod1->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    ampmod1->addItem (TRANS("LFO1"), 1);
    ampmod1->addItem (TRANS("LFO2"), 2);
    ampmod1->addItem (TRANS("Envelope1"), 3);
    ampmod1->addItem (TRANS("Envelope2"), 4);
    ampmod1->addListener (this);
    
    addAndMakeVisible (freq2 = new Slider ("Frequency1"));
    freq2->setTooltip (TRANS("Frequency1"));
    freq2->setRange (20, 20000, 1);
    freq2->setSliderStyle (Slider::Rotary);
    freq2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    freq2->addListener (this);
    freq2->setSkewFactor (.5);
    
    addAndMakeVisible (amp2 = new Slider ("Amplitude1"));
    amp2->setRange (0, 1, 0.01);
    amp2->setSliderStyle (Slider::Rotary);
    amp2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    amp2->addListener (this);
    
    addAndMakeVisible (freqmod2 = new ComboBox ("FreqMod2"));
    freqmod2->setEditableText (false);
    freqmod2->setJustificationType (Justification::centredLeft);
    freqmod2->setTextWhenNothingSelected (TRANS("Select Modifier:"));
    freqmod2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    freqmod2->addItem (TRANS("LFO1"), 1);
    freqmod2->addItem (TRANS("LFO2"), 2);
    freqmod2->addItem (TRANS("Envelope1"), 3);
    freqmod2->addItem (TRANS("Envelope2"), 4);
    freqmod2->addListener (this);
    
    addAndMakeVisible (ampmod2 = new ComboBox ("AmpMod2"));
    ampmod2->setEditableText (false);
    ampmod2->setJustificationType (Justification::centredLeft);
    ampmod2->setTextWhenNothingSelected (TRANS("Select Modifier:"));
    ampmod2->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    ampmod2->addItem (TRANS("LFO1"), 1);
    ampmod2->addItem (TRANS("LFO2"), 2);
    ampmod2->addItem (TRANS("Envelope1"), 3);
    ampmod2->addItem (TRANS("Envelope2"), 4);
    ampmod2->addListener (this);
    
    addAndMakeVisible (lfofreq1 = new Slider ("LFOFreq1"));
    lfofreq1->setTooltip (TRANS("Frequency1"));
    lfofreq1->setRange (0.1, 10, 0.1);
    lfofreq1->setSliderStyle (Slider::Rotary);
    lfofreq1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    lfofreq1->addListener (this);
    lfofreq1->setSkewFactor (.5);
    
    addAndMakeVisible (lfoamp1 = new Slider ("LFOAmp1"));
    lfoamp1->setRange (0, 1, 0.01);
    lfoamp1->setSliderStyle (Slider::Rotary);
    lfoamp1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    lfoamp1->addListener (this);
    
    addAndMakeVisible (lfofreq2 = new Slider ("LFOFreq1"));
    lfofreq2->setTooltip (TRANS("Frequency1"));
    lfofreq2->setRange (0.1, 10, 0.1);
    lfofreq2->setSliderStyle (Slider::Rotary);
    lfofreq2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    lfofreq2->addListener (this);
    lfofreq2->setSkewFactor (.5);
    
    addAndMakeVisible (lfoamp2 = new Slider ("LFOAmp2"));
    lfoamp2->setRange (0, 10, 0.1);
    lfoamp2->setSliderStyle (Slider::Rotary);
    lfoamp2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    lfoamp2->addListener (this);
    
    addAndMakeVisible (attacktime1 = new Slider ("AttackTime1"));
    attacktime1->setTooltip (TRANS("Frequency1"));
    attacktime1->setRange (0, 2, 0.001);
    attacktime1->setSliderStyle (Slider::Rotary);
    attacktime1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    attacktime1->addListener (this);
    
    addAndMakeVisible (attacklevel1 = new Slider ("AttackLevel1"));
    attacklevel1->setRange (0, 1, 0.01);
    attacklevel1->setSliderStyle (Slider::Rotary);
    attacklevel1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    attacklevel1->addListener (this);
    
    addAndMakeVisible (decaytime1 = new Slider ("DecayTime1"));
    decaytime1->setTooltip (TRANS("Frequency1"));
    decaytime1->setRange (0, 2, 0.001);
    decaytime1->setSliderStyle (Slider::Rotary);
    decaytime1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    decaytime1->addListener (this);
    
    addAndMakeVisible (sustainlevel1 = new Slider ("sustainlevel1"));
    sustainlevel1->setRange (0.01, 1, 0.01);
    sustainlevel1->setSliderStyle (Slider::Rotary);
    sustainlevel1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sustainlevel1->addListener (this);
    
    addAndMakeVisible (releasetime1 = new Slider ("ReleaseTime1"));
    releasetime1->setRange (0, 2, 0.001);
    releasetime1->setSliderStyle (Slider::Rotary);
    releasetime1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    releasetime1->addListener (this);
    
    addAndMakeVisible (attacktime2 = new Slider ("AttackTime2"));
    attacktime2->setTooltip (TRANS("Frequency1"));
    attacktime2->setRange (0, 2, 0.001);
    attacktime2->setSliderStyle (Slider::Rotary);
    attacktime2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    attacktime2->addListener (this);
    
    addAndMakeVisible (attacklevel2 = new Slider ("AttackLevel2"));
    attacklevel2->setRange (0, 1, 0.01);
    attacklevel2->setSliderStyle (Slider::Rotary);
    attacklevel2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    attacklevel2->addListener (this);
    
    addAndMakeVisible (decaytime2 = new Slider ("DecayTime2"));
    decaytime2->setTooltip (TRANS("Frequency1"));
    decaytime2->setRange (0, 2, 0.001);
    decaytime2->setSliderStyle (Slider::Rotary);
    decaytime2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    decaytime2->addListener (this);
    
    addAndMakeVisible (sustainlevel2 = new Slider ("sustainlevel2"));
    sustainlevel2->setRange (0.1, 1, 0.01);
    sustainlevel2->setSliderStyle (Slider::Rotary);
    sustainlevel2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    sustainlevel2->addListener (this);
    
    addAndMakeVisible (releasetime2 = new Slider ("ReleaseTime2"));
    releasetime2->setRange (0, 2, 0.001);
    releasetime2->setSliderStyle (Slider::Rotary);
    releasetime2->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    releasetime2->addListener (this);
    
    addAndMakeVisible (filteramp1 = new Slider ("FilterAmp1"));
    filteramp1->setRange (0, 1, 0.01);
    filteramp1->setSliderStyle (Slider::Rotary);
    filteramp1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    filteramp1->addListener (this);
    
    addAndMakeVisible (filterfreq1 = new Slider ("FilterFreq1"));
    filterfreq1->setTooltip (TRANS("Frequency1"));
    filterfreq1->setRange (20, 20000, 1);
    filterfreq1->setSliderStyle (Slider::Rotary);
    filterfreq1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    filterfreq1->addListener (this);
    filterfreq1->setSkewFactor (.5);
    
    addAndMakeVisible (filterreso1 = new Slider ("FilterReso1"));
    filterreso1->setRange (.2, .8, 0.01);
    filterreso1->setSliderStyle (Slider::Rotary);
    filterreso1->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    filterreso1->addListener (this);
    
    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("Oscillator 1")));
    label->setFont (Font (15.00f, Font::plain));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("LFO 1")));
    label2->setFont (Font (15.00f, Font::plain));
    label2->setJustificationType (Justification::centredLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label3 = new Label ("new label",
                                           TRANS("Oscillator 2")));
    label3->setFont (Font (15.00f, Font::plain));
    label3->setJustificationType (Justification::centredLeft);
    label3->setEditable (false, false, false);
    label3->setColour (TextEditor::textColourId, Colours::black);
    label3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label4 = new Label ("new label",
                                           TRANS("Oscillator 1 Control")));
    label4->setFont (Font (15.00f, Font::plain));
    label4->setJustificationType (Justification::centredLeft);
    label4->setEditable (false, false, false);
    label4->setColour (TextEditor::textColourId, Colours::black);
    label4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label5 = new Label ("new label",
                                           TRANS("Oscillator 2 Control")));
    label5->setFont (Font (15.00f, Font::plain));
    label5->setJustificationType (Justification::centredLeft);
    label5->setEditable (false, false, false);
    label5->setColour (TextEditor::textColourId, Colours::black);
    label5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label6 = new Label ("new label",
                                           TRANS("LFO 2")));
    label6->setFont (Font (15.00f, Font::plain));
    label6->setJustificationType (Justification::centredLeft);
    label6->setEditable (false, false, false);
    label6->setColour (TextEditor::textColourId, Colours::black);
    label6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label7 = new Label ("new label",
                                           TRANS("Low Pass Filter")));
    label7->setFont (Font (15.00f, Font::plain));
    label7->setJustificationType (Justification::centredLeft);
    label7->setEditable (false, false, false);
    label7->setColour (TextEditor::textColourId, Colours::black);
    label7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label8 = new Label ("new label",
                                           TRANS("Evnelope 1")));
    label8->setFont (Font (15.00f, Font::plain));
    label8->setJustificationType (Justification::centredLeft);
    label8->setEditable (false, false, false);
    label8->setColour (TextEditor::textColourId, Colours::black);
    label8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label9 = new Label ("new label",
                                           TRANS("Evnelope 2")));
    label9->setFont (Font (15.00f, Font::plain));
    label9->setJustificationType (Justification::centredLeft);
    label9->setEditable (false, false, false);
    label9->setColour (TextEditor::textColourId, Colours::black);
    label9->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label10 = new Label ("new label",
                                            TRANS("Freq")));
    label10->setFont (Font (15.00f, Font::plain));
    label10->setJustificationType (Justification::centredLeft);
    label10->setEditable (false, false, false);
    label10->setColour (TextEditor::textColourId, Colours::black);
    label10->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label11 = new Label ("new label",
                                            TRANS("Amp")));
    label11->setFont (Font (15.00f, Font::plain));
    label11->setJustificationType (Justification::centredLeft);
    label11->setEditable (false, false, false);
    label11->setColour (TextEditor::textColourId, Colours::black);
    label11->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label12 = new Label ("new label",
                                            TRANS("Freq")));
    label12->setFont (Font (15.00f, Font::plain));
    label12->setJustificationType (Justification::centredLeft);
    label12->setEditable (false, false, false);
    label12->setColour (TextEditor::textColourId, Colours::black);
    label12->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label13 = new Label ("new label",
                                            TRANS("Amp")));
    label13->setFont (Font (15.00f, Font::plain));
    label13->setJustificationType (Justification::centredLeft);
    label13->setEditable (false, false, false);
    label13->setColour (TextEditor::textColourId, Colours::black);
    label13->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label14 = new Label ("new label",
                                            TRANS("Freq")));
    label14->setFont (Font (15.00f, Font::plain));
    label14->setJustificationType (Justification::centredLeft);
    label14->setEditable (false, false, false);
    label14->setColour (TextEditor::textColourId, Colours::black);
    label14->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label15 = new Label ("new label",
                                            TRANS("Gain")));
    label15->setFont (Font (15.00f, Font::plain));
    label15->setJustificationType (Justification::centredLeft);
    label15->setEditable (false, false, false);
    label15->setColour (TextEditor::textColourId, Colours::black);
    label15->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label16 = new Label ("new label",
                                            TRANS("Resonance")));
    label16->setFont (Font (15.00f, Font::plain));
    label16->setJustificationType (Justification::centredLeft);
    label16->setEditable (false, false, false);
    label16->setColour (TextEditor::textColourId, Colours::black);
    label16->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label17 = new Label ("new label",
                                            TRANS("Freq")));
    label17->setFont (Font (15.00f, Font::plain));
    label17->setJustificationType (Justification::centredLeft);
    label17->setEditable (false, false, false);
    label17->setColour (TextEditor::textColourId, Colours::black);
    label17->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label18 = new Label ("new label",
                                            TRANS("Amp")));
    label18->setFont (Font (15.00f, Font::plain));
    label18->setJustificationType (Justification::centredLeft);
    label18->setEditable (false, false, false);
    label18->setColour (TextEditor::textColourId, Colours::black);
    label18->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label19 = new Label ("new label",
                                            TRANS("Freq")));
    label19->setFont (Font (15.00f, Font::plain));
    label19->setJustificationType (Justification::centredLeft);
    label19->setEditable (false, false, false);
    label19->setColour (TextEditor::textColourId, Colours::black);
    label19->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label20 = new Label ("new label",
                                            TRANS("Amp")));
    label20->setFont (Font (15.00f, Font::plain));
    label20->setJustificationType (Justification::centredLeft);
    label20->setEditable (false, false, false);
    label20->setColour (TextEditor::textColourId, Colours::black);
    label20->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label21 = new Label ("new label",
                                            TRANS("Freq")));
    label21->setFont (Font (15.00f, Font::plain));
    label21->setJustificationType (Justification::centredLeft);
    label21->setEditable (false, false, false);
    label21->setColour (TextEditor::textColourId, Colours::black);
    label21->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label22 = new Label ("new label",
                                            TRANS("Amp")));
    label22->setFont (Font (15.00f, Font::plain));
    label22->setJustificationType (Justification::centredLeft);
    label22->setEditable (false, false, false);
    label22->setColour (TextEditor::textColourId, Colours::black);
    label22->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label23 = new Label ("new label",
                                            TRANS("Freq")));
    label23->setFont (Font (15.00f, Font::plain));
    label23->setJustificationType (Justification::centredLeft);
    label23->setEditable (false, false, false);
    label23->setColour (TextEditor::textColourId, Colours::black);
    label23->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label24 = new Label ("new label",
                                            TRANS("Amp")));
    label24->setFont (Font (15.00f, Font::plain));
    label24->setJustificationType (Justification::centredLeft);
    label24->setEditable (false, false, false);
    label24->setColour (TextEditor::textColourId, Colours::black);
    label24->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label25 = new Label ("new label",
                                            TRANS("Attack Time")));
    label25->setFont (Font (15.00f, Font::plain));
    label25->setJustificationType (Justification::centredLeft);
    label25->setEditable (false, false, false);
    label25->setColour (TextEditor::textColourId, Colours::black);
    label25->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label26 = new Label ("new label",
                                            TRANS("Attack Level")));
    label26->setFont (Font (15.00f, Font::plain));
    label26->setJustificationType (Justification::centredLeft);
    label26->setEditable (false, false, false);
    label26->setColour (TextEditor::textColourId, Colours::black);
    label26->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label27 = new Label ("new label",
                                            TRANS("Decay Time")));
    label27->setFont (Font (15.00f, Font::plain));
    label27->setJustificationType (Justification::centredLeft);
    label27->setEditable (false, false, false);
    label27->setColour (TextEditor::textColourId, Colours::black);
    label27->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label28 = new Label ("new label",
                                            TRANS("Sustain Level")));
    label28->setFont (Font (15.00f, Font::plain));
    label28->setJustificationType (Justification::centredLeft);
    label28->setEditable (false, false, false);
    label28->setColour (TextEditor::textColourId, Colours::black);
    label28->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    
    addAndMakeVisible (label29 = new Label ("new label",
                                            TRANS("Release Time")));
    label29->setFont (Font (15.00f, Font::plain));
    label29->setJustificationType (Justification::centredLeft);
    label29->setEditable (false, false, false);
    label29->setColour (TextEditor::textColourId, Colours::black);
    label29->setColour (TextEditor::backgroundColourId, Colour (0x00000000));
    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

Csc344finalAudioProcessorEditor::~Csc344finalAudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    freq1 = nullptr;
    amp1 = nullptr;
    freqmod1 = nullptr;
    ampmod1 = nullptr;
    freq2 = nullptr;
    amp2 = nullptr;
    freqmod2 = nullptr;
    ampmod2 = nullptr;
    lfofreq1 = nullptr;
    lfoamp1 = nullptr;
    lfofreq2 = nullptr;
    lfoamp2 = nullptr;
    attacktime1 = nullptr;
    attacklevel1 = nullptr;
    decaytime1 = nullptr;
    sustainlevel1 = nullptr;
    releasetime1 = nullptr;
    attacktime2 = nullptr;
    attacklevel2 = nullptr;
    decaytime2 = nullptr;
    sustainlevel2 = nullptr;
    releasetime2 = nullptr;
    filteramp1 = nullptr;
    filterfreq1 = nullptr;
    filterreso1 = nullptr;
    label = nullptr;
    label2 = nullptr;
    label3 = nullptr;
    label4 = nullptr;
    label5 = nullptr;
    label6 = nullptr;
    label7 = nullptr;
    label8 = nullptr;
    label9 = nullptr;
    label10 = nullptr;
    label11 = nullptr;
    label12 = nullptr;
    label13 = nullptr;
    label14 = nullptr;
    label15 = nullptr;
    label16 = nullptr;
    label17 = nullptr;
    label18 = nullptr;
    label19 = nullptr;
    label20 = nullptr;
    label21 = nullptr;
    label22 = nullptr;
    label23 = nullptr;
    label24 = nullptr;
    label25 = nullptr;
    label26 = nullptr;
    label27 = nullptr;
    label28 = nullptr;
    label29 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void Csc344finalAudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void Csc344finalAudioProcessorEditor::resized()
{
    freq1->setBounds (48, 40, 150, 24);
    amp1->setBounds (48, 72, 150, 24);
    freqmod1->setBounds (224, 40, 150, 24);
    ampmod1->setBounds (224, 72, 150, 24);
    freq2->setBounds (48, 136, 150, 24);
    amp2->setBounds (48, 168, 150, 24);
    freqmod2->setBounds (224, 136, 150, 24);
    ampmod2->setBounds (224, 168, 150, 24);
    lfofreq1->setBounds (432, 40, 150, 24);
    lfoamp1->setBounds (432, 72, 150, 24);
    lfofreq2->setBounds (432, 136, 150, 24);
    lfoamp2->setBounds (432, 168, 150, 24);
    attacktime1->setBounds (152, 304, 150, 24);
    attacklevel1->setBounds (152, 336, 150, 24);
    decaytime1->setBounds (152, 368, 150, 24);
    sustainlevel1->setBounds (152, 400, 150, 24);
    releasetime1->setBounds (152, 432, 150, 24);
    attacktime2->setBounds (304, 304, 150, 24);
    attacklevel2->setBounds (304, 336, 150, 24);
    decaytime2->setBounds (304, 368, 150, 24);
    sustainlevel2->setBounds (304, 400, 150, 24);
    releasetime2->setBounds (304, 432, 150, 24);
    filteramp1->setBounds (224, 232, 150, 24);
    filterfreq1->setBounds (48, 232, 150, 24);
    filterreso1->setBounds (432, 232, 150, 24);
    label->setBounds (48, 16, 150, 24);
    label2->setBounds (432, 16, 150, 24);
    label3->setBounds (48, 112, 150, 24);
    label4->setBounds (224, 16, 150, 24);
    label5->setBounds (224, 112, 150, 24);
    label6->setBounds (432, 112, 150, 24);
    label7->setBounds (48, 208, 150, 24);
    label8->setBounds (152, 280, 150, 24);
    label9->setBounds (304, 280, 150, 24);
    label10->setBounds (8, 40, 150, 24);
    label11->setBounds (8, 72, 150, 24);
    label12->setBounds (8, 136, 150, 24);
    label13->setBounds (8, 168, 150, 24);
    label14->setBounds (8, 232, 150, 24);
    label15->setBounds (184, 232, 150, 24);
    label16->setBounds (360, 232, 150, 24);
    label17->setBounds (184, 40, 150, 24);
    label18->setBounds (184, 72, 150, 24);
    label19->setBounds (184, 136, 150, 24);
    label20->setBounds (184, 168, 150, 24);
    label21->setBounds (392, 40, 150, 24);
    label22->setBounds (392, 72, 150, 24);
    label23->setBounds (392, 136, 150, 24);
    label24->setBounds (392, 168, 150, 24);
    label25->setBounds (56, 304, 150, 24);
    label26->setBounds (56, 336, 150, 24);
    label27->setBounds (56, 368, 150, 24);
    label28->setBounds (56, 400, 150, 24);
    label29->setBounds (56, 432, 150, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void Csc344finalAudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]
    double newVal = sliderThatWasMoved->getValue();

    if (sliderThatWasMoved == freq1)
    {
        //[UserSliderCode_freq1] -- add your slider handling code here..
        //[/UserSliderCode_freq1]
        //getProcessor()->setSinFreq(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->sinFreq, newVal);
    }
    else if (sliderThatWasMoved == amp1)
    {
        //getProcessor()->setSinAmp(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->sinAmp, newVal);

        //[UserSliderCode_amp1] -- add your slider handling code here..
        //[/UserSliderCode_amp1]
    }
    else if (sliderThatWasMoved == freq2)
    {
        //getProcessor()->setSawFreq(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->sawFreq, newVal);

        //[UserSliderCode_freq2] -- add your slider handling code here..
        //[/UserSliderCode_freq2]
    }
    else if (sliderThatWasMoved == amp2)
    {
        //getProcessor()->setSawAmp(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->sawAmp, newVal);

        //[UserSliderCode_amp2] -- add your slider handling code here..
        //[/UserSliderCode_amp2]
    }
    else if (sliderThatWasMoved == lfofreq1)
    {
        //getProcessor()->setLfo1Freq(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->lfo1Freq, newVal);

        //[UserSliderCode_lfofreq1] -- add your slider handling code here..
        //[/UserSliderCode_lfofreq1]
    }
    else if (sliderThatWasMoved == lfoamp1)
    {
        //getProcessor()->setLfo1Amp(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->lfo1Amp, newVal);
        
        //[UserSliderCode_lfoamp1] -- add your slider handling code here..
        //[/UserSliderCode_lfoamp1]
    }
    else if (sliderThatWasMoved == lfofreq2)
    {
        //getProcessor()->setLfo2Freq(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->lfo2Freq, newVal);

        //[UserSliderCode_lfofreq2] -- add your slider handling code here..
        //[/UserSliderCode_lfofreq2]
    }
    else if (sliderThatWasMoved == lfoamp2)
    {
        //getProcessor()->setLfo2Amp(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->lfo2Amp, newVal);

        //[UserSliderCode_lfoamp2] -- add your slider handling code here..
        //[/UserSliderCode_lfoamp2]
    }
    else if (sliderThatWasMoved == attacktime1)
    {
        //getProcessor()->setEnv1AttackTime(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->env1AT, newVal);

        //[UserSliderCode_attacktime1] -- add your slider handling code here..
        //[/UserSliderCode_attacktime1]
    }
    else if (sliderThatWasMoved == attacklevel1)
    {
        //getProcessor()->setEnv1AttackLevel(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->env1AL, newVal);

        //[UserSliderCode_attacklevel1] -- add your slider handling code here..
        //[/UserSliderCode_attacklevel1]
    }
    else if (sliderThatWasMoved == decaytime1)
    {
        //getProcessor()->setEnv1DecayTime(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->env1DT, newVal);

        //[UserSliderCode_decaytime1] -- add your slider handling code here..
        //[/UserSliderCode_decaytime1]
    }
    else if (sliderThatWasMoved == sustainlevel1)
    {
        //getProcessor()->setEnv1SustainLevel(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->env1SL, newVal);

        //[UserSliderCode_sustainlevel1] -- add your slider handling code here..
        //[/UserSliderCode_sustainlevel1]
    }
    else if (sliderThatWasMoved == releasetime1)
    {
        // getProcessor()->setEnv1ReleaseTime(newVal);
        
        getProcessor()->setParameterNotifyingHost(getProcessor()->env1RT, newVal);

        //[UserSliderCode_releasetime1] -- add your slider handling code here..
        //[/UserSliderCode_releasetime1]
    }
    else if (sliderThatWasMoved == attacktime2)
    {
        //getProcessor()->setEnv2AttackTime(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->env2AT, newVal);

        //[UserSliderCode_attacktime2] -- add your slider handling code here..
        //[/UserSliderCode_attacktime2]
    }
    else if (sliderThatWasMoved == attacklevel2)
    {
        //   getProcessor()->setEnv2AttackLevel(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->env2AL, newVal);

        //[UserSliderCode_attacklevel2] -- add your slider handling code here..
        //[/UserSliderCode_attacklevel2]
    }
    else if (sliderThatWasMoved == decaytime2)
    {
        //getProcessor()->setEnv2DecayTime(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->env2DT, newVal);

        //[UserSliderCode_decaytime2] -- add your slider handling code here..
        //[/UserSliderCode_decaytime2]
    }
    else if (sliderThatWasMoved == sustainlevel2)
    {
        //getProcessor()->setEnv2SustainLevel(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->env2SL, newVal);

        //[UserSliderCode_sustainlevel2] -- add your slider handling code here..
        //[/UserSliderCode_sustainlevel2]
    }
    else if (sliderThatWasMoved == releasetime2)
    {
        //getProcessor()->setEnv2ReleaseTime(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->env2RT, newVal);

        //[UserSliderCode_releasetime2] -- add your slider handling code here..
        //[/UserSliderCode_releasetime2]
    }
    else if (sliderThatWasMoved == filteramp1)
    {
        //getProcessor()->setLowPassAmp(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->filterAmp, newVal);

        //[UserSliderCode_filteramp1] -- add your slider handling code here..
        //[/UserSliderCode_filteramp1]
    }
    else if (sliderThatWasMoved == filterfreq1)
    {
        //getProcessor()->setLowPassFreq(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->filterFreq, newVal);

        //[UserSliderCode_filterfreq1] -- add your slider handling code here..
        //[/UserSliderCode_filterfreq1]
    }
    else if (sliderThatWasMoved == filterreso1)
    {
        getProcessor()->setLowPassReso(newVal);
        getProcessor()->setParameterNotifyingHost(getProcessor()->filterReso, newVal);

        //[UserSliderCode_filterreso1] -- add your slider handling code here..
        //[/UserSliderCode_filterreso1]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void Csc344finalAudioProcessorEditor::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == freqmod1)
    {
        //[UserComboBoxCode_freqmod1] -- add your combo box handling code here..
        //[/UserComboBoxCode_freqmod1]
    }
    else if (comboBoxThatHasChanged == ampmod1)
    {
        //[UserComboBoxCode_ampmod1] -- add your combo box handling code here..
        //[/UserComboBoxCode_ampmod1]
    }
    else if (comboBoxThatHasChanged == freqmod2)
    {
        //[UserComboBoxCode_freqmod2] -- add your combo box handling code here..
        //[/UserComboBoxCode_freqmod2]
    }
    else if (comboBoxThatHasChanged == ampmod2)
    {
        //[UserComboBoxCode_ampmod2] -- add your combo box handling code here..
        //[/UserComboBoxCode_ampmod2]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

Csc344finalAudioProcessor *Csc344finalAudioProcessorEditor::getProcessor() {
    return proc;
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="AudioProcessorEditor" className="Csc344finalAudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <SLIDER name="Frequency1" id="b06be8b94012495" memberName="freq1" virtualName=""
          explicitFocusOrder="0" pos="48 40 150 24" tooltip="Frequency1"
          min="20" max="20000" int="1" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.5"/>
  <SLIDER name="Amplitude1" id="6275ab15d7adca7" memberName="amp1" virtualName=""
          explicitFocusOrder="0" pos="48 72 150 24" min="0" max="1" int="0.010000000000000000208"
          style="Rotary" textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="FreqMod1" id="47fe0208458b0304" memberName="freqmod1" virtualName=""
            explicitFocusOrder="0" pos="224 40 150 24" editable="0" layout="33"
            items="LFO1&#10;LFO2&#10;Envelope1&#10;Envelope2" textWhenNonSelected="Select Modifier:"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="AmpMod1" id="b3e66385d8a2b4f3" memberName="ampmod1" virtualName=""
            explicitFocusOrder="0" pos="224 72 150 24" editable="0" layout="33"
            items="LFO1&#10;LFO2&#10;Envelope1&#10;Envelope2" textWhenNonSelected="Select Modifier:"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="Frequency1" id="84d74d27032bf16e" memberName="freq2" virtualName=""
          explicitFocusOrder="0" pos="48 136 150 24" tooltip="Frequency1"
          min="20" max="20000" int="1" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.5"/>
  <SLIDER name="Amplitude1" id="29dc3d53330811e1" memberName="amp2" virtualName=""
          explicitFocusOrder="0" pos="48 168 150 24" min="0" max="1" int="0.010000000000000000208"
          style="Rotary" textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <COMBOBOX name="FreqMod2" id="cbaabefc4f98ef11" memberName="freqmod2" virtualName=""
            explicitFocusOrder="0" pos="224 136 150 24" editable="0" layout="33"
            items="LFO1&#10;LFO2&#10;Envelope1&#10;Envelope2" textWhenNonSelected="Select Modifier:"
            textWhenNoItems="(no choices)"/>
  <COMBOBOX name="AmpMod2" id="742f77e349674066" memberName="ampmod2" virtualName=""
            explicitFocusOrder="0" pos="224 168 150 24" editable="0" layout="33"
            items="LFO1&#10;LFO2&#10;Envelope1&#10;Envelope2" textWhenNonSelected="Select Modifier:"
            textWhenNoItems="(no choices)"/>
  <SLIDER name="LFOFreq1" id="442ab924fbd24de5" memberName="lfofreq1" virtualName=""
          explicitFocusOrder="0" pos="432 40 150 24" tooltip="Frequency1"
          min="0.10000000000000000555" max="10" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.5"/>
  <SLIDER name="LFOAmp1" id="e0672c2693ab121b" memberName="lfoamp1" virtualName=""
          explicitFocusOrder="0" pos="432 72 150 24" min="0" max="1" int="0.010000000000000000208"
          style="Rotary" textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="LFOFreq1" id="179a1c9cabac5ec" memberName="lfofreq2" virtualName=""
          explicitFocusOrder="0" pos="432 136 150 24" tooltip="Frequency1"
          min="0.10000000000000000555" max="10" int="0.10000000000000000555"
          style="Rotary" textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.5"/>
  <SLIDER name="LFOAmp2" id="1f1d31f64089163c" memberName="lfoamp2" virtualName=""
          explicitFocusOrder="0" pos="432 168 150 24" min="0" max="10"
          int="0.10000000000000000555" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="AttackTime1" id="782d8ea49dc6c072" memberName="attacktime1"
          virtualName="" explicitFocusOrder="0" pos="152 304 150 24" tooltip="Frequency1"
          min="0" max="2" int="0.0010000000000000000208" style="Rotary"
          textBoxPos="TextBoxLeft" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="AttackLevel1" id="6cbcf33b86268628" memberName="attacklevel1"
          virtualName="" explicitFocusOrder="0" pos="152 336 150 24" min="0"
          max="1" int="0.010000000000000000208" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="DecayTime1" id="221b0c882aa78708" memberName="decaytime1"
          virtualName="" explicitFocusOrder="0" pos="152 368 150 24" tooltip="Frequency1"
          min="20" max="20000" int="1" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="sustainlevel1" id="80f5e79576c393f" memberName="sustainlevel1"
          virtualName="" explicitFocusOrder="0" pos="152 400 150 24" min="0.10000000000000000555"
          max="10" int="0.10000000000000000555" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="ReleaseTime1" id="15b71713a52b88be" memberName="releasetime1"
          virtualName="" explicitFocusOrder="0" pos="152 432 150 24" min="0.10000000000000000555"
          max="10" int="0.10000000000000000555" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="AttackTime2" id="f5517b4ed2ee532f" memberName="attacktime2"
          virtualName="" explicitFocusOrder="0" pos="304 304 150 24" tooltip="Frequency1"
          min="20" max="20000" int="1" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="AttackLevel2" id="237f26f84a59d53" memberName="attacklevel2"
          virtualName="" explicitFocusOrder="0" pos="304 336 150 24" min="0"
          max="1" int="0.010000000000000000208" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="DecayTime2" id="b95dffbdb5e2dda1" memberName="decaytime2"
          virtualName="" explicitFocusOrder="0" pos="304 368 150 24" tooltip="Frequency1"
          min="20" max="20000" int="1" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="sustainlevel2" id="b4106e3d12a85241" memberName="sustainlevel2"
          virtualName="" explicitFocusOrder="0" pos="304 400 150 24" min="0.10000000000000000555"
          max="10" int="0.10000000000000000555" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="ReleaseTime2" id="d8b1a2e00d4aeba" memberName="releasetime2"
          virtualName="" explicitFocusOrder="0" pos="304 432 150 24" min="0.10000000000000000555"
          max="10" int="0.10000000000000000555" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="FilterAmp1" id="f7b4c0b2401c2434" memberName="filteramp1"
          virtualName="" explicitFocusOrder="0" pos="224 232 150 24" min="0"
          max="1" int="0.010000000000000000208" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <SLIDER name="FilterFreq1" id="6774c6fbdfe542cb" memberName="filterfreq1"
          virtualName="" explicitFocusOrder="0" pos="48 232 150 24" tooltip="Frequency1"
          min="20" max="20000" int="1" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.5"/>
  <SLIDER name="FilterReso1" id="eba0e48c73a6f2a6" memberName="filterreso1"
          virtualName="" explicitFocusOrder="0" pos="432 232 150 24" min="0"
          max="1" int="0.010000000000000000208" style="Rotary" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1"/>
  <LABEL name="new label" id="c2eb5f7adec92164" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="48 16 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Oscillator 1" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d0cd6505bfc8fef3" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="432 16 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="LFO 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b33c5a1a9be13773" memberName="label3" virtualName=""
         explicitFocusOrder="0" pos="48 112 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Oscillator 2" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="2f0f622b5094bc7e" memberName="label4" virtualName=""
         explicitFocusOrder="0" pos="224 16 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Oscillator 1 Control" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="14dba6556d5c2434" memberName="label5" virtualName=""
         explicitFocusOrder="0" pos="224 112 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Oscillator 2 Control" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="39420eb554059152" memberName="label6" virtualName=""
         explicitFocusOrder="0" pos="432 112 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="LFO 2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c3574a2a32aa19a3" memberName="label7" virtualName=""
         explicitFocusOrder="0" pos="48 208 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Low Pass Filter" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6e1e0e6035ee9fb7" memberName="label8" virtualName=""
         explicitFocusOrder="0" pos="152 280 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Evnelope 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="1c16d40a070c13d2" memberName="label9" virtualName=""
         explicitFocusOrder="0" pos="304 280 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Evnelope 2" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f258936ed0665027" memberName="label10" virtualName=""
         explicitFocusOrder="0" pos="8 40 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="15da45268c380446" memberName="label11" virtualName=""
         explicitFocusOrder="0" pos="8 72 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amp" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c1cd2b246e4d63d1" memberName="label12" virtualName=""
         explicitFocusOrder="0" pos="8 136 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d954b47faba5cf8f" memberName="label13" virtualName=""
         explicitFocusOrder="0" pos="8 168 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amp" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b06c526d515f7046" memberName="label14" virtualName=""
         explicitFocusOrder="0" pos="8 232 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="6774f9d7c8ee2bd5" memberName="label15" virtualName=""
         explicitFocusOrder="0" pos="184 232 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Gain" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="3c3b1499f5817a10" memberName="label16" virtualName=""
         explicitFocusOrder="0" pos="360 232 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Resonance" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a69ee54ed00da301" memberName="label17" virtualName=""
         explicitFocusOrder="0" pos="184 40 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8402e7e2c51968b3" memberName="label18" virtualName=""
         explicitFocusOrder="0" pos="184 72 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amp" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="a465293a16c384fb" memberName="label19" virtualName=""
         explicitFocusOrder="0" pos="184 136 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e345c2a31b60f50a" memberName="label20" virtualName=""
         explicitFocusOrder="0" pos="184 168 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amp" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c1f516c00ab75df5" memberName="label21" virtualName=""
         explicitFocusOrder="0" pos="392 40 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="9f9fac19ff75b1fd" memberName="label22" virtualName=""
         explicitFocusOrder="0" pos="392 72 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amp" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e93fbb7bd3a116ff" memberName="label23" virtualName=""
         explicitFocusOrder="0" pos="392 136 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Freq" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f0344356f5cc914d" memberName="label24" virtualName=""
         explicitFocusOrder="0" pos="392 168 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Amp" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="87511de25a44ef20" memberName="label25" virtualName=""
         explicitFocusOrder="0" pos="56 304 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack Time" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="f93f3d5e3c69c021" memberName="label26" virtualName=""
         explicitFocusOrder="0" pos="56 336 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Attack Level" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c5b9ca5f1180601" memberName="label27" virtualName=""
         explicitFocusOrder="0" pos="56 368 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Decay Time" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="ca47dd766b6a1642" memberName="label28" virtualName=""
         explicitFocusOrder="0" pos="56 400 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Sustain Level" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c8c5ac562c0ffa51" memberName="label29" virtualName=""
         explicitFocusOrder="0" pos="56 432 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Release Time" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
