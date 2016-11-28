#include "ColorSnsr.h"

uint8_t ColorSnsr::_LED_MASK = 0;
const uint8_t ColorSnsr::_S0 = 2;
const uint8_t ColorSnsr::_S2 = 6;
Timer* ColorSnsr::_TIMER = nullptr;

const uint16_t ColorSnsr::_COLOR_UNCERT = 0x30; // ± 48
                                                       // ---RED  -GREEN  --BLUE
uint16_t ColorSnsr::_THRESHES_FOR_WHITE[COLOR_SEQ_MAX] = {0x1100, 0x0800, 0x0680};


struct EqualFunctor      { void operator()(uint16_t& lhs, uint16_t rhs) { lhs  = rhs; } };
struct MinusEqualFunctor { void operator()(uint16_t& lhs, uint16_t rhs) { lhs -= rhs; } };

// ====================
// =    COLOR_SNSR    =
// ====================

// PUBLIC

void ColorSnsr::init(TimerExternalClock tec) {
    switch (tec) {
     case T0_FALLING_EDGE: // fallthrough
     case T0_RISING_EDGE:  _LED_MASK = 0x2; _TIMER = &timer0; break;
     case T1_FALLING_EDGE: //fallthrough
     case T1_RISING_EDGE:  _LED_MASK = 0x1; _TIMER = &timer1; break;
     default: ;
    }
    
    _TIMER->setPrescale(tec & 0x0F);
    
    _MASK(PORTC, 0x3 << _S0, 0x3 << _S0); // Division d'horloge = 1:1
    
    _initializeConstants();
}

ShapeColor ColorSnsr::read() {
    uint16_t colorsIntesity[COLOR_SEQ_MAX];
    
    // Prendre une mesure avec la LED allumée...
    _MASK(PORTB, 0xFF, _LED_MASK);
    _readColors<EqualFunctor>(colorsIntesity);
    
    // ...une mesure sans, et faire la différence entre les deux pour annuler
    // l'effet de la lumière ambiante.
    _MASK(PORTB, 0, _LED_MASK);
    _readColors<MinusEqualFunctor>(colorsIntesity);
    
    return _decideWhichColor(colorsIntesity);
}

// PRIVATE

void ColorSnsr::_initializeConstants() {
    // Prendre une mesure avec la LED allumée...
    _MASK(PORTB, 0xFF, _LED_MASK);
    _readColors<EqualFunctor>(_THRESHES_FOR_WHITE);
    
    // ...une mesure sans, et faire la différence entre les deux pour annuler
    // l'effet de la lumière ambiante.
    _MASK(PORTB, 0x00, _LED_MASK);
    _readColors<MinusEqualFunctor>(_THRESHES_FOR_WHITE);
}

template <class Operator>
void ColorSnsr::_readColors(uint16_t colorsIntensity[COLOR_SEQ_MAX]) {
    Operator op;
    
    ShapeColor colorFilter = OCTOGON_RED;
    
    for (uint8_t i = 0; i < COLOR_SEQ_MAX; ++i) {
        _MASK(PORTC, colorFilter << _S2, 0x3 << _S2); // Envoyer le filtre de couleur au capteur
        _TIMER->setTcntN(0);
        _delay_ms(15.0);
        
        op(colorsIntensity[i], _TIMER->getTcntN());
        
        switch(colorFilter) { // Passer à l'état (filtre) suivant
         case OCTOGON_RED:  colorFilter = CIRCLE_GREEN; break;
         case CIRCLE_GREEN: colorFilter = SQUARE_BLUE; break;
         default: ;
        }
    }
}

ShapeColor ColorSnsr::_decideWhichColor(uint16_t colorsIntensity[COLOR_SEQ_MAX]) {
    ShapeColor colorRead;
    
    bool
        isRedForWhite   = colorsIntensity[RED_INDEX]   >= _THRESHES_FOR_WHITE[RED_INDEX],
        isGreenForWhite = colorsIntensity[GREEN_INDEX] >= _THRESHES_FOR_WHITE[GREEN_INDEX],
        isBlueForWhite  = colorsIntensity[BLUE_INDEX]  >= _THRESHES_FOR_WHITE[BLUE_INDEX];
    if (isRedForWhite && isGreenForWhite && isBlueForWhite) {
        colorRead = NO_SHAPE_WHITE;
    } else if (colorsIntensity[RED_INDEX]  > (colorsIntensity[GREEN_INDEX] + _COLOR_UNCERT) &&
               colorsIntensity[RED_INDEX]  > (colorsIntensity[BLUE_INDEX]  + _COLOR_UNCERT)) {
        colorRead = OCTOGON_RED;
    } else if (colorsIntensity[BLUE_INDEX] > (colorsIntensity[GREEN_INDEX] + _COLOR_UNCERT)) {
        colorRead = SQUARE_BLUE;
    } else {
        colorRead = CIRCLE_GREEN;
    }
    
    return colorRead;
}