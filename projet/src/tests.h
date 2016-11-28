/**
 * Tests des capteurs et de certaines classes.
 *
 * Ecole Polytechnique de Montreal
 * Département de Génie Informatique
 * Cours INF1995
 *
 * Emir Khaled Belhaddad, Anthony Dentinger,
 * Gergi Younis et Vincent Dandenault
 * 2016
 *
 * Code qui n'est sous aucune license.
 * 
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

void testColorSensor();

void testDistSensor();

void testColorSequenceDetector(const ShapeColor shapeSequence[3]);

void testBuzzer();

#endif // TESTS_H
