/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
MicroClipperAudioProcessorEditor::MicroClipperAudioProcessorEditor (MicroClipperAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    distKnob.setSliderStyle (Slider::Rotary);
    distKnob.setRange(0,1,0.01);
    distKnob.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    distKnob.setTextValueSuffix(" Distortion");
    distKnob.setValue(processor.distortion);
    
    brightKnob.setSliderStyle (Slider::Rotary);
    brightKnob.setRange(0.01,0.99,0.01);
    brightKnob.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    brightKnob.setTextValueSuffix(" Brightness");
    brightKnob.setValue(processor.brightness);
    
    warmthKnob.setSliderStyle (Slider::Rotary);
    warmthKnob.setRange(0,1,0.01);
    warmthKnob.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    warmthKnob.setTextValueSuffix(" Warmth");
    warmthKnob.setValue(processor.warmth);
    
    pregainKnob.setSliderStyle (Slider::Rotary);
    pregainKnob.setRange(0,1,0.01);
    pregainKnob.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    pregainKnob.setTextValueSuffix(" Pre-Gain");
    pregainKnob.setValue(processor.getPregain());
    
    addAndMakeVisible (distKnob);
    addAndMakeVisible (brightKnob);
    addAndMakeVisible (warmthKnob);
    addAndMakeVisible (pregainKnob);
    
    distKnob.addListener (this);
    warmthKnob.addListener (this);
    brightKnob.addListener (this);
    pregainKnob.addListener (this);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize ((2*edgeBound) + (4*knobSize), 120);
}

MicroClipperAudioProcessorEditor::~MicroClipperAudioProcessorEditor()
{
}

//==============================================================================
void MicroClipperAudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window white
    g.fillAll (Colours::white);
    
    // set the current drawing colour to black
    g.setColour (Colours::black);
    
    // set the font size and draw text to the screen
    g.setFont (15.0f);
    
    g.drawSingleLineText ("Pre-gain",   edgeBound + (0.5*knobSize),
                          110, Justification::horizontallyCentred);
    g.drawSingleLineText ("Distortion", edgeBound + (1.5*knobSize),
                          20,  Justification::horizontallyCentred);
    g.drawSingleLineText ("Brightness", edgeBound + (2.5*knobSize),
                          110, Justification::horizontallyCentred);
    g.drawSingleLineText ("Warmth",     edgeBound + (3.5*knobSize),
                          20,  Justification::horizontallyCentred);
}

void MicroClipperAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    pregainKnob.setBounds(edgeBound + (0*knobSize), 60, knobSize, knobSize);
    distKnob.setBounds   (edgeBound + (1*knobSize), 30, knobSize, knobSize);
    brightKnob.setBounds (edgeBound + (2*knobSize), 60, knobSize, knobSize);
    warmthKnob.setBounds (edgeBound + (3*knobSize), 30, knobSize, knobSize);
}

void MicroClipperAudioProcessorEditor::sliderValueChanged (Slider* slider)
{
    if (slider == &distKnob)
        processor.setDistortion(distKnob.getValue());
    else if(slider == &warmthKnob)
        processor.setWarmth(warmthKnob.getValue());
    else if(slider == &brightKnob)
        processor.setBrightness(brightKnob.getValue());
    else if(slider == &pregainKnob)
        processor.setPregain(pregainKnob.getValue());
    
}
