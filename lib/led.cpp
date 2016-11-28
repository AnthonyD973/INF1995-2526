/*
 * Classe permettant l'utilisation d'une LED.
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Emir Khaled Belhaddad, Anthony Dentinger,
 * Gergi Younis et Vincent Dandenault
 * 2016
 *
 * Code qui n'est sous aucune license.
 *
 */

#include "led.h"

// ===============================
// =   GESTION DE LED_POSITION   =
// ===============================

volatile uint8_t* getPortPtr(LedPosition ledPos) {
    switch (ledPos / 8) {
        case 0:  return &PORTA; break;
        case 1:  return &PORTB; break;
        case 2:  return &PORTC; break;
        default: return &PORTD; break;
    }
}

uint8_t getPinVal(LedPosition ledPos) {
    switch (ledPos / 8) {
        case 0:  return PINA; break;
        case 1:  return PINB; break;
        case 2:  return PINC; break;
        default: return PIND; break;
    }
}

__attribute__ ((always_inline))
inline uint8_t getPinNumber(LedPosition ledPos) { return ledPos & 0x07; }

__attribute__ ((always_inline))
inline uint8_t getMask(LedPosition ledPos) { return 0x3 << getPinNumber(ledPos); }

__attribute__ ((always_inline))
inline uint16_t getShiftedPos(LedPosition ledPos) { return 1 << (ledPos/2); }

// ===============================
// =   GESTION DES LED AMBRES    =
// ===============================

void switchAmberLedsColor(Timer* timer) {
    // Test fréquemment vrai, alors effectué au début.
    if (timer->_nAmberLeds == 0) {
        return;
    }
    
    // Changer la couleur des LED actuellement ambres.
    uint16_t curAmberLeds  = timer->_amberLeds;
    uint8_t nAmberLedsLeft = timer->_nAmberLeds;
    volatile uint8_t* curPort;
    for (LedPosition portBeginNum = 0; portBeginNum < 32 && nAmberLedsLeft != 0; portBeginNum += 8) {
        curPort = getPortPtr(portBeginNum);
        uint8_t amberLedsMask = 0;
        
        for (uint8_t pinNumberDivBy2 = 0; pinNumberDivBy2 < 4 && nAmberLedsLeft != 0; ++pinNumberDivBy2) {
            bool isThisLedAmber = (curAmberLeds & 1) == 1;
            if (isThisLedAmber) {
                --nAmberLedsLeft;
                amberLedsMask |= getMask(portBeginNum + 2*pinNumberDivBy2);
            }
            curAmberLeds >>= 1;
        }
        
        _MASK(*curPort, ~(*curPort), amberLedsMask);
    }
}

// ===============
// =     LED     =
// ===============

// PUBLIC:

LED::LED(LedPosition ledPos, Timer* timer)
    : _timer(timer),
      _ledPos(ledPos),
      _GREEN(LED_GREEN << getPinNumber(ledPos)),
      _RED(LED_RED << getPinNumber(ledPos)),
      _THIS_MASK(getMask(ledPos)),
      _PORT(getPortPtr(ledPos))
{ }


void LED::setColor(LedColor color) {
    if (_color == LED_AMBER) {
        _unsetColorAmber();
    }
    
    switch(color) {
        case LED_GREEN: _MASK(*_PORT, _GREEN, _THIS_MASK); break;
        case LED_RED:   _MASK(*_PORT,   _RED, _THIS_MASK); break;
        case LED_AMBER: _setColorAmber(); break;
        case LED_OFF:   // fallthrough
        default:        _MASK(*_PORT,   0x00, _THIS_MASK); break;
    }
    
    _color = color;
}

LedColor LED::getColor() {
    return _color;
}


LedPosition LED::getLedPos() {
    return _ledPos;
}


void LED::setTimer(Timer* timer) {
    if (_color == LED_AMBER) {
        _unsetColorAmber();
        _timer = timer;
        _setColorAmber();
        return;
    }
    _timer = timer;
    return;
}

Timer* LED::getTimer() {
    return _timer;
}

// PRIVATE:

void LED::_setColorAmber() {
    ++(_timer->_nAmberLeds);
    _MASK(*_PORT, _GREEN, _THIS_MASK);
    _MASK(_timer->_amberLeds, getShiftedPos(_ledPos), getShiftedPos(_ledPos));
}

void LED::_unsetColorAmber()  {
    --(_timer->_nAmberLeds);
    _MASK(*_PORT,  0x00,  _THIS_MASK);
    _MASK(_timer->_amberLeds, 0x0, getShiftedPos(_ledPos));
}
