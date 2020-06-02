#pragma once

#include <JuceHeader.h>
#include "Dimensions.h"
#include "MaterialSwitch.h"

using namespace std;

class TopBar : public Component, private TextButton::Listener
{
public:
    
    TopBar(Colour backgroundColour, VirtualRumbleAudioProcessor& p) : processor(p)
    {
        background = backgroundColour;
        
        bypassButtonAttach = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
                                            (processor.parameters, BYPASS_ID, bypassSwitch);
        
        bypassSwitch.setSize(SWITCH_W, 0.5*TOP_BAR_H);
        bypassSwitch.setTopLeftPosition(WIN_WIDTH - 2*BORDER - SWITCH_W - 16, 0.25*TOP_BAR_H);
        bypassSwitch.setAlpha(0.0f);
        bypassSwitch.setWantsKeyboardFocus(false);
        bypassSwitch.addListener(this);
        
        materialSwitch.setBounds(WIN_WIDTH - 2*BORDER - SWITCH_W - 16, 0.25*TOP_BAR_H, SWITCH_W, 0.5*TOP_BAR_H);
        materialSwitch.setState(processor.bypass);
        
        addAndMakeVisible(materialSwitch);
        addAndMakeVisible(bypassSwitch);
    }

    ~TopBar()
    {
        bypassButtonAttach.~unique_ptr();
    }

    void paint (Graphics& g) override
    {
        g.setColour(background);
        g.fillRoundedRectangle (0, 0, getWidth(), getHeight(), FILLET);
        
        g.drawImage(logo, 16, 0.05*getHeight(), 0.9*getHeight(), 0.9*getHeight(), 0, 0, 200, 200);
        
        g.setColour(Colours::whitesmoke);
        g.setFont(Font("Muli", 30.0f, Font::plain));
        g.drawText("Virtual Rumble - V. 1.0.2", 70, 0.1*getHeight(), 400, 0.8*getHeight(), Justification::centredLeft);
        
        g.setFont(TEXT_H);
        g.drawText("Bypass", WIN_WIDTH - 2*BORDER - SWITCH_W - 132, 0.2*getHeight(), 100,
                   0.6*getHeight(), Justification::centredRight);
    }

    void resized() override
    {
    }
    
    unique_ptr<AudioProcessorValueTreeState::ButtonAttachment> bypassButtonAttach;

private:
    
    VirtualRumbleAudioProcessor& processor;
    
    Colour background;
    Image logo = ImageCache::getFromMemory(BinaryData::logoAltColor_png, BinaryData::logoAltColor_pngSize);
    
    TextButton bypassSwitch;
    MaterialSwitch materialSwitch;
    
    void buttonClicked(Button* button) override
    {        
        processor.bypass = !processor.bypass;
        materialSwitch.setState(processor.bypass);
        materialSwitch.repaint();
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TopBar)
};
