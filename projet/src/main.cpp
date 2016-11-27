#include <lib.h>
#include <timer.h>
#include <led.h>
#include <buzzer.h>
#include <uart.h>

#include "LineSnsr.h"
#include "DistSnsr.h"
#include "ColorSnsr.h"
#include "ShapeDetector.h"
#include "ColorSequenceDetector.h"
#include "path.h"
#include "tests.h"

void globalInit(Engine& engL, Engine& engR) {
    // DDRA est modifié par LineSnsr::init.
    DDRB = 0xFD; // 1111 1101
    DDRC = 0xFF; // 1111 1111
    DDRD = 0xFF; // 1111 1111
    
    
    UART::init(2400);
    CAN::init();
    LineSnsr::init(&PORTA, &DDRA);
    DistSnsr::init(PA7);
    ColorSnsr::init(T1_RISING_EDGE);
    Path::init(&engL, &engR);
    Buzzer::init(&timer0);
}


int main() {
    Engine engL(T2CA);
    Engine engR(T2CB);
    LED led(C4_C5, nullptr);
    
    globalInit(engL, engR);
    
    ShapeColor shapeSequence[COLOR_SEQ_MAX];
    
	
    Path::doPath(0);
    shapeSequence[2] = testShapeDetector();
    Path::doPath(1);
    shapeSequence[1] = testShapeDetector();
    Path::doPath(1);
    shapeSequence[0] = testShapeDetector();
    Path::doPath(2);
    
    ColorSequenceDetector::checkSequence(shapeSequence, led);
    
    for EVER {
        // Busy wait
    }
    
    return 0;
}
