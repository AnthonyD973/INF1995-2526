#include "lib.h"
#include "uart.h"
#include "ram.h"
#include "led.h"

Timer0 timer0(P01_CLK8);
Timer1 timer1(P01_CLK8);

int main() {
    uint16_t size = 0;
    uint8_t  buffer = 0;
    
    DDRA = DDRB = DDRC = DDRD = 0xff;
    
    UART::init(2400);
    RAM::init();
    
    PORTB = LED_RED;
    
    UART::receive((uint8_t*)&size, 2);
    RAM::write(0, (uint8_t*)&size, 2);
    
    for (uint16_t i = 2; i < size; ++i) {
        buffer = UART::receive();
        RAM::write(i, buffer);
    }
    
    for EVER {
        PORTB = LED_GREEN;
    }
    
    return 0;
}
