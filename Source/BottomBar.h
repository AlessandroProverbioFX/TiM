#pragma once

#include <JuceHeader.h>
#include "Dimensions.h"
#include "MaterialSwitch.h"
#include "ProcessorData.h"

using namespace std;

class BottomBar : public Component, private TextButton::Listener
{
public:
    
    BottomBar(ProcessorData* p)
    {
        processorParams = p;
        
        incrementSwitch.setBounds(BOTTOM_BLOCK_W - 5, 0.25*BOTTOM_BAR_H, SWITCH_W, 0.5*BOTTOM_BAR_H);
        incrementSwitch.setAlpha(0.0f);
        incrementSwitch.setWantsKeyboardFocus(false);
        incrementSwitch.addListener(this);
        
        matIncrementSwitch.setBounds(BOTTOM_BLOCK_W - 5, 0.25*BOTTOM_BAR_H, SWITCH_W, 0.5*BOTTOM_BAR_H);
        matIncrementSwitch.setState(processorParams->isIncrementOn);
        
        beatSwitch.setBounds(2*BOTTOM_BLOCK_W + SWITCH_W - 10, 0.25*BOTTOM_BAR_H, SWITCH_W, 0.5*BOTTOM_BAR_H);
        beatSwitch.setAlpha(0.0f);
        beatSwitch.setWantsKeyboardFocus(false);
        beatSwitch.addListener(this);
        
        matBeatSwitch.setBounds(2*BOTTOM_BLOCK_W + SWITCH_W - 10, 0.25*BOTTOM_BAR_H, SWITCH_W, 0.5*BOTTOM_BAR_H);
        matBeatSwitch.setState(processorParams->isBeatOn);
        

        addAndMakeVisible(matIncrementSwitch);
        addAndMakeVisible(matBeatSwitch);
        addAndMakeVisible(incrementSwitch);
        addAndMakeVisible(beatSwitch);
        
        Typeface::Ptr muli = Typeface::createSystemTypefaceFor (BinaryData::Muli_ttf, BinaryData::Muli_ttfSize);
        getLookAndFeel().setDefaultSansSerifTypeface(muli);
    }

    ~BottomBar()
    {
    }

    void paint (Graphics& g) override
    {
        g.setColour(Colour(44,50,65));
        g.fillRoundedRectangle (0, 0, getWidth(), getHeight(), FILLET);
        
        g.setColour(Colours::whitesmoke);
        g.setFont(TEXT_H);
        g.drawText("Incremental Speed", 0, 0.1*getHeight(), BOTTOM_BLOCK_W, 0.8*getHeight(), Justification::centred);
        g.drawText("Beat Accent", BOTTOM_BLOCK_W + SWITCH_W + 20, 0.1*getHeight(), BOTTOM_BLOCK_W, 0.8*getHeight(), Justification::centred);
    }

    void resized() override
    {
    }

private:
    
    ProcessorData* processorParams;
       
    TextButton incrementSwitch;
    TextButton beatSwitch;
    MaterialSwitch matIncrementSwitch;
    MaterialSwitch matBeatSwitch;
    
    void buttonClicked(Button* button) override
    {
        if (button == &incrementSwitch)
        {
            processorParams->isIncrementOn = !processorParams->isIncrementOn;
            matIncrementSwitch.setState(processorParams->isIncrementOn);
            matIncrementSwitch.repaint();
            
            processorParams->barsDone = 0;
            processorParams->beat = 1;
        }
        else
        {
            processorParams->isBeatOn = !processorParams->isBeatOn;
            matBeatSwitch.setState(processorParams->isBeatOn);
            matBeatSwitch.repaint();
        }
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BottomBar)
};
