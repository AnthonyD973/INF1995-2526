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
Timer* ColorSnsr::_TIMER = nullptr;

void ColorSnsr::init(TimerExternalClock tec) {
    switch (tec) {
     case T0_FALLING_EDGE: // fallthrough
     case T0_RISING_EDGE:  _LED_MASK = 0x2; _TIMER = &timer0; break;
     case T1_FALLING_EDGE: //fallthrough
     case T1_RISING_EDGE:  _LED_MASK = 0x1; _TIMER = &timer1; break;
     default: ;
    }
    
    _TIMER->setPrescale(tec & 0x0F);
    
    _MASK(PORTC, 0x2 << _BV(PC2), _BV(PC2) | _BV(PC3)); // S1:0 = 2. Division d'horloge = 1:50
}

ColorFilter ColorSnsr::read() {
	_MASK(PORTB, 0xFF, _LED_MASK); // Allumer la LED.
    
    
    ColorFilter cf = FILTER_RED;
    uint8_t colors[3];
    for (uint8_t i = 0; i < 3; ++i) {
        _TIMER->setTcntN(0);
        _delay_ms(50.0); //FIXME Est-ce la bonne valeur?
        colors[i] = _TIMER->getTcntN();
        
        switch(cf) {
         case FILTER_RED:   cf = FILTER_GREEN;
         case FILTER_GREEN: cf = FILTER_BLUE;
         default: cf = FILTER_CLEAR;
        }
    }
    
    _MASK(PORTB, 0, _LED_MASK); // Éteindre la LED.
    
    ColorFilter ret;
    
    if () { // ROUGE ?
        ret = FILTER_RED;
    } else if () { // VERT ?
        ret = FILTER_GREEN;
    } else if () { // BLEU ?
        ret = FILTER_BLUE;
    } else {
        ret = FILTER_CLEAR;
    }
    
    return ret;
}
