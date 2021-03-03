/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ButterCrunchVst3AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ButterCrunchVst3AudioProcessorEditor (ButterCrunchVst3AudioProcessor&);
    ~ButterCrunchVst3AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    ScopedPointer<Slider> driveKnob;
    ScopedPointer<Slider> rangeKnob;
    ScopedPointer<Slider> blendKnob;
    ScopedPointer<Slider> volumeKnob;

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> blendAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> volumeAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ButterCrunchVst3AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ButterCrunchVst3AudioProcessorEditor)
};
