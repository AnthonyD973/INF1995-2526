#include "drive.h"

Timer0 timer0(P01_CLK8);
Timer1 timer1(P01_CLK8);

int main() {
    DDRA = DDRB = DDRC = DDRD = 0xFF;
    
    UART::init(2400);
    Drive::init(T0CA, T0CB, 127, 255);
    
    LED led(B0_B1, &timer0);
    led.setColor(LED_GREEN);
    /*
    Engine engL(T0CA);
    Engine engR(T0CB);
    
    engL.setMode(ENG_FORWARD);/*/
    
    
    Drive::setMovement(ENG_FORWARD, 0xFF);//*/
    
    for EVER {
        // Busy-wait
    }
    
    return 0;
}
