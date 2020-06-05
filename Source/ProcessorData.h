#pragma once

#include "Ranges.h"

class ProcessorData
{

public:
    
    int bpm {BPM_STD};
    int increment {INCREMENT_STD};
    int bars {BARS_STD};
    
    int isRunning {0};
    int isIncrementOn {0};
    int isBeatOn {1};
    
    int beat {1};
    int barsDone {0};
    
    int hasBpmChanged {0};
    
};
