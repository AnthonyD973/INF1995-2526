#include "LineSnsr.h"

volatile uint8_t* LineSnsr::_PIN = &PINA;

void LineSnsr::init(volatile uint8_t* pin, volatile uint8_t* port, volatile uint8_t* ddr) {
    _PIN = pin;
    *ddr &= ~(_BV(0) | _BV(1) | _BV(2) | _BV(3) | _BV(4)); // Les sorties du capteur sont en entrée du microcontrôleur.
    *ddr |= _BV(5);  // Bit de calibration
    *port |= _BV(5); // Bit de calibration (actif bas) désactivé.
}

uint8_t LineSnsr::read() { 
    return *_PIN & 0x1F;
    
}
