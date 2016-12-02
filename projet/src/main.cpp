/**
 * @file    src/main.cpp
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
 *     <li>La documentation de notre [compilateur GAS](@ref GAS_MAINPAGE), situé sous projet/gas/; </li>
 *     <li>La documentation des [fichiers créés pour notre projet](@ref SRC_MAINPAGE), situés sous projet/src.</li>
 * </ol>
 * 
 * <div id="PLUGIN">
 * <h2>Comment brancher les composantes</h2>
 * </div>
 * <ul>
 *     <li>PORT A</li>
 *     <ul>
 *         <li>0-5: @link LineSnsr Suiveur de ligne@endlink. Les bits des
 *             capteurs sont du côté des bits moins significatifs.</li>
 *         <li>7: Bit OUT du @link DistSnsr capteur de distance@endlink.</li>
 *     </ul>
 *     <li>PORT B</li>
 *     <ul>
 *         <li>0-1: Bits %LED et OUT (respectivement) du @link ColorSnsr capteur de couleur@endlink.</li>
 *         <li>2-3: Bits du @link Buzzer piézo-électrique@endlink.</li>
 *     </ul>
 *     <li>PORT C</li>
 *     <ul>
 *         <li>2-3: Bits S0 et S1 (respectivement) du @link ColorSnsr capteur de couleur@endlink.</li>
 *         <li>4-5: @link LED Del libre@endlink. La borne positive doit être
 *             vers l'extérieur de la carte (du même côté que le VCC).</li>
 *         <li>6-7: Bits S2 et S3 (respectivement) du @link ColorSnsr capteur de couleur@endlink.</li>
 *     </ul>
 *     <li>PORT D</li>
 *     <ul>
 *         <li>4,6: Bits <i>Direction</i> et <i>Enable</i> du @link Engine moteur @endlink droit.</li>
 *         <li>5,7: Bits <i>Direction</i> et <i>Enable</i> du @link Engine moteur @endlink gauche.</li>
 *     </ul>
 * </ul>
 * 
 * <div if="SNSRS">
 * <h2>Placement des capteurs</h2>
 * </div>
 * 
 * <ul><li><b>@link LineSnsr Suiveur de lignes@endlink (LSS05)</b></li></ul>
 * Le suiveur de lignes est placé sous le robot et en avant.
 * 
 * <ul><li><b>@link DistSnsr Capteur de distance@endlink (GP2D12)</b></li></ul>
 * Le capteur de distance est placé sur le robot et en avant.
 * 
 * <ul><li><b>@link ColorSnsr Capteur de couleurs@endlink (TCS230)</b></li></ul>
 * Le capteur de couleurs est placé sur le robot et sur la droite.
 * 
 * 
 * <div id="HOWTO">
 * <h2>Faire fonctionner notre projet</h2>
 * </div>
 * 
 * Pour faire fonctionner votre robot, simplement exécuter la commande...
 * 
 *     $ make everything
 * 
 * ...dans le dossier projet/src
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
