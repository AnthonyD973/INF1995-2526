#include "lib.h"
#include "uart.h"
#include "ram.h"
#include "led.h"

int main() {
    uint16_t size = 0;
    uint8_t  buffer = 0;
    
    DDRC = 0x30;
    DDRD = 0x02;
    
    UART::init(2400);
    RAM::init();
    
    PORTC = LED_RED << 4;
    
    for (uint8_t i = 0; i < 2; ++i) {
        buffer = UART::receive();
        size += (buffer << (8*(i)));
    }
    
    RAM::write(0, (uint8_t*)&size, 2);
    
    PORTC = LED_GREEN << 4;
    
    for (uint16_t i = 2; i < size; ++i) {
        PORTC = LED_RED << 4;
        buffer = UART::receive();
        PORTC = LED_GREEN << 4;
        RAM::write(i, buffer);
    }
    
    for EVER {
        PORTC = LED_OFF << 4;
    }
    
    return 0;
}
