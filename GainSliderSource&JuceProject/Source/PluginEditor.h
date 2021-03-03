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
class GainSliderwithAutomationVst3AudioProcessorEditor  : public AudioProcessorEditor
{
public:
    GainSliderwithAutomationVst3AudioProcessorEditor (GainSliderwithAutomationVst3AudioProcessor&);
    ~GainSliderwithAutomationVst3AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:

    //points for gui

    ScopedPointer<Slider> gainSlider;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> gainValue;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainSliderwithAutomationVst3AudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainSliderwithAutomationVst3AudioProcessorEditor)
};
