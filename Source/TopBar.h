#pragma once

#include <JuceHeader.h>
#include "Dimensions.h"
#include "MaterialSwitch.h"
#include "ProcessorData.h"


class TopBar : public Component, private TextButton::Listener
{
public:
    
    TopBar(ProcessorData* p)
    {
        processorParams = p;
        
        bypassSwitch.setBounds(WIN_WIDTH - 2*BORDER - SWITCH_W - 16, 0.25*TOP_BAR_H, SWITCH_W, 0.5*TOP_BAR_H);
        bypassSwitch.setAlpha(0.0f);
        bypassSwitch.setWantsKeyboardFocus(false);
        bypassSwitch.addListener(this);
        
        materialSwitch.setBounds(WIN_WIDTH - 2*BORDER - SWITCH_W - 16, 0.25*TOP_BAR_H, SWITCH_W, 0.5*TOP_BAR_H);
        materialSwitch.setState(processorParams->isRunning);
        
        addAndMakeVisible(materialSwitch);
        addAndMakeVisible(bypassSwitch);
    }

    ~TopBar()
    {
    }

    void paint (Graphics& g) override
    {
        g.setColour(Colour(44,50,65));
        g.fillRoundedRectangle (0, 0, getWidth(), getHeight(), FILLET);
        
        g.drawImage(logo, 16, 0.05*getHeight() + 1, 0.9*getHeight(), 0.9*getHeight(), 0, 0, 200, 200);
        
        g.setColour(Colours::whitesmoke);
        g.setFont(Font("Muli", TEXT_H, Font::plain));
        g.drawText("TiM - The Incremental Metronome 0.0.0", 70, 0.1*getHeight(), 400, 0.8*getHeight(), Justification::centredLeft);
        g.drawText("Start", WIN_WIDTH - 2*BORDER - SWITCH_W - 132, 0.1*getHeight(), 100,
                   0.8*getHeight(), Justification::centredRight);
    }

    void resized() override
    {
    }
    
    void spaceKeyPressed()
    {
        updateParam();
    }

private:
    
    ProcessorData* processorParams;
    
    Image logo = ImageCache::getFromMemory(BinaryData::logoAltColor_png, BinaryData::logoAltColor_pngSize);
    
    TextButton bypassSwitch;
    MaterialSwitch materialSwitch;
    
    void buttonClicked(Button* button) override
    {        
        updateParam();
    }
    
    void updateParam()
    {
        processorParams->isRunning = !processorParams->isRunning;
        materialSwitch.setState(processorParams->isRunning);
        materialSwitch.repaint();
        
        processorParams->beat = 1;
        processorParams->barsDone = 0;
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TopBar)
};
