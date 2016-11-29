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

/**
 * @mainpage BIENVENUE DANS LA DOCUMENTATION DE NOTRE PROJET
 * @anchor  SRC_MAINPAGE
 * 
 * Notre répertoire Git contient trois documentations:
 * <ol type="1">
 *     <li>La documentation de notre [librairie](@ref LIB_MAINPAGE), située sous lib/ ;</li>
 *     <li>La documentation de notre [compilateur GAS](@ref LIB_MAINPAGE), situé sous projet/gas/; </li>
 *     <li>La documentation des [fichiers créés pour notre projet](@ref SRC_MAINPAGE), situés sous projet/src.</li>
 * </ol>
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
#include "Player.h"

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
    Player::init();
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
    
    Player::play();
    
    for EVER {
        // Busy wait
    }
    
    return 0;
}
/** @endcond */
