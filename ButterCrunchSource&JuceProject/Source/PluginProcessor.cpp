/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ButterCrunchVst3AudioProcessor::ButterCrunchVst3AudioProcessor()
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


    state->createAndAddParameter("drive", "Drive", "Drive", NormalisableRange<float>(0.f, 1.f, 0.0001), 1.0, nullptr, nullptr);

    state->createAndAddParameter("range", "Range", "Range", NormalisableRange<float>(0.f, 3000.f, 0.0001), 1.0, nullptr, nullptr);

    state->createAndAddParameter("blend", "Blend", "Blend", NormalisableRange<float>(0.f, 1.f, 0.0001), 1.0, nullptr, nullptr);

    state->createAndAddParameter("volume", "Volume", "Volume", NormalisableRange<float>(0.f, 3.f, 0.0001), 1.0, nullptr, nullptr);

    state->state = ValueTree("drive");
    state->state = ValueTree("range");
    state->state = ValueTree("blend");
    state->state = ValueTree("volume");

}




ButterCrunchVst3AudioProcessor::~ButterCrunchVst3AudioProcessor()
{
}

//==============================================================================
const String ButterCrunchVst3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ButterCrunchVst3AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ButterCrunchVst3AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ButterCrunchVst3AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ButterCrunchVst3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ButterCrunchVst3AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ButterCrunchVst3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void ButterCrunchVst3AudioProcessor::setCurrentProgram (int index)
{
}

const String ButterCrunchVst3AudioProcessor::getProgramName (int index)
{
    return {};
}

void ButterCrunchVst3AudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ButterCrunchVst3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ButterCrunchVst3AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ButterCrunchVst3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ButterCrunchVst3AudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    float drive = *state->getRawParameterValue("drive");
    float range = *state->getRawParameterValue("range");
    float blend = *state->getRawParameterValue("blend");
    float volume = *state->getRawParameterValue("volume");


    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //
        float* channelData = buffer.getWritePointer (channel);

        //
        ///
        for (int sample = 0; sample < buffer.getNumSamples(); sample++) {
            
            float cleanSig = *channelData;

            //
            *channelData *= drive * range;

            //The distortion algorithm                                                                    |kinda sorta a /2 here but hold a sec
            *channelData = ((((2.f / float_Pi) * atan(*channelData) * blend))); 
            //blend knob?
            //so the channelData is added with the cleanSignal. Addition makes the blend signal smooth.
            *channelData = *channelData + (cleanSig * (1.0 - blend));
            //volume knob
            *channelData = *channelData * volume;

            channelData++;        
        }
    }
}

//==============================================================================

AudioProcessorValueTreeState& ButterCrunchVst3AudioProcessor::getState() {

    return *state;
}


//==============================================================================
bool ButterCrunchVst3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ButterCrunchVst3AudioProcessor::createEditor()
{
    return new ButterCrunchVst3AudioProcessorEditor (*this);
}

//==============================================================================
void ButterCrunchVst3AudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);
}

void ButterCrunchVst3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new ButterCrunchVst3AudioProcessor();
}
