#pragma once

#include <JuceHeader.h>
#include "Dimensions.h"
#include "Ranges.h"
#include "ProcessorData.h"

class BigSliderLookAndFeel : public LookAndFeel_V4
{
public:
    
    BigSliderLookAndFeel() { }
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                           float sliderPos,
                                           float minSliderPos,
                                           float maxSliderPos,
                                           const Slider::SliderStyle style, Slider& slider)
    {
        if (slider.isBar())
        {
            g.setColour (slider.findColour (Slider::trackColourId));
            g.fillRect (slider.isHorizontal() ? Rectangle<float> (static_cast<float> (x), y + 0.5f, sliderPos - x, height - 1.0f)
                                              : Rectangle<float> (x + 0.5f, sliderPos, width - 1.0f, y + (height - sliderPos)));
        }
        else
        {
            auto isTwoVal   = (style == Slider::SliderStyle::TwoValueVertical   || style == Slider::SliderStyle::TwoValueHorizontal);
            auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

            auto trackWidth = jmin (6.0f, slider.isHorizontal() ? height * 0.25f : width * 0.25f);

            Point<float> startPoint (slider.isHorizontal() ? x : x + width * 0.5f,
                                     slider.isHorizontal() ? y + height * 0.5f : height + y);

            Point<float> endPoint (slider.isHorizontal() ? width + x : startPoint.x,
                                   slider.isHorizontal() ? startPoint.y : y);

            Path backgroundTrack;
            backgroundTrack.startNewSubPath (startPoint);
            backgroundTrack.lineTo (endPoint);
            g.setColour (slider.findColour (Slider::backgroundColourId));
            g.strokePath (backgroundTrack, { trackWidth*2, PathStrokeType::curved, PathStrokeType::rounded });

            Path valueTrack;
            Point<float> minPoint, maxPoint, thumbPoint;

            if (isTwoVal || isThreeVal)
            {
                minPoint = { slider.isHorizontal() ? minSliderPos : width * 0.5f,
                             slider.isHorizontal() ? height * 0.5f : minSliderPos };

                if (isThreeVal)
                    thumbPoint = { slider.isHorizontal() ? sliderPos : width * 0.5f,
                                   slider.isHorizontal() ? height * 0.5f : sliderPos };

                maxPoint = { slider.isHorizontal() ? maxSliderPos : width * 0.5f,
                             slider.isHorizontal() ? height * 0.5f : maxSliderPos };
            }
            else
            {
                auto kx = slider.isHorizontal() ? sliderPos : (x + width * 0.5f);
                auto ky = slider.isHorizontal() ? (y + height * 0.5f) : sliderPos;

                minPoint = startPoint;
                maxPoint = { kx, ky };
            }

            auto thumbWidth = (getSliderThumbRadius (slider))*2;

            valueTrack.startNewSubPath (minPoint);
            valueTrack.lineTo (isThreeVal ? thumbPoint : maxPoint);
            g.setColour (slider.findColour (Slider::trackColourId));
            g.strokePath (valueTrack, { trackWidth*2, PathStrokeType::curved, PathStrokeType::rounded });

            if (! isTwoVal)
            {
                g.setColour (Colours::whitesmoke);
                g.fillEllipse (Rectangle<float> (static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre (isThreeVal ? thumbPoint : maxPoint));
            }

            if (isTwoVal || isThreeVal)
            {
                auto sr = jmin (trackWidth, (slider.isHorizontal() ? height : width) * 0.4f);
                auto pointerColour = slider.findColour (Slider::thumbColourId);

                if (slider.isHorizontal())
                {
                    drawPointer (g, minSliderPos - sr,
                                 jmax (0.0f, y + height * 0.5f - trackWidth * 2.0f),
                                 trackWidth * 2.0f, pointerColour, 2);

                    drawPointer (g, maxSliderPos - trackWidth,
                                 jmin (y + height - trackWidth * 2.0f, y + height * 0.5f),
                                 trackWidth * 2.0f, pointerColour, 4);
                }
                else
                {
                    drawPointer (g, jmax (0.0f, x + width * 0.5f - trackWidth * 2.0f),
                                 minSliderPos - trackWidth,
                                 trackWidth * 2.0f, pointerColour, 1);

                    drawPointer (g, jmin (x + width - trackWidth * 2.0f, x + width * 0.5f), maxSliderPos - sr,
                                 trackWidth * 2.0f, pointerColour, 3);
                }
            }
        }
    }
    
    void fillTextEditorBackground (Graphics&, int width, int height, TextEditor&)
    {
        
    };
    void drawTextEditorOutline (Graphics&, int width, int height, TextEditor&)
    {
        
    };
    
    Label* createSliderTextBox (Slider& slider)
    {
        auto l = new Label;

        l->setJustificationType (Justification::centred);
        l->setFont(Font("Muli", 32, Font::plain));
        l->setKeyboardType (TextInputTarget::decimalKeyboard);
        
        l->setColour (Label::textColourId, slider.findColour (Slider::textBoxTextColourId));
        l->setColour (Label::backgroundColourId,
                      (slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
                                ? Colours::transparentBlack
                                : slider.findColour (Slider::textBoxBackgroundColourId));
        l->setColour (Label::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));
        l->setColour (TextEditor::textColourId, slider.findColour (Slider::textBoxTextColourId));
        l->setColour (TextEditor::backgroundColourId,
                      slider.findColour (Slider::textBoxBackgroundColourId)
                            .withAlpha ((slider.getSliderStyle() == Slider::LinearBar || slider.getSliderStyle() == Slider::LinearBarVertical)
                                            ? 0.7f : 1.0f));
        l->setColour (TextEditor::outlineColourId, slider.findColour (Slider::textBoxOutlineColourId));
        l->setColour (TextEditor::highlightColourId, slider.findColour (Slider::textBoxHighlightColourId));

        return l;
    }
};


class MetronomeControls : public Component, private Slider::Listener
{
public:
    
    MetronomeControls(ProcessorData* p): backgroundColour(58,64,81)
    {
        processorParams = p;
        
        bpmSlider.setLookAndFeel(&bigSliderLookAndFeel);
        bpmSlider.setBounds(150, 0, SLIDER_W, SLIDER_H);
        bpmSlider.setSliderStyle(Slider::LinearHorizontal);
        bpmSlider.setColour(Slider::thumbColourId, Colours::whitesmoke);
        bpmSlider.setColour(Slider::trackColourId, Colours::cornflowerblue);
        bpmSlider.setColour(Slider::backgroundColourId, Colour(33,36,45));
        bpmSlider.setRange(BPM_START, BPM_END, 1);
        bpmSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxRight, false, 60, 32);
        bpmSlider.setColour(Slider::textBoxBackgroundColourId, backgroundColour);
        bpmSlider.setColour(Slider::textBoxTextColourId, Colours::whitesmoke);
        bpmSlider.setColour(Slider::textBoxOutlineColourId, backgroundColour);
        bpmSlider.setValue(processorParams->bpm);
        bpmSlider.addListener(this);
        
        incrementSlider.setLookAndFeel(&bigSliderLookAndFeel);
        incrementSlider.setBounds(150, SLIDER_H, SLIDER_W, SLIDER_H);
        incrementSlider.setSliderStyle(Slider::LinearHorizontal);
        incrementSlider.setColour(Slider::thumbColourId, Colours::whitesmoke);
        incrementSlider.setColour(Slider::trackColourId, Colours::cornflowerblue);
        incrementSlider.setColour(Slider::backgroundColourId, Colour(33,36,45));
        incrementSlider.setRange(INCREMENT_START, INCREMENT_END, 1);
        incrementSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxRight, true, 60, 32);
        incrementSlider.setColour(Slider::textBoxBackgroundColourId, backgroundColour);
        incrementSlider.setColour(Slider::textBoxTextColourId, Colours::whitesmoke);
        incrementSlider.setColour(Slider::textBoxOutlineColourId, backgroundColour);
        incrementSlider.setValue(processorParams->increment);
        incrementSlider.addListener(this);
        
        barsSlider.setLookAndFeel(&bigSliderLookAndFeel);
        barsSlider.setBounds(150, 2*SLIDER_H, SLIDER_W, SLIDER_H);
        barsSlider.setSliderStyle(Slider::LinearHorizontal);
        barsSlider.setColour(Slider::thumbColourId, Colours::whitesmoke);
        barsSlider.setColour(Slider::trackColourId, Colours::cornflowerblue);
        barsSlider.setColour(Slider::backgroundColourId, Colour(33,36,45));
        barsSlider.setRange(BARS_START, BARS_END, 1);
        barsSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxRight, true, 60, 32);
        barsSlider.setColour(Slider::textBoxBackgroundColourId, backgroundColour);
        barsSlider.setColour(Slider::textBoxTextColourId, Colours::whitesmoke);
        barsSlider.setColour(Slider::textBoxOutlineColourId, backgroundColour);
        barsSlider.setValue(processorParams->bars);
        barsSlider.addListener(this);
    
        addAndMakeVisible(bpmSlider);
        addAndMakeVisible(incrementSlider);
        addAndMakeVisible(barsSlider);
    }

    ~MetronomeControls()
    {
        bpmSlider.setLookAndFeel(nullptr);
        incrementSlider.setLookAndFeel(nullptr);
        barsSlider.setLookAndFeel(nullptr);
    }

    void paint (Graphics& g) override
    {
        g.setColour(Colour(58,64,81));
        g.fillRoundedRectangle (0, 0, getWidth(), getHeight(), FILLET);
        
        g.setColour(Colours::whitesmoke);
        g.setFont(Font("Muli", 32, Font::plain));
        
        g.drawText("BPM",       10, 0,          130, BLOCKS_H, Justification::centred);
        g.drawText("Increment", 10, BLOCKS_H,   130, BLOCKS_H, Justification::centred);
        g.drawText("Bars",      10, 2*BLOCKS_H, 130, BLOCKS_H, Justification::centred);
    }

    void resized() override
    {
    }
    
    void updateBpm()
    {
        bpmSlider.setValue(processorParams->bpm);
    }

private:
    
    ProcessorData* processorParams;
      
    Slider bpmSlider;
    Slider incrementSlider;
    Slider barsSlider;
    
    Colour backgroundColour;
    
    BigSliderLookAndFeel bigSliderLookAndFeel;
    
    void sliderValueChanged(Slider* slider) override
    {
        if (slider == &bpmSlider)
        {
            processorParams->bpm = bpmSlider.getValue();
            processorParams->hasBpmChanged = 1;
        }
        else if (slider == &barsSlider)
        {
            processorParams->bars = barsSlider.getValue();
            processorParams->barsDone = 0;
        }
        else
        {
            processorParams->increment = incrementSlider.getValue();
        }
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MetronomeControls)
};
