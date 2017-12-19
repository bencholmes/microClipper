/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "clipperCircuit.hpp"
#include "lowShelf.hpp"


//==============================================================================
/**
*/
class MicroClipperAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MicroClipperAudioProcessor();
    ~MicroClipperAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void setDistortion(double newDistortion);
    void setWarmth(double newWarmth);
    void setBrightness(double newBrightness);
    void setPregain(double newGainFactor);
    double getPregain();
    
    double brightness = 0.5;
    double distortion = 0.4;
    double warmth = 0.5;
    

private:
    
    clipperCircuit<double> *clipper = NULL;
    lowShelf<double> *postFilter = NULL;
    
    const double filterCutoff = 500;
    double preGain = 1.1;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MicroClipperAudioProcessor)
};
