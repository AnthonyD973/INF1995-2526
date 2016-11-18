#include "tests.h"

void testColorSensor() {
    DDRA = 0;
    DDRB = 0xFD; // 11111101
    DDRC = DDRD = 0xFF;
    
    _MASK(PORTC, _BV(PC3) | _BV(PC2), _BV(PC3) | _BV(PC2)); // S1:0 = 3 (division d'horloge par 1)
    _MASK(PORTB, _BV(PB6) | _BV(PB0), _BV(PB7) | _BV(PB6) | _BV(PB0)); // S3:2 = 2 (clear filter) et LED = 1
    
    timer1.setPrescale(P01_EXT_CLK_RISING_EDGE);
    
    for EVER {
     
        for (unsigned int i = 0; i < 255; ++i) {
                timer1.setTcntN(0);
            for (unsigned int j = 0; j < i; ++j) {
                _delay_ms(1.0);
            }
            uint16_t numEdges = timer1.getTcntN();
            UART::transmitHex(numEdges);
        }
        
    }
}