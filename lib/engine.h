#ifndef ENGINE_H // ENGINE_H
#define ENGINE_H

#include "lib.h"
#include "timer.h"

class Timer0; // Nécessaire pour résoudre la dépendance circulaire.
class Timer1; // Nécessaire pour résoudre la dépendance circulaire.

extern Timer0 timer0;
extern Timer1 timer1;

class Timer;   // Nécessaire pour résoudre la dépendance circulaire.

typedef uint8_t EngineMode;
const EngineMode
    ENG_OFF = 0x04,
    ENG_FORWARD = 0x00,
    ENG_BACKWARD = 0x01;

typedef uint8_t TimerChannelUsed;
const TimerChannelUsed              // | ENABLE | DIRECTION |
    T0CA = 0,   // PWM utilisé = OC0A. |   PB3  |    PB2    |
    T0CB = 1,   // PWM utilisé = OC0B. |   PB4  |    PB5    |
    T1CA = 2,   // PWM utilisé = OC1A. |   PD5  |    PD3    |
    T1CB = 3/*, // PWM utilisé = OC1B. |   PD4  |    PD2    |
    T2CA = 4,   // PWM utilisé = OC2A. |   PD7  |    ???    |
    T2CB = 5*/; // PWM utilisé = OC2B. |   PD6  |    ???    |


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
