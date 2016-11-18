#ifndef LIB_H
#define LIB_H 1

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart.h"

#define _MASK(reg, value, mask) (reg = ((reg) & ~(mask)) | ((value) & (mask))) // Change la valeur de certains bits d'un registre.
#define _MASKV(reg, value, mask) (((reg) & ~(mask)) | ((value) & (mask))) // Retourne la valeur d'un mask appliqué à certain bits

#define EVER (;;) // for EVER { ... }

/**
 * @brief Interrompt l'execution du programme pour un certain temps.
 * @param[in] t100us Temps à attendre (* 100 µs).
 */
void delay100MicroSeconds(const uint16_t& t100us);

/**
 * @brief Interrompt l'execution du programme pour un certain temps.
 * @param[in] t100us Temps à attendre (* 100 µs).
 */
void delay10MiliSeconds(const uint16_t& t10ms);

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
