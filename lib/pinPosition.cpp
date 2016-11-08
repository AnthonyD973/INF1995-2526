#include "pinPosition.h"

volatile uint8_t* getPortPtr(PinPosition pinPos) {
    switch (pinPos / 8) {
        case 0:  return &PORTA; break;
        case 1:  return &PORTB; break;
        case 2:  return &PORTB; break;
        default: return &PORTD; break;
    }
}

volatile uint8_t getPinVal(PinPosition pinPos) {
    switch (pinPos / 8) {
        case 0:  return PINA; break;
        case 1:  return PINB; break;
        case 2:  return PINB; break;
        default: return PIND; break;
    }
}
