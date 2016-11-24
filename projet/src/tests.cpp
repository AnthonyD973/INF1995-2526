#include "tests.h"

void testColorSensor() {
    for EVER {
        ColorRead curCR = ColorSnsr::read();
    }
}

void testDistSensor() {
    for EVER {
        uint16_t curDR = DistSnsr::readAverage();
        UART::transmitHex(curDR);
        UART::transmit('\n');
        _delay_ms(100.0);
    }
}

void testShapeDetector() {
    Shape shape = ShapeDetector::checkShape();
    
    switch (shape) {
     case CIRCLE_G:  _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); _delay_ms(1000.0); break;
     case OCTOGON_R: _MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5));   _delay_ms(1000.0); break;
     case SQUARE_B:  _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); _delay_ms(1000.0); _MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5)); _delay_ms(1000.0); break;
     default: ;
    }

    _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
}
