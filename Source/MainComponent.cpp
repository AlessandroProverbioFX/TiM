#include "MainComponent.h"
#include "Dimensions.h"
#include "Ranges.h"


MainComponent::MainComponent(): topBar(&processorParams), metronomeControls(&processorParams), bottomBar(&processorParams)
{
    setSize (WIN_WIDTH, WIN_HEIGHT);
    setAudioChannels (0, 1);
    
    topBar.setBounds(BORDER, BORDER, WIN_WIDTH - 2*BORDER, TOP_BAR_H);
    metronomeControls.setBounds(BORDER, 2*BORDER + TOP_BAR_H, WIN_WIDTH - 2*BORDER, CENTRAL_BLOCK_H);   
    bottomBar.setBounds(BORDER, WIN_HEIGHT - BORDER - BOTTOM_BAR_H, WIN_WIDTH - 2*BORDER, BOTTOM_BAR_H);
    
    setWantsKeyboardFocus(true);
    
    addAndMakeVisible(topBar);
    addAndMakeVisible(metronomeControls);
    addAndMakeVisible(bottomBar);
    
    updateTimer();
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

bool MainComponent::keyPressed(const KeyPress &k)
{
    if( k.getTextCharacter() == ' ' )
    {
        topBar.spaceKeyPressed();
        return true;
    }
    if ( k.getTextCharacter() == '+')
    {
        processorParams.bpm = (processorParams.bpm + 1 <= BPM_END) ? processorParams.bpm + 1 : BPM_END;
        updateTimer();
        return true;
    }
    if ( k.getTextCharacter() == '-')
    {
        processorParams.bpm = (processorParams.bpm - 1 >= BPM_START) ? processorParams.bpm - 1 : BPM_START;
        updateTimer();
        return true;
    }
    
    return false;
}

void MainComponent::updateTimer()
{
    Timer::startTimer( (60.0 / float(processorParams.bpm))*1000 );
    metronomeControls.updateBpm();
}

void MainComponent::timerCallback()
{
    if (processorParams.isRunning)
    {
        // Update BPM with Increment
        if (processorParams.barsDone == processorParams.bars &&
            processorParams.isIncrementOn)
        {
            processorParams.bpm = (processorParams.bpm + processorParams.increment <= BPM_END) ?
                                   processorParams.bpm + processorParams.increment : BPM_END;
            updateTimer();
            processorParams.barsDone = 0;
        }
        // Update BPM
        if (processorParams.hasBpmChanged)
        {
            updateTimer();
            processorParams.hasBpmChanged = 0;
        }
        
        // Play Metronome Sound
        if (processorParams.beat == 1 && processorParams.isBeatOn)
        {
            // Play Tik
            std::cout << processorParams.beat << " start " << processorParams.bpm << std::endl;
        }
        else
        {
            // Play Tok
            std::cout << processorParams.beat << " " << processorParams.bpm <<  std::endl;
        }
        
        // Update Bars Count
        if (processorParams.beat == 4)
        {
            processorParams.beat = 1;
            processorParams.barsDone += 1;
        }
        else
        {
            processorParams.beat += 1;
        }
    }
}

