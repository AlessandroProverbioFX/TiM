#include "MainComponent.h"
#include "Dimensions.h"


MainComponent::MainComponent()
{
    setSize (WIN_WIDTH, WIN_HEIGHT);
    setAudioChannels (0, 1);
    
    topBar.setBounds(BORDER, BORDER, WIN_WIDTH - 2*BORDER, TOP_BAR_H);
    metronomeControls.setBounds(BORDER, 2*BORDER + TOP_BAR_H, WIN_WIDTH - 2*BORDER, CENTRAL_BLOCK_H);   
    bottomBar.setBounds(BORDER, WIN_HEIGHT - BORDER - BOTTOM_BAR_H, WIN_WIDTH - 2*BORDER, BOTTOM_BAR_H);
    
    addAndMakeVisible(topBar);
    addAndMakeVisible(metronomeControls);
    addAndMakeVisible(bottomBar);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{

}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{

}


void MainComponent::paint (Graphics& g)
{
    g.fillAll(Colour(33,36,45));
}

void MainComponent::resized()
{
}
