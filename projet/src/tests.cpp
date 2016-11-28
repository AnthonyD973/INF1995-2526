#include "tests.h"

void testColorSensor() {
    for EVER {
        ShapeColor curCR = ColorSnsr::read();
        switch(curCR) {
        case OCTOGON_RED:    _MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5)); break;
        case CIRCLE_GREEN:   _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); break;
        case SQUARE_BLUE:    if((PORTC & 0x30) == 0x30 || (PORTC & 0x30) == 0x00) _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); _MASK(PORTC, ~PORTC, _BV(PC4) | _BV(PC5)); break;
        case NO_SHAPE_WHITE: _MASK(PORTC, 0, _BV(PC4) | _BV(PC5)); break;
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

void testBuzzer() {
	const float delayValue = 150.0;
	
	Buzzer::setTone(67);
	_delay_ms(delayValue);
	Buzzer::setTone(66);
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
	_delay_ms(delayValue);
	
	Buzzer::clearTone();
	for EVER {
	    // Busy-wait
	}
}
