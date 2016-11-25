/*
 * Fichier à inclure dans les fichiers d'en-tête de la librarie.
 *
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

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define _MASKV(reg, value, mask) ((reg) & ~(mask)) | ((value) & (mask)) // Retourne la valeur d'un masque appliqué à certain bits
#define _MASK(reg, value, mask) (reg = _MASKV(reg, value, mask)) // Change la valeur de certains bits d'un registre.