#ifndef LED_H
#define LED_H

#include "lib.h"
#include "timer.h"

class Timer;    // Nécessaire pour résoudre la dépendance circulaire.


typedef uint8_t LedColor;

/**
 * @brief Constantes pour la DEL.
 */
//const LedColor
#define    LED_OFF   0x00
#define    LED_GREEN 0x01
#define    LED_RED   0x02
#define    LED_AMBER 0xFF


class LED {
public:
    LED(PinPosition pinPos, Timer* timer);
    
    void setColor(volatile LedColor color);
    volatile LedColor getColor();
    
    PinPosition getPinPos();
    
    void setTimer(Timer* timer);
    Timer* getTimer();
    
private:
    void _setColorAmber();
    void _unsetColorAmber();
    
    Timer* _timer;
    const PinPosition _pinPos;
    volatile LedColor _color;
    
    const uint8_t _GREEN, _RED;
    const uint8_t _THIS_MASK;
    volatile uint8_t* const _PORT;
};

#endif // LED_H
