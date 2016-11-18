#include "tests.h"

void testColorSensor() {
    DDRA = 0;
    DDRB = 0xFD; // 11111101
    DDRC = DDRD = 0xFF;
    
    _MASK(PORTC, _BV(PC3) | _BV(PC2), _BV(PC3) | _BV(PC2)); // S1:0 = 3 (division d'horloge par 1)
    _MASK(PORTB,  _BV(PB6) | _BV(PB0), _BV(PB7) | _BV(PB6) | _BV(PB0)); // S3:2 = 2 (clear filter) et LED = 1
    for EVER {
        _delay_ms(500.0);
        _MASK(PORTB, _BV(PB0), _BV(PB0)); // LED = 1
        _delay_ms(500.0);
        _MASK(PORTB, 0, _BV(PB0));
    }
}