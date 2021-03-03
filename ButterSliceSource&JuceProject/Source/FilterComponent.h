/*
  ==============================================================================

    FilterComponent.h
    Created: 5 May 2020 9:25:41am
    Author:  rummy

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent    : public Component
{
public:
    FilterComponent();
    ~FilterComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
