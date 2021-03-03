/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ButterSliceVstAudioProcessorEditor::ButterSliceVstAudioProcessorEditor (ButterSliceVstAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible(wall);

    addAndMakeVisible(filterCutoffDial = new Slider("Cutoff"));
    filterCutoffDial->setSliderStyle(Slider::RotaryVerticalDrag);
    filterCutoffDial->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    ///////
    ///////
    addAndMakeVisible(filterResDial = new Slider("Resonance"));
    filterResDial->setSliderStyle(Slider::RotaryVerticalDrag);
    filterResDial->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    //////
    ////////
    filterCutoffValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "cutoff", *filterCutoffDial);

    filterResValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "resonance", *filterResDial);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (250, 250);
}

ButterSliceVstAudioProcessorEditor::~ButterSliceVstAudioProcessorEditor()
{
}

//==============================================================================
void ButterSliceVstAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);

    g.setColour(Colours::mediumvioletred);
    g.setFont(15.0f);
    //g.drawFittedText ("Woah!", getLocalBounds(), Justification::centred, 1); 

    g.drawText("Cutoff", (25), (110), 100, 100, Justification::centred, false);
    g.drawText("Resonance", (125), (110), 100, 100, Justification::centred, false);
}

void ButterSliceVstAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    wall.setBounds(getLocalBounds());
    filterCutoffDial->setBounds(25, 50, 100, 100);

    filterResDial->setBounds(125, 50, 100, 100);
}
