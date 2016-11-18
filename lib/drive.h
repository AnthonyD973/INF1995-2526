#ifndef DRIVE_H
#define DRIVE_H

#include "incl.h"

typedef uint8_t DriveDir;

#include "lib.h"
#include "engine.h"

/* 
 * RegEx   : (\s*[A-Z0-9_]*\s*)=\s*(0x[0-9a-fA-F]+)[,;]
 * Pattern : #define\1\2
 * 
 */

// ---DriveDir---
#define    DIR_OFF 0x00
#define    DIR_RIGHT 0x01
#define    DIR_LEFT 0x02

class Drive {
public:
    static void init(TimerChannelUsed tcuLeft, TimerChannelUsed tcuRight,
                     uint8_t constLeft, uint8_t constRight);
    
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

#endif // DRIVE_H
