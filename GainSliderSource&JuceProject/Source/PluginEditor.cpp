/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainSliderwithAutomationVst3AudioProcessorEditor::GainSliderwithAutomationVst3AudioProcessorEditor (GainSliderwithAutomationVst3AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    

    addAndMakeVisible(gainSlider = new Slider("Gain"));
    gainSlider->setSliderStyle(Slider::RotaryVerticalDrag);
    gainSlider->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    //
    gainValue = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "gain", *gainSlider);
    //gainSlider->setRange(0.0f, 1.0f);
    //gainSlider->setValue(0.5f);
    //gainSlider->addListener(&this);

    setSize(100, 100);
}

GainSliderwithAutomationVst3AudioProcessorEditor::~GainSliderwithAutomationVst3AudioProcessorEditor()
{
}

//==============================================================================
void GainSliderwithAutomationVst3AudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setColour (Colours::mediumvioletred);
    g.setFont (15.0f);
    g.drawText ("Gain", 0,0,100,100, Justification::centred, false);
}

void GainSliderwithAutomationVst3AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    Rectangle<int> bounds = getLocalBounds();
    //gainSlider->setBounds(0,0,100,100);


    FlexBox flexbox;

    flexbox.flexDirection = FlexBox::Direction::row;
    flexbox.flexWrap = FlexBox::Wrap::wrap;
    flexbox.alignContent = FlexBox::AlignContent::stretch;

    Array<FlexItem> itemArray;
    itemArray.add(FlexItem(100,100,*gainSlider));

    flexbox.items = itemArray;

    flexbox.performLayout(bounds);
}


