/*
  ==============================================================================

    FilterComponent.cpp
    Created: 5 May 2020 9:25:41am
    Author:  rummy

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (Graphics& g)
{
    //Drawin a box
    Rectangle <float> wall(25, 25, 200, 200);
    //g.fillRect(wall);
    g.drawRect(wall);
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
