/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ButterCrunchVst3AudioProcessorEditor::ButterCrunchVst3AudioProcessorEditor (ButterCrunchVst3AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

    addAndMakeVisible(driveKnob = new Slider("Drive"));
    driveKnob->setSliderStyle(Slider::RotaryVerticalDrag);
    driveKnob->setTextBoxStyle(Slider::NoTextBox, false, 100,100);

    addAndMakeVisible(rangeKnob = new Slider("Range"));
    rangeKnob->setSliderStyle(Slider::RotaryVerticalDrag);
    rangeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

    addAndMakeVisible(blendKnob = new Slider("Blend"));
    blendKnob->setSliderStyle(Slider::RotaryVerticalDrag);
    blendKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

    addAndMakeVisible(volumeKnob = new Slider("Volume"));
    volumeKnob->setSliderStyle(Slider::RotaryVerticalDrag);
    volumeKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);

    driveAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "drive", *driveKnob);

    rangeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "range", *rangeKnob);

    blendAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "blend", *blendKnob);

    volumeAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "volume", *volumeKnob);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 100);
}

ButterCrunchVst3AudioProcessorEditor::~ButterCrunchVst3AudioProcessorEditor()
{
}

//==============================================================================
void ButterCrunchVst3AudioProcessorEditor::paint (Graphics& g)
{
    Rectangle<int> bounds = getLocalBounds();
    Rectangle <float> wall(4,4,92,92);
    Rectangle <float> wall2(104, 4, 92, 92);
    Rectangle <float> wall3(204, 4, 92, 92);
    Rectangle <float> wall4(304, 4, 92, 92);
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::transparentBlack);

    g.setColour (Colours::darkslategrey);
    g.setFont (15.0f);
    //g.drawFittedText ("Woah!", getLocalBounds(), Justification::centred, 1); 
    g.drawText("Drive", ( (getWidth() / 4) * 1) - (100), (getHeight() / 3) - 25, 100, 100, Justification::centred, false);
    g.drawText("Range", ((getWidth() / 4) * 2) - (100), (getHeight() / 3) - 25, 100, 100, Justification::centred, false);
    g.drawText("Blend", ((getWidth() / 4) * 3) - (100), (getHeight() / 3) - 25, 100, 100, Justification::centred, false);
    g.drawText("Volume", ((getWidth() / 4) * 4) - (100), (getHeight() / 3) - 25, 100, 100, Justification::centred, false);

    g.drawRoundedRectangle(wall, 3.0f, 9.0f); g.drawRoundedRectangle(wall2, 3.0f, 9.0f); 
    g.drawRoundedRectangle(wall3, 3.0f, 9.0f); g.drawRoundedRectangle(wall4, 3.0f, 9.0f);   
    
}

void ButterCrunchVst3AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    /*
    So we bring in driveKnob 
    by reference and call set bounds() -- 
    
                                 we divide the width by 5 and mult by it's desired position, same with y
                                                                                
                                                        
                                 This is the x position,            y position,                x size, y size.   */
    //driveKnob->setBounds(     ( (getWidth() / 5) * 1) - (100 / 2), (getHeight() / 4) - (100 / 2), 100, 100);

    //rangeKnob->setBounds(     ( (getWidth() / 5) * 2) - (100 / 2), (getHeight() / 4) - (100 / 2), 100, 100);

    //blendKnob->setBounds(     ( (getWidth() / 5) * 3) - (100 / 2), (getHeight() / 4) - (100 / 2), 100, 100);

    //volumeKnob->setBounds(    ( (getWidth() / 5) * 4) - (100 / 2), (getHeight() / 4) - (100 / 2), 100, 100);


    Rectangle<int> bounds = getLocalBounds();

    FlexBox flexbox;

    flexbox.flexDirection = FlexBox::Direction::row;
    flexbox.flexWrap = FlexBox::Wrap::wrap;
    flexbox.alignContent = FlexBox::AlignContent::stretch;

    Array<FlexItem> itemArray;
    itemArray.add(FlexItem(100, 100, *driveKnob));
    itemArray.add(FlexItem(100, 100, *rangeKnob));
    itemArray.add(FlexItem(100, 100, *blendKnob));
    itemArray.add(FlexItem(100, 100, *volumeKnob));
    flexbox.items = itemArray;
    flexbox.performLayout(bounds);
}
