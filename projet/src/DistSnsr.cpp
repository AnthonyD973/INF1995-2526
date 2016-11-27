#include "DistSnsr.h"

uint8_t DistSnsr::_PIN_A_NUM = 0xFF;

// NOTE: Le Potentiomètre doit être réglé à 2.65 V.
void DistSnsr::init(uint8_t pinANum) {
    _PIN_A_NUM = pinANum;
}

uint8_t DistSnsr::read() {
    uint16_t val = 0xFF & (CAN::read(_PIN_A_NUM) >> 2);
    // La constante 26.5 a été calculée à partir du graphique de la Figure 5 de
    // la documentation.
    // La constante 2.65 est le potentiel maximal que peut fournir le capteur
    // (correspondant, à peu près, à 10±1cm).
    
    // Calculs :
    
    // L = (26.5)/(Vin) - 0.42
    // L = (26.5)/(2.65*(val/256)) - 0.42
    // L = (26.5/2.65*256)/val -0.42
    // L = (10*256)/val - 0.42
    
    // out = (L) * 256 / (MAX - MIN + 1) - 1
    // out = ((2560)/val -0.42) *256 / (71) -1
    // out = ((10*2^16) / val - 107.52) / (71) -1
    // out = ((10*2^16/71) / val - 1.51) -1
    // out = (9230.42)/(val) - 2.51
    return (9230/val)-3;
}

uint8_t DistSnsr::readAverage() {
    static const uint8_t nReads = 32;
    
    uint16_t sum = 0;
    for (uint8_t i = 0; i < nReads; ++i) {
        sum += read();
    }
    
    return sum/nReads;
}
