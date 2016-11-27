#include "LineSnsr.h"

volatile uint8_t* LineSnsr::_PORT = nullptr;

void LineSnsr::init(volatile uint8_t* port, volatile uint8_t* ddr) {
    *ddr  &= ~LINE_BITS_MASK; // Les sorties du capteur sont en entrée du microcontrôleur.
    *ddr  |= _BV(5); // Bit de calibration
    *port |= _BV(5); // Bit de calibration (actif bas) désactivé.
    _PORT  = port;
}

uint8_t LineSnsr::read() { 
    return (*_PORT) & LINE_BITS_MASK;
}
