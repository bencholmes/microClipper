/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>


//==============================================================================
MicroClipperAudioProcessor::MicroClipperAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MicroClipperAudioProcessor::~MicroClipperAudioProcessor()
{
    if(clipper != NULL)
    {
        delete clipper;
    }
    
    if(postFilter != NULL)
    {
        delete postFilter;
    }
}

//==============================================================================
const String MicroClipperAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MicroClipperAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MicroClipperAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MicroClipperAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MicroClipperAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MicroClipperAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MicroClipperAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MicroClipperAudioProcessor::setCurrentProgram (int index)
{
}

const String MicroClipperAudioProcessor::getProgramName (int index)
{
    return {};
}

void MicroClipperAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MicroClipperAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    if(clipper != NULL)
    {
        delete clipper;
    }
    
    clipper = new clipperCircuit<double>(sampleRate);
    
    
    
    if(postFilter !=NULL)
    {
        delete postFilter;
    }
    
    postFilter = new lowShelf<double>(sampleRate);
    postFilter->setCutoff(filterCutoff);
    
    setBrightness(brightness);
    setWarmth(warmth);
    setDistortion(distortion);
    setPregain(getPregain());
}

void MicroClipperAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MicroClipperAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MicroClipperAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    float copyBuffer[buffer.getNumSamples()];
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        
        if(channel==0)
        {
            for(unsigned int nn=0; nn < buffer.getNumSamples(); nn++)
            {
                channelData[nn] = clipper->run(preGain*channelData[nn]);
                channelData[nn] = postFilter->run(channelData[nn]);
                copyBuffer[nn] = channelData[nn];
            }
        }
        else
        {
            for(unsigned int nn=0; nn < buffer.getNumSamples(); nn++)
            {
                channelData[nn] = copyBuffer[nn];
            }
        }
    }
}

//==============================================================================
bool MicroClipperAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MicroClipperAudioProcessor::createEditor()
{
    return new MicroClipperAudioProcessorEditor (*this);
}

//==============================================================================
void MicroClipperAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    MemoryOutputStream (destData, true).writeFloat (brightness);
    MemoryOutputStream (destData, true).writeFloat (distortion);
    MemoryOutputStream (destData, true).writeFloat (warmth);
    MemoryOutputStream (destData, true).writeFloat (getPregain());
}

void MicroClipperAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    brightness = MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    distortion = MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    warmth = MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    setPregain(MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat());
    
    
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MicroClipperAudioProcessor();
}

void MicroClipperAudioProcessor::setDistortion(double newDistortion)
{
    distortion = newDistortion;
    clipper->setIdeality(2 - (-1.2250*std::pow(0.1837,distortion) + 1.2250));
}

void MicroClipperAudioProcessor::setWarmth(double newWarmth)
{
    warmth = newWarmth;
    clipper->setAsymmetry(1 + (2*(1-warmth)));
}

void MicroClipperAudioProcessor::setBrightness(double newBrightness)
{
    brightness = newBrightness;
    postFilter->setGain(-brightness*15);
}

void MicroClipperAudioProcessor::setPregain(double newGainFactor)
{
    preGain = std::pow(10.,newGainFactor/2);
}

double MicroClipperAudioProcessor::getPregain()
{
    return 2*std::log10(preGain);
}
