#pragma once

#include <JuceHeader.h>
#include "TopBar.h"
#include "BottomBar.h"
#include "MetronomeControls.h"
#include "ProcessorData.h"

class MainComponent : public AudioAppComponent
{
public:
    
    MainComponent();
    ~MainComponent();
    
    ProcessorData processorParams;

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint (Graphics& g) override;
    void resized() override;

private:
    
    TopBar topBar;
    MetronomeControls metronomeControls;
    BottomBar bottomBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
