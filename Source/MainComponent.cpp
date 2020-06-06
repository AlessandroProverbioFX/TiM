#include "MainComponent.h"
#include "Dimensions.h"
#include "Ranges.h"


MainComponent::MainComponent(): topBar(&processorParams), metronomeControls(&processorParams), bottomBar(&processorParams)
{
    setSize (WIN_WIDTH, WIN_HEIGHT);
    setAudioChannels (0, 2);
    
    topBar.setBounds(BORDER, BORDER, WIN_WIDTH - 2*BORDER, TOP_BAR_H);
    metronomeControls.setBounds(BORDER, 2*BORDER + TOP_BAR_H, WIN_WIDTH - 2*BORDER, CENTRAL_BLOCK_H);   
    bottomBar.setBounds(BORDER, WIN_HEIGHT - BORDER - BOTTOM_BAR_H, WIN_WIDTH - 2*BORDER, BOTTOM_BAR_H);
    
    setWantsKeyboardFocus(true);
    
    addAndMakeVisible(topBar);
    addAndMakeVisible(metronomeControls);
    addAndMakeVisible(bottomBar);
    
    updateTimerAndBpm();
    
    formatManager.registerBasicFormats();
    
    ticReader = formatManager.createReaderFor(tic);
    tocReader = formatManager.createReaderFor(toc);
    std::unique_ptr<AudioFormatReaderSource> ticTempSource (new AudioFormatReaderSource (ticReader, true));
    std::unique_ptr<AudioFormatReaderSource> tocTempSource (new AudioFormatReaderSource (tocReader, true));
    ticSource.reset (ticTempSource.release());
    tocSource.reset (tocTempSource.release());
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    if (!processorParams.isRunning)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
 
    transportSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    transportSource.releaseResources();
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
        updateTimerAndBpm();
        return true;
    }
    if ( k.getTextCharacter() == '-')
    {
        processorParams.bpm = (processorParams.bpm - 1 >= BPM_START) ? processorParams.bpm - 1 : BPM_START;
        updateTimerAndBpm();
        return true;
    }
    
    return false;
}

void MainComponent::updateTimerAndBpm()
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
            updateTimerAndBpm();
            processorParams.barsDone = 0;
        }
        
        // Update BPM
        if (processorParams.hasBpmChanged)
        {
            updateTimerAndBpm();
            processorParams.hasBpmChanged = 0;
        }
        
        // Play Metronome Sound
        if (processorParams.beat == 1 && processorParams.isBeatOn)
        {
            transportSource.setSource(ticSource.get(), 0, nullptr, ticReader->sampleRate);
            transportSource.start();
        }
        else
        {
            transportSource.setSource(tocSource.get(), 0, nullptr, ticReader->sampleRate);
            transportSource.start();
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


