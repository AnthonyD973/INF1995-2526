/**
 * @file    DistSnsr.h
 * 
 * @brief   Définition de DistSnsr qui permet l'accès au capteur de distance
 *      GP2D12 de SHARP.
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

#ifndef DIST_SNSR_H_
#define DIST_SNSR_H_

#include <incl.h>
#include <lib.h>
#include <can.h>

#include "typedefs.h"

/**
 * @class DistSnsr
 * @brief   Classe à utiliser pour obtenir la valeur de distance lue par le
 *          capteur de distance GP2D12.
 * 
 * La classe se charge de l'interprétation de la valeur analogique que fournit
 * le capteur et donne une valeur normalisée de la distance (voir
 * DistSnsr::read).
 */
class DistSnsr {

public:
    /**
     * @brief   Initialisation du détecteur. À appeler au début du programme.
     * @param[in] pinANum   La position de la broche où la sortie du capteur
     *                      est branchée. Entre 0 (PA0) et 7 (PA7).
     */
    static void init(uint8_t pinANum);

    /**
     * @brief   Lit la valeur du capteur.
     * 
     * @return  Une valeur allant de 0 à 256 représentant la valeur de la
     *          tension émise par le capteur.
     */
    static uint8_t read();
    /**
     * @brief   Effectue 32 lectures en rafale sur le capteur et en fait la
     *      moyenne pour avoir un signal plus constant entre deux lectures.
     * 
     * @return  Une valeur moyenne allant de 0 à 256 représentant la valeur de
     *          la tension émise par le capteur.
     */
    static uint8_t readAverage();

private:
    /**
     * @brief   Numéro de la broche. Entre 0 (PA0) et 7 (PA7).
     */
    static uint8_t _PIN_A_NUM;

};

#endif  // DIST_SNSR_H_
