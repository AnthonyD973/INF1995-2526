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

const uint16_t ColorSnsr::COLOR_UNCERT = 0x30; // ± 48

uint16_t ColorSnsr::_BLUE_THRESH_FOR_WHITE  = 0x0680;
uint16_t ColorSnsr::_GREEN_THRESH_FOR_WHITE = 0x0800;
uint16_t ColorSnsr::_RED_THRESH_FOR_WHITE   = 0x1100;


class EqualFunctor { void operator()(uint16_t& lhs, uint16_t rhs) { lhs = rhs; } };
class MinusEqualFunctor { void operator()(uint16_t& lhs, uint16_t rhs) { lhs -= rhs; } };


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
    ColorRead colorFilter = COLOR_READ_RED;
    uint16_t colors[COLOR_SEQ_MAX];
    
    // Prendre une mesure avec la LED allumée...
    _MASK(PORTB, 0xFF, _LED_MASK);
    _readColors<EqualFunctor>(colors);
    
    // ...une mesure sans, et faire la différence entre les deux pour annuler
    // l'effet de la lumière ambiante.
    _MASK(PORTB, 0, _LED_MASK);
    _readColors<MinusEqualFunctor>(colors);
    
    ColorRead colorRead;
    
    bool
        isRed =   colors[0] >= _RED_THRESH_FOR_WHITE,
        isGreen = colors[1] >= _GREEN_THRESH_FOR_WHITE,
        isBlue =  colors[2] >= _BLUE_THRESH_FOR_WHITE;
    if (isRed && isGreen && isBlue) {
        colorRead = COLOR_READ_WHITE;
    } else if (colors[0] > (colors[1] + COLOR_UNCERT) &&  // red > green + incert
                colors[0] > (colors[2] + COLOR_UNCERT)) { // red > blue + incert
        colorRead = COLOR_READ_RED;
    } else if (colors[2] > (colors[1] + COLOR_UNCERT)) {  // blue > green + incert
        colorRead = COLOR_READ_BLUE;
    } else {
        colorRead = COLOR_READ_GREEN;
    }
    
    /*switch(ret) {
     case COLOR_READ_RED:   UART::transmitCStr(" RED  \n"); break;
     case COLOR_READ_GREEN: UART::transmitCStr(" GREEN\n"); break;
     case COLOR_READ_BLUE:  UART::transmitCStr(" BLUE \n"); break;
     case COLOR_READ_WHITE: UART::transmitCStr(" WHITE\n"); break;
     default: UART::transmitCStr(" ??? \n");
    }*/
    
    return colorRead;
}

void ColorSnsr::_initializeConstants() {
    // On soustrait les valeur prise avec les LEDs des valeurs prise à la
    // lumière ambiante. Selon la documentation, cela permet d'accroitre la
    // précision des mesures 

    _MASK(PORTB, 0xFF, _LED_MASK); // Allumer les LED
    
    _MASK(PORTC, COLOR_READ_RED << _S2, 0x3 << _S2); // On choisi le filtre Rouge
    _TIMER->setTcntN(0);
    _delay_ms(15.0);
    _RED_THRESH_FOR_WHITE = (_TIMER->getTcntN() >> 2) * 3;
    _MASK(PORTC, COLOR_READ_GREEN << _S2, 0x3 << _S2);
    _TIMER->setTcntN(0);
    _delay_ms(15.0);
    _GREEN_THRESH_FOR_WHITE = (_TIMER->getTcntN() >> 2) * 3;
    _MASK(PORTC, COLOR_READ_BLUE << _S2, 0x3 << _S2);
    _TIMER->setTcntN(0);
    _delay_ms(15.0);
    _BLUE_THRESH_FOR_WHITE = (_TIMER->getTcntN() >> 2) * 3;
    
    _MASK(PORTB, 0x00, _LED_MASK); // Éteindre les LED
    
    _MASK(PORTC, COLOR_READ_RED << _S2, 0x3 << _S2); // On choisi le filtre Rouge
    _TIMER->setTcntN(0);
    _delay_ms(15.0);
    _RED_THRESH_FOR_WHITE -= (_TIMER->getTcntN() >> 2) * 3;
    _MASK(PORTC, COLOR_READ_GREEN << _S2, 0x3 << _S2);
    _TIMER->setTcntN(0);
    _delay_ms(15.0);
    _GREEN_THRESH_FOR_WHITE -= (_TIMER->getTcntN() >> 2) * 3;
    _MASK(PORTC, COLOR_READ_BLUE << _S2, 0x3 << _S2);
    _TIMER->setTcntN(0);
    _delay_ms(15.0);
    _BLUE_THRESH_FOR_WHITE -= (_TIMER->getTcntN() >> 2) * 3;
    
    UART::transmitCStr("[Initialisation] ");
    UART::transmitCStr("RED: ");
    UART::transmitHex(_RED_THRESH_FOR_WHITE >> 8);
    UART::transmitHex(_RED_THRESH_FOR_WHITE);
    UART::transmitCStr(" GREEN: ");
    UART::transmitHex(_GREEN_THRESH_FOR_WHITE >> 8);
    UART::transmitHex(_GREEN_THRESH_FOR_WHITE);
    UART::transmitCStr(" BLUE: ");
    UART::transmitHex(_BLUE_THRESH_FOR_WHITE >> 8);
    UART::transmitHex(_BLUE_THRESH_FOR_WHITE);
    UART::transmit('\n');
}

template <class Operator>
void ColorSnsr::_readColors(uint16_t colors[COLOR_SEQ_MAX]) {
    Operator op;
    
    ColorRead colorFilter = COLOR_READ_RED;
    
    for (uint8_t i = 0; i < COLOR_SEQ_MAX; ++i) {
        _MASK(PORTC, colorFilter << _S2, 0x3 << _S2); // Envoyer le filtre de couleur au capteur
        _TIMER->setTcntN(0);
        _delay_ms(15.0);
        
        op(colors[i], _TIMER->getTcntN());
        
        switch(colorFilter) { // Passer à l'état (filtre) suivant
         case COLOR_READ_RED:   colorFilter = COLOR_READ_GREEN; break;
         case COLOR_READ_GREEN: colorFilter = COLOR_READ_BLUE; break;
         default: colorFilter = COLOR_READ_WHITE; break;
        }
    }
}