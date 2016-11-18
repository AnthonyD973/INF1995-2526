/*
 * Ecole Polytechnique de Montreal
 * Département de Génie informatique
 * Cours INF1995
 *
 * Emir Khaled Belhaddad, Anthony Dentinger,
 * Gergi Younis et Vincent Dandenault
 * 2016
 *
 * Code qui n'est sous aucune license.
 *
 */

#include "LineSnsr.h"

void LineSnsr::init(volatile uint8_t* pin, volatile uint8_t* port, volatile uint8_t* ddr) {
    _PIN = pin; // choix des pins pour recevoir les sorties du capteur
    *ddr &= ~(_BV(0) | _BV(1) | _BV(2) | _BV(3) | _BV(4)); // port configuré en entrée pour recevoir les sorties du capteur sur les broches 1 à 5
    *ddr |= _BV(5);  // port configuré en sortie et broche 6 mise à 1 pour ne pas se mettre en mode calibration
    *port |= _BV(5); // 
}

uint8_t LineSnsr::read() { 
    return *_PIN & 0x1F; // lecture de la sortie du capteur sur les cinq bits les moins significatifs 
    
}
