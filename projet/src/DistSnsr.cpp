/*
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Emir Khaled Belhaddad, Anthony Dentinger,
 * Gergi Younis et Vincent Dandenault
 * 2016
 *
 * Code qui n'est sous aucune license.
 *
 */

#include "DistSnsr.h"

PinAPos DistSnsr::_PIN_A_NUM = 0xFF;

//TODO Le Potentiomètre doit être réglé à 2.65 V.
void DistSnsr::init(PinAPos pinANum) {
    _PIN_A_NUM = pinANum;
}

uint16_t DistSnsr::read() {
    uint16_t val = 0x3FF & CAN::read(_PIN_A_NUM);
    // La constante 26.5 a été calculée à partir du graphique de la Figure 5 de
    // la documentation.
    // La constante 2.65 est le potentiel maximal que peut fournir le capteur
    // (correspondant, à peu près, à 10±1cm).
    
    // Calculs :
    
    // L = (26.5)/(Vin) - 0.42
    // L = (26.5)/(2.65*(val/1024)) - 0.42
    // L = (26.5/2.65*1024)/val -0.42
    // L = (10*1024)/val - 0.42
    
    // out = (L) * 256 / (MAX - MIN + 1) - 1
    // out = ((10240)/val -0.42) *256 / (71) -1
    // out = ((10*2^18) / val - 107.52) / (71) -1
    // out = ((10*2^18/71) / val - 1.51) -1
    // out = (36921.69)/(val) - 2.51
    return (36922/val)-3;
}