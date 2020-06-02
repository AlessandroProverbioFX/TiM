#pragma once

#include <JuceHeader.h>


class MaterialSwitch : public Component
{
public:
    
    MaterialSwitch(): trackOnColor(Colours::cornflowerblue), trackOffColor(33,36,45),
                      thumbOnColor(Colours::whitesmoke), thumbOffColor(89,96,115)
    {
    }

    ~MaterialSwitch()
    {
    }

    void paint (Graphics& g) override
    {
        if (isOn)
        {
            g.setColour(trackOnColor);
            g.fillRoundedRectangle (0.025*getWidth(), 0.025*getHeight(), 0.95*getWidth(), 0.95*getHeight(), 12);
            
            g.setColour(thumbOnColor);
            g.fillEllipse(getWidth() - getHeight(), 0, getHeight(), getHeight());
        }
        else
        {
            g.setColour(trackOffColor);
            g.fillRoundedRectangle (0.025*getWidth(), 0.025*getHeight(), 0.95*getWidth(), 0.95*getHeight(), 12);
            
            g.setColour(thumbOffColor);
            g.fillEllipse(0, 0, getHeight(), getHeight());
        }

    }

    void resized() override
    {

    }
    
    void setState(int isOnFromParent)
    {
        isOn = isOnFromParent;
        repaint();
    }
    
    void setTrackOnColor(Colour newColor)
    {
        trackOnColor = newColor;
    }
    
    void setTrackOffColor(Colour newColor)
    {
        trackOffColor = newColor;
    }
    
    void setThumbOnColor(Colour newColor)
    {
        thumbOnColor = newColor;
    }
    
    void setThumbOffColor(Colour newColor)
    {
        thumbOffColor = newColor;
    }

private:
    
    int isOn;
    
    Colour trackOnColor;
    Colour trackOffColor;
    Colour thumbOnColor;
    Colour thumbOffColor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MaterialSwitch)
};
