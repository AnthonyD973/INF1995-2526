/*
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

#include "ColorSnsr.h"

uint8_t ColorSnsr::_LED_MASK = 0;
const uint8_t ColorSnsr::_S0 = 2;
const uint8_t ColorSnsr::_S2 = 6;
Timer* ColorSnsr::_TIMER = nullptr;

const uint16_t ColorSnsr::_BLUE_THRESH  = 0x1680;
const uint16_t ColorSnsr::_GREEN_THRESH = 0x1B80;
const uint16_t ColorSnsr::_RED_THRESH   = 0x2500;


void ColorSnsr::init(TimerExternalClock tec) {
    switch (tec) {
     case T0_FALLING_EDGE: // fallthrough
     case T0_RISING_EDGE:  _LED_MASK = 0x2; _TIMER = &timer0; break;
     case T1_FALLING_EDGE: //fallthrough
     case T1_RISING_EDGE:  _LED_MASK = 0x1; _TIMER = &timer1; break;
     default: ;
    }
    
    _TIMER->setPrescale(tec & 0x0F);
    
    _MASK(PORTC, 0x3 << _S0 | COLOR_READ_WHITE << _S2, 0x3 << _S0 | 0x3 << _S2); // S1:0 = 2. Division d'horloge = 1:50 ; S3:2 = 1. Filtre Blanc.
}

ColorRead ColorSnsr::read() {
	_MASK(PORTB, 0xFF, _LED_MASK); // Allumer la LED.
    PORTD = 0x00;
    
    uint16_t intensity;
    _TIMER->setTcntN(0);
    _delay_ms(400.0); //FIXME Est-ce la bonne valeur?
    intensity = _TIMER->getTcntN();
    
    _MASK(PORTB, 0, _LED_MASK); // Éteindre la LED.
    
    UART::transmitCStr("INTENSITY: ");
    UART::transmitHex(intensity >> 8);
    UART::transmitHex(intensity);
    UART::transmit('\n');
    
    ColorRead ret;
    
    bool
        isBlue  = intensity <= _BLUE_THRESH,
        isGreen = intensity <= _GREEN_THRESH,
        isRed   = intensity <= _RED_THRESH;
    if (isBlue) {
        ret = COLOR_READ_BLUE;
    } else if (isGreen) {
        ret = COLOR_READ_GREEN;
    } else if (isRed) {
        ret = COLOR_READ_RED;
    } else {
        ret = COLOR_READ_WHITE;
    }
    
    return ret;
}
