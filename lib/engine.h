#ifndef ENGINE_H
#define ENGINE_H

#include "incl.h"

class Engine;   // Résolution des dépendances circulaires (c'est du patchwork...)

typedef uint8_t EngineMode;
typedef uint8_t TimerChannelUsed;

#include "lib.h"
#include "timer.h"


// ---EngineMode---
#define    ENG_OFF      0x04
#define    ENG_FORWARD  0x00
#define    ENG_BACKWARD 0x01

// #define pour TimerChannelUsed
                                        // | ENABLE | DIRECTION |
#define    T0CA 0   // PWM utilisé = OC0A. |   PB3  |    PB2    |
#define    T0CB 1   // PWM utilisé = OC0B. |   PB4  |    PB5    |
#define    T1CA 2   // PWM utilisé = OC1A. |   PD5  |    PD3    |
#define    T1CB 3/* // PWM utilisé = OC1B. |   PD4  |    PD2    |
#define    T2CA 4   // PWM utilisé = OC2A. |   PD7  |    ???    |
#define    T2CB 5*/ // PWM utilisé = OC2B. |   PD6  |    ???    |


class Engine {
public:
    Engine(TimerChannelUsed tcu);
    
    void setPower(EngineMode mode, uint16_t occrNX);
    
    void setMode(EngineMode mode);
    
    Timer* getTimer();
    
private:
    Timer* _timer;
    bool _isOnChannelA;
    
    uint8_t _FORWARD, _BACKWARD;
    uint8_t _THIS_MASK;
    volatile uint8_t* _PORT;
};
#endif // ENGINE_H
