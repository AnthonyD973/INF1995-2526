#include "lib.h"
#include "uart.h"
#include "ram.h"
#include "led.h"

Timer0 timer0(P01_CLK8);
Timer1 timer1(P01_CLK8);

int main() {
    uint16_t size = 0;
    uint8_t  buffer = 0;
    
    DDRA = DDRB = DDRC = 0xff;
    
    UART::init(2400);
    RAM::init();
    
    PORTB = LED_RED;
    
    for (uint8_t i = 0; i < 2; ++i) {
        buffer = UART::receive();
        size += (buffer << (8*(1-i)));
    }
    
    RAM::write(0, (uint8_t*)&size, 2);
    
    PORTB = LED_GREEN;
    
    for (uint16_t i = 2; i < size; ++i) {
        PORTB = LED_RED;
        buffer = UART::receive();
        PORTB = LED_GREEN;
        RAM::write(i, buffer);
    }
    
    for EVER {
        PORTB = LED_OFF;
    }
    
    return 0;
}
