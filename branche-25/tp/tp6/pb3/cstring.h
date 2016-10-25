#ifndef CSTRING_H
#define CSTRING_H

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef uint16_t size_t;

/**
 * @brief Compare deux chaînes C.
 * @param[in] str1 Chaîne à comparer.
 * @param[in] str2 Chaîne à comparer.
 * @return true si le test est concluant.
 */
bool strcmp(uint8_t* str1, uint8_t* str2);

/**
 * @brief Détermine la longueur d'une chaîne C.
 * @param[in] str Chaîne à parcourir.
 * @return La longueur de la chaîne (sans compter l'octet zéro).
 */
uint16_t strlen(uint8_t* str);

#endif