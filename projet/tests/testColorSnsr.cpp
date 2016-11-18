#include "tests.h"

void testColorSensor() {
    DDRA = 0;
    DDRB = 0xFD; // 11111101
    DDRC = DDRD = 0xFF;
    
    _MASK(PORTC, _BV(PC2) | _BV(PC4), _BV(PC2) | _BV(PC4)); // S1:0 = 3
    for EVER {
     
    }
}