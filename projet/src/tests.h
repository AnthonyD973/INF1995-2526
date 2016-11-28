/**
 * @file    tests.h
 * 
 * @brief   Définition de quelques fonctions de tests.
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

#ifndef TESTS_H
#define TESTS_H

#include <lib.h>
#include <timer.h>
#include <led.h>
#include <buzzer.h>
#include <uart.h>

#include "typedefs.h"
#include "LineSnsr.h"
#include "DistSnsr.h"
#include "ColorSnsr.h"
#include "path.h"
#include "ShapeDetector.h"
#include "ColorSequenceDetector.h"

/**
 * @brief   Teste la classe ColorSnsr en faisant des lectures à l'infini et en
 *      allumant la LED dépendamment de la couleur retournée.
 */
void testColorSensor();

/**
 * @brief   Teste la classe DistSnsr en transmettant la valeur retournée via
 *      l'UART.
 */
void testDistSensor();

/**
 * @brief   Teste la classe Buzzer en faisant jouer une musique.
 */
void testBuzzer();

#endif // TESTS_H
