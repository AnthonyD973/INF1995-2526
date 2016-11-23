#include <lib.h>
#include <timer.h>
#include <led.h>
#include <buzzer.h>
#include <uart.h>

#include "LineSnsr.h"
#include "DistSnsr.h"
#include "ColorSnsr.h"
#include "path.h"
#include "ShapeDetector.h"

void globalInit(Engine& engL, Engine& engR) {
    DDRB = 0xFD; // 1111 1101
    DDRC = 0xFF; // 1111 1111
    DDRD = 0xFF; // 1111 1111
    
    
    UART::init(2400);
    CAN::init();
    LineSnsr::init(&PINA, &PORTA, &DDRA);
    DistSnsr::init(PA7);
    ColorSnsr::init(T1_RISING_EDGE);
    Path::init(&engL, &engR);
    Buzzer::init(&timer0);
}


void testColorSensor() {
    for EVER {
        ColorRead curCR = ColorSnsr::read();
    }
}

void testDistSensor() {
    for EVER {
        uint16_t curDR = DistSnsr::read();
        UART::transmitHex(curDR);
        UART::transmit(' ');
        _delay_ms(1000.0);
    }
}

void testShapeDetector(LED& led) {
    Shape shape = ShapeDetector::checkShape();
    
    switch (shape) {
     case CIRCLE_G:  _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); _delay_ms(1000.0); break;
     case OCTOGON_R: _MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5));   _delay_ms(1000.0); break;
     case SQUARE_B:  _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); _delay_ms(1000.0); _MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5)); _delay_ms(1000.0); break;
     default: ;
    }
    _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
}

int main() {
    Engine engL(T2CA);
    Engine engR(T2CB);
    
    LED led(C4_C5, &timer0);
    
    globalInit(engL, engR);
    
    Path::doPath(0);
    testShapeDetector(led);
    /**/Path::doPath(1);
    testShapeDetector(led);
    Path::doPath(1);
    testShapeDetector(led);
    Path::doPath(2);//*/
    
    /*
    Path::doPath(0);
    readShape();
    Path::doPath(1);
    readShape();
    Path::doPath(1);
    readShape();
    Path::doPath(2);*/
    
    return 0;
}
