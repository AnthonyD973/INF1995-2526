#include <lib.h>
#include <timer.h>
#include <buzzer.h>
#include <uart.h>
#include "path.h"


void testColorSensor() {
    DDRA = 0;
    DDRB = 0xFD; // 11111101
    DDRC = DDRD = 0xFF;
    
    _MASK(PORTC, _BV(PC3) | _BV(PC2), _BV(PC3) | _BV(PC2)); // S1:0 = 3 (division d'horloge par 1)
    _MASK(PORTB, _BV(PB6) | _BV(PB0), _BV(PB7) | _BV(PB6) | _BV(PB0)); // S3:2 = 2 (clear filter) et LED = 1
    
    timer1.setPrescale(P01_EXT_CLK_RISING_EDGE);
    
    for EVER {
     
        for (unsigned int i = 0; i < 50; ++i) {
                timer1.setTcntN(0);
            for (unsigned int j = 0; j < i; ++j) {
                _delay_us(100.0);
            }
            uint16_t numEdges = timer1.getTcntN();
            UART::transmitHex(numEdges);
        }
        
    }
}

void readShape() {
    Path::turn(ROT_RIGHT);
    _delay_ms(500.0);
    while (!(LineSnsr::read() & 0x08));
    Path::stop();
}

int main() {
    Engine engL(T0CA);
    Engine engR(T0CB);
    
    UART::init(2400);
    LineSnsr::init(&PINA, &PORTA, &DDRA);
    Path::init(&engL, &engR);
    
    Path::doPath(0);
    readShape();
    Path::doPath(1);
    readShape();
    Path::doPath(1);
    readShape();
    Path::doPath(2);
    
    return 0;
}
