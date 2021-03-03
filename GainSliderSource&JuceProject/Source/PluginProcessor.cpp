/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainSliderwithAutomationVst3AudioProcessor::GainSliderwithAutomationVst3AudioProcessor()
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
    state = new AudioProcessorValueTreeState(*this, nullptr);
    NormalisableRange<float> gainRange(0.0f, 1.0f,0.0001f);

    state->createAndAddParameter("gain", "Gain", "Gain", gainRange, 1.0, nullptr, nullptr);

    state->state = ValueTree("gain");
}

GainSliderwithAutomationVst3AudioProcessor::~GainSliderwithAutomationVst3AudioProcessor()
{
}

//==============================================================================
const String GainSliderwithAutomationVst3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool GainSliderwithAutomationVst3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool GainSliderwithAutomationVst3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool GainSliderwithAutomationVst3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double GainSliderwithAutomationVst3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int GainSliderwithAutomationVst3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int GainSliderwithAutomationVst3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void GainSliderwithAutomationVst3AudioProcessor::setCurrentProgram (int index)
{
}

const String GainSliderwithAutomationVst3AudioProcessor::getProgramName (int index)
{
    return {};
}

void GainSliderwithAutomationVst3AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void GainSliderwithAutomationVst3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    lastSampleRate = sampleRate;
    dsp::ProcessSpec spec;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
}

void GainSliderwithAutomationVst3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool GainSliderwithAutomationVst3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void GainSliderwithAutomationVst3AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    //
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //
    //refers to buffer in this block
    dsp::AudioBlock<float> block(buffer);
    float gain = *state->getRawParameterValue("gain");
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        

        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
            *channelData = buffer.getSample(channel, sample) * gain;
            //channelData[sample] = buffer.getSample(channel, sample) * gainValue; // this gives the knob gain
            channelData++;
        }
    }
}
//==============================================================================

AudioProcessorValueTreeState& GainSliderwithAutomationVst3AudioProcessor::getState() {
    return *state;
}
//==============================================================================
bool GainSliderwithAutomationVst3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* GainSliderwithAutomationVst3AudioProcessor::createEditor()
{
    return new GainSliderwithAutomationVst3AudioProcessorEditor (*this);
}

//==============================================================================
void GainSliderwithAutomationVst3AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);
}

void GainSliderwithAutomationVst3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

    if (tree.isValid()) {
        state->state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new GainSliderwithAutomationVst3AudioProcessor();
}
