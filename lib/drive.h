#ifndef DRIVE_H
#define DRIVE_H

#include "lib.h"
#include "engine.h"

class Drive {
public:
    static void init(TimerChannelUsed tcuLeft, TimerChannelUsed tcuRight);
    
    static void setPower(EngineMode mode, uint8_t power);
    
private:
    static void _forward(uint8_t power);
    
    static Engine _engL, _engR;
};

#endif // DRIVE_H