/**
 * @file    main.cpp
 * 
 * @brief   Fichier principal du projet.
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

#include <lib.h>
#include <timer.h>
#include <led.h>
#include <buzzer.h>
#include <uart.h>

#include "LineSnsr.h"
#include "DistSnsr.h"
#include "ColorSnsr.h"
#include "ShapeDetector.h"
#include "ColorSequenceDetector.h"
#include "path.h"
#include "tests.h"

/**
 * @brief   Initialisation globale du microcontrôleur.
 * @param[in,out] engL  Moteur gauche. Doit être instancié dans main pour
 *      éviter qu'il soit détruit.
 * @param[in,out] engR  Moteur droit. Doit être instancié dans main pour
 *      éviter qu'il soit détruit.
 * @param[in,out] led   LED libre. Doit être instancié dans main pour
 *      éviter qu'il soit détruit.
 */
void globalInit(Engine& engL, Engine& engR, LED& led) {
    // DDRA est modifié par LineSnsr::init.
    DDRB = 0xFD; // 1111 1101
    DDRC = 0xFF; // 1111 1111
    DDRD = 0xFF; // 1111 1111
    
    
    UART::init(2400);
    CAN::init();
    LineSnsr::init(&PINA, &PORTA, &DDRA);
    DistSnsr::init(PA7);
    ColorSnsr::init(T1_RISING_EDGE);
    Path::init(&engL, &engR);
    Buzzer::init(&timer0);
    ShapeDetector::init(&led);
    ColorSequenceDetector::init(&led);
}

/** @cond FALSE */ // Ne pas documenter cette fonction.
int main() {
    Engine engL(T2CA);
    Engine engR(T2CB);
    LED led(C4_C5, nullptr);
    
    globalInit(engL, engR, led);
    
    ShapeColor shapeSequence[COLOR_SEQ_MAX];
    
	
    Path::doPath(0);
    shapeSequence[2] = ShapeDetector::checkShape();
    Path::doPath(1);
    shapeSequence[1] = ShapeDetector::checkShape();
    Path::doPath(1);
    shapeSequence[0] = ShapeDetector::checkShape();
    Path::doPath(2);
    
    ColorSequenceDetector::checkSequence(shapeSequence);
    
    for EVER {
        // Busy wait
    }
    
    return 0;
}
/** @endcond */
