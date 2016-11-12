#ifndef LIB_H
#define LIB_H

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "timer.h"
#include "drive.h"
#include "buzzer.h"
#include "ram.h"
#include "uart.h"

// +-------------------------+
// | SYMBOLES GLOBAUX DIVERS |
// +-------------------------+

#define _MASK(reg, value, mask) (reg = ((reg) & ~(mask)) | ((value) & (mask))) // Change la valeur de certains bits d'un registre.

#define EVER (;;) // for EVER { ... }

/**
 * @brief Initialise les classes entièrement statiques.
 */
__attribute__ ((always_inline))
inline void globalInit() {
    Drive::init();
    Buzzer::init();
    RAM::init();
    UART::init();
}

// +-----------------------------+
// | FONCTIONS UTILISABLES DANS  |
// | LES ROUTINES D'INTERRUPTION |
// +-----------------------------+

class Timer; // Déclaration nécessaire pour résoudre la dépendance circulaire.

/**
 * @brief Change la couleur des leds présentement ambres gérées par un compteur.
 *      NOTE: Cette fonction n'est utilisée nulle part dans les libraires ; c'est une fonction
 *      préécrite que l'on peut utiliser, par exemple dans les routines d'interruption.
 * @param[in] timer Compteur impliqué.
 */
void switchAmberLedsColor(Timer* timer);

// +------------------------+
// | GESTION DE PinPosition |
// +------------------------+
typedef uint8_t PinPosition;
//const PinPosition
#define    A0_A1 0
#define    A2_A3 2
#define    A4_A5 4
#define    A6_A7 6
#define    B0_B1 8
#define    B2_B3 10
#define    B4_B5 12
#define    B6_B7 14
#define    C0_C1 16
#define    C2_C3 18
#define    C4_C5 20
#define    C6_C7 22
#define    D0_D1 24
#define    D2_D3 26
#define    D4_D5 28
#define    D6_D7 30

/**
 * @brief   Détermine à quel port correspond une position.
 * @param[in] pinPos    Position sur les broches.
 * @return  Un pointeur vers le port correspondant à la position spécifiée.
 */
volatile uint8_t* getPortPtr(PinPosition pinPos);
/**
 * @brief   Détermine la valeur courante sur le port correspondant à une position.
 * @param[in] pinPos    Position sur les broches.
 * @return  La valeur présentement sur le port correspondant à la position spécifiée.
 */
uint8_t getPinVal(PinPosition pinPos);
/**
 * @brief   Détermine le numéro de broche correspondant à une position.
 * @param[in] pinPos    Position sur les broches.
 * @return  Le numéro de broche correspondant à une position. Ex : C4_C5 -> 4 ; D2_D3 -> 2.
 */
__attribute__ ((always_inline))
inline uint8_t getPinNumber(PinPosition pinPos) { return pinPos % 8; }
/**
 * @brief   Détermine le masque compatible avec la macro '_MASK'.
 * @param[in] pinPos    Position sur les broches.
 * @return  Masque compatible avec la macro '_MASK' Ex : _MASK(*port, val, getMask(D4_D5))
 */
__attribute__ ((always_inline))
inline uint8_t getMask(PinPosition pinPos) { return 0x3 << getPinNumber(pinPos); }

#endif // LIB_H