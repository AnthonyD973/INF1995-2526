/**
 * @file    incl.h
 * 
 * @brief   Fichier à inclure dans les fichiers d'en-tête de la librarie.
 * 
 * @authors Belhaddad, Emir Khaled
 * @authors Dandenault, Vincent
 * @authors Dentinger, Anthony
 * @authors Younis, Gergi
 * 
 * @date Automne 2016
 * 
 * @copyright Code qui n'est sous aucune license.
 */
#ifndef INCL_H
#define INCL_H

/**
 * @brief Fréquence du microcontrôleur, en Hertz.
 */
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "typedefsLib.h"

/**
 * @brief Retourne la valeur d'un registre lorsqu'on lui aura changé certains bits
 */
#define _MASKV(reg, value, mask) ((reg) & ~(mask)) | ((value) & (mask))
/**
 * @brief Change la valeur de certains bits d'un registre.
 */
#define _MASK(reg, value, mask) (reg = _MASKV(reg, value, mask))

#endif // INCL_H