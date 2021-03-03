/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ButterSliceVstAudioProcessor::ButterSliceVstAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr), lowPassFilter(dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f))
#endif
{
    state = new AudioProcessorValueTreeState(*this, nullptr);
    NormalisableRange<float> cutoffRange(20.0f, 20000.0f);
    NormalisableRange<float> resRange(1.0f,5.0f);
    
    state->createAndAddParameter("cutoff", "Cutoff", "Cutoff", cutoffRange, 600.0f, nullptr, nullptr);
    state->createAndAddParameter("resonance", "Resonance", "Resonance", resRange, 1.0f, nullptr, nullptr);
    state->state = ValueTree("cutoff");
    state->state = ValueTree("resonance");
    tree.createAndAddParameter("cutoff", "Cutoff", "Cutoff", cutoffRange, 600.0f, nullptr, nullptr);
    tree.createAndAddParameter("resonance", "Resonance", "Resonance", resRange, 1.0f, nullptr, nullptr);
}

ButterSliceVstAudioProcessor::~ButterSliceVstAudioProcessor()
{
}

//==============================================================================
const String ButterSliceVstAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ButterSliceVstAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ButterSliceVstAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ButterSliceVstAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ButterSliceVstAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ButterSliceVstAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ButterSliceVstAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ButterSliceVstAudioProcessor::setCurrentProgram (int index)
{
}

const String ButterSliceVstAudioProcessor::getProgramName (int index)
{
    return {};
}

void ButterSliceVstAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ButterSliceVstAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    dsp::ProcessSpec spec;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    lowPassFilter.prepare(spec);
    lowPassFilter.reset();
}

void ButterSliceVstAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ButterSliceVstAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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



void ButterSliceVstAudioProcessor::updateFilter() {
    float freq = *tree.getRawParameterValue("cutoff");
    float res = *tree.getRawParameterValue("resonance");
    *lowPassFilter.state = *dsp::IIR::Coefficients<float>::makeLowPass(lastSampleRate, freq, res);
}

void ButterSliceVstAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //refers to buffer in this block
    dsp::AudioBlock<float> block (buffer);
    //
    updateFilter();
    lowPassFilter.process(dsp::ProcessContextReplacing<float> (block));
}
//==============================================================================

AudioProcessorValueTreeState& ButterSliceVstAudioProcessor::getState() {
    return *state;
}
//==============================================================================
bool ButterSliceVstAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ButterSliceVstAudioProcessor::createEditor()
{
    return new ButterSliceVstAudioProcessorEditor (*this);
}

//==============================================================================
void ButterSliceVstAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);
}

void ButterSliceVstAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

    if (tree.isValid()) {
        state->state = tree;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ButterSliceVstAudioProcessor();
}
