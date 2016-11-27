#include "tests.h"

void testColorSensor() {
    for EVER {
        ColorRead curCR = ColorSnsr::read();
        switch(curCR) {
        case COLOR_READ_RED:   _MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5)); break;
        case COLOR_READ_GREEN: _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); break;
        case COLOR_READ_BLUE:  if((PORTC & 0x30) == 0x30 || (PORTC & 0x30) == 0x00) _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); _MASK(PORTC, ~PORTC, _BV(PC4) | _BV(PC5)); break;
        case COLOR_READ_WHITE: _MASK(PORTC, 0, _BV(PC4) | _BV(PC5)); break;
        default: _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
        }
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

Shape testShapeDetector() {
    Shape shape = ShapeDetector::checkShape();
    Buzzer::clearTone();
    _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
    
    switch (shape) {
     case CIRCLE_G:  _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); _delay_ms(1000.0); break;
     case OCTOGON_R: _MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5)); _delay_ms(1000.0); break;
     case SQUARE_B:  Buzzer::setTone(68); _delay_ms(1000.0); break;
     default: ;
    }

    Buzzer::clearTone();
    _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
    
    return shape;
}

void testBuzzer() {
	const float delayValue = 150.0;
	
	Buzzer::setTone(67);
	_delay_ms(delayValue);
	/**/Buzzer::setTone(66);
	_delay_ms(delayValue);
	Buzzer::setTone(63);
	_delay_ms(delayValue);
	Buzzer::setTone(57);
	_delay_ms(delayValue);
	Buzzer::setTone(56);
	_delay_ms(delayValue);
	Buzzer::setTone(64);
	_delay_ms(delayValue);
	Buzzer::setTone(68);
	_delay_ms(delayValue);
	Buzzer::setTone(72);
	_delay_ms(delayValue);//*/
	
	Buzzer::clearTone();
	for EVER {
	    Buzzer::clearTone();
	}
}
