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

const uint16_t ColorSnsr::_BLUE_THRESH  = 0x0680;
const uint16_t ColorSnsr::_GREEN_THRESH = 0x0800;
const uint16_t ColorSnsr::_RED_THRESH   = 0x1100;


void ColorSnsr::init(TimerExternalClock tec) {
    switch (tec) {
     case T0_FALLING_EDGE: // fallthrough
     case T0_RISING_EDGE:  _LED_MASK = 0x2; _TIMER = &timer0; break;
     case T1_FALLING_EDGE: //fallthrough
     case T1_RISING_EDGE:  _LED_MASK = 0x1; _TIMER = &timer1; break;
     default: ;
    }
    
    _TIMER->setPrescale(tec & 0x0F);
    
    _MASK(PORTC, 0x3 << _S0 | COLOR_READ_WHITE << _S2, 0x3 << _S0 | 0x3 << _S2); // S1:0 = 2. Division d'horloge = 1:1 ; S3:2 = 1. Filtre Blanc.
    
    _initializeConstants();
}

ColorRead ColorSnsr::read() {
	_MASK(PORTB, 0xFF, _LED_MASK); // Allumer la LED.
    
    
    ColorRead cf = COLOR_READ_RED;
    uint16_t colors[3];
    for (uint8_t i = 0; i < 3; ++i) {
        _MASK(PORTC, cf << _S2, 0x3 << _S2); // Envoyer le filtre de couleur au capteur
        _TIMER->setTcntN(0);
        _delay_ms(30.0); //FIXME Est-ce la bonne valeur?
        colors[i] = _TIMER->getTcntN();
        
        switch(cf) { // Passer à l'état (filtre) suivant
         case COLOR_READ_RED:   cf = COLOR_READ_GREEN; break;
         case COLOR_READ_GREEN: cf = COLOR_READ_BLUE; break;
         default: cf = COLOR_READ_WHITE; break;
        }
    }
    
    _MASK(PORTB, 0, _LED_MASK); // Éteindre la LED.
    
    UART::transmitCStr("RED: ");
    UART::transmitHex(colors[0] >> 8);
    UART::transmitHex(colors[0]);
    UART::transmit(' ');
    UART::transmitCStr("GREEN: ");
    UART::transmitHex(colors[1] >> 8);
    UART::transmitHex(colors[1]);
    UART::transmit(' ');
    UART::transmitCStr("BLUE: ");
    UART::transmitHex(colors[2] >> 8);
    UART::transmitHex(colors[2]);
    UART::transmit('\n');
    
    ColorRead ret;
    
    bool
        isRed =   colors[0] >= _RED_THRESH,
        isGreen = colors[1] >= _GREEN_THRESH,
        isBlue =  colors[2] >= _BLUE_THRESH;
    if (isRed && isGreen && isBlue) {
        ret = COLOR_READ_WHITE;
    } else if (colors[0] > (colors[1] + COLOR_INCERT) &&  // red > green + incert
                colors[0] > (colors[2] + COLOR_INCERT)) { // red > blue + incert
        ret = COLOR_READ_RED;
    } else if (colors[2] > (colors[1] + COLOR_INCERT)) {  // blue > green + incert
        ret = COLOR_READ_BLUE;
    } else {
        ret = COLOR_READ_GREEN;
    }
    
    switch(ret) {
     case COLOR_READ_RED:   UART::transmitCStr("RED  \n");
     case COLOR_READ_GREEN: UART::transmitCStr("GREEN\n");
     case COLOR_READ_BLUE:  UART::transmitCStr("BLUE \n");
     case COLOR_READ_WHITE: UART::transmitCStr("WHITE\n");
     default: UART::transmitCStr("???  \n");
    }
    
    return ret;
}

void _initialiseConstants() {
    _MASK(PORTB, 0xFF, _LED_MASK); // Allumer les LED
    _MASK(PORTC, COLOR_READ_RED << _S2, 0x3 << _S2); // On choisi le filtre Rouge
    _TIMER->setTcnt(0);
    _delay_ms(30.0);
    _RED_THRESH = (_TIMER->getTcnt() >> 2) * 3;
    _MASK(PORTC, COLOR_READ_GREEN << _S2, 0x3 << _S2);
    _TIMER->setTcnt(0);
    _delay_ms(30.0);
    _GREEN_THRESH = (_TIMER->getTcnt() >> 2) * 3;
    _MASK(PORTC, COLOR_READ_BLUE << _S2, 0x3 << _S2);
    _TIMER->setTcnt(0);
    _delay_ms(30.0);
    _BLUE_THRESH = (_TIMER->getTcnt() >> 2) * 3;
    _MASK(PORTB, 0x00, _LED_MASK);
}