/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FilterComponent.h"
//==============================================================================
/**
*/
class ButterSliceVstAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ButterSliceVstAudioProcessorEditor (ButterSliceVstAudioProcessor&);
    ~ButterSliceVstAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    ScopedPointer<Slider> filterCutoffDial;
    ScopedPointer<Slider> filterResDial;

    ScopedPointer < AudioProcessorValueTreeState::SliderAttachment> filterCutoffValue;
    ScopedPointer < AudioProcessorValueTreeState::SliderAttachment> filterResValue;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ButterSliceVstAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButterSliceVstAudioProcessorEditor)
        FilterComponent wall;
};
