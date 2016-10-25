#ifndef LIB_H
#define LIB_H 1

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart.h"

#define _MASK(reg, value, mask) (reg = ((reg) & ~(mask)) | ((value) & (mask)))

// inline void changeRegisterFromMask(volatile uint8_t& reg, uint8_t value, uint8_t mask) {
//   uint8_t notToChange = reg   & ~mask;
//   uint8_t changed     = value & mask;
//   reg = notToChange | changed;
// }
// 
// inline void changeRegisterFromMask(volatile uint16_t& reg, uint16_t value, uint16_t mask) {
//   uint16_t notToChange = reg   & ~mask;
//   uint16_t changed     = value & mask;
//   reg = notToChange | changed;
// }

/**
 * @brief Détection de fronts montants d'un port avec antirebond.
 *        Change previousPin si le front montant est détecté.
 * @param[in]     pin État du port.
 * @param[in,out] previousPin État précédent du port.
 * @return true si sur front montant, false sinon.
 */
bool risingEdge(const uint8_t& pin, uint8_t& previousPin);

/**
 * @brief Détection de fronts descendants d'un port avec antirebond.
 *        Change previousPin si le front descendant est détecté.
 * @param[in]     pin État du port.
 * @param[in,out] previousPin État précédent du port.
 * @return true si sur front descendant, false sinon.
 */
bool fallingEdge(const uint8_t& pin, uint8_t& previousPin);

/**
 * @brief Détection de fronts descendents d'un port avec antirebont.
 *        Change previousPin si un front est détecté.
 * @param[in]     pin État du port.
 * @param[in,out] previousPin État précédent du port.
 * @return true si sur front, false sinon.
 */
bool anyEdge(const uint8_t& pin, uint8_t& previousPin);

#endif // LIB_H
