#include <lib.h>
#include <timer.h>
#include <led.h>
#include <buzzer.h>
#include <uart.h>

#include "LineSnsr.h"
#include "DistSnsr.h"
#include "ColorSnsr.h"
#include "ShapeDetector.h"
#include "path.h"
#include "tests.h"

void globalInit(Engine& engL, Engine& engR) {
	// DDRA est modifié par LineSnsr::init.
    DDRB = 0xFD; // 1111 1101
    DDRC = 0xFF; // 1111 1111
    DDRD = 0xFF; // 1111 1111
    
    
    UART::init(2400);
    CAN::init();
    LineSnsr::init(&PINA, &PORTA, &DDRA);
    DistSnsr::init(PA7);
    ColorSnsr::init(T1_RISING_EDGE);
    Path::init(&engL, &engR);
    Buzzer::init(&timer1);
}


int main() {
    Engine engL(T2CA);
    Engine engR(T2CB);
    
    
    globalInit(engL, engR);
	
	testBuzzer();
	
    /*/
    Path::doPath(0);
    testShapeDetector();
    Path::doPath(1);
    testShapeDetector();
    Path::doPath(1);
    testShapeDetector();
    Path::doPath(2);//*/
    
    return 0;
}
