#ifndef DRIVE_H
#define DRIVE_H

#include "lib.h"
#include "engine.h"

typedef uint8_t DriveDir;
const DriveDir
    DIR_OFF = 0x00,
    DIR_RIGHT = 0x01,
    DIR_LEFT = 0x02;

class Drive {
public:
    static void init(TimerChannelUsed tcuLeft, TimerChannelUsed tcuRight,
                     uint8_t right, uint8_t left);
    
    /**
     * @brief   Fait avancer/reculer le robot.
     */
    static void setMovement(EngineMode mode, uint8_t power);
    /**
     * @brief   Fait pivoter le robot.
     */
    static void setRotation(DriveDir dir, uint8_t power);
    
private:
    static Engine _engL, _engR;
    static uint8_t CONST_R, CONST_L;
};

uint8_t Drive::CONST_R = 0xFF, Drive::CONST_L = 0xFF;

#endif // DRIVE_H
