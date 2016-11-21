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

void DistSnsr::init(PinAPos pinANum) {
    _PIN_A_NUM = pinANum;
}

uint8_t DistSnsr::read() {
    uint8_t valueRead = (uint8_t)CAN::read(_PIN_A_NUM);
    UART::transmitHex(valueRead);
    UART::transmit(' ');
    return valueRead;
}