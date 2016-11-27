/* 
 * Classe permettant l'accès au capteur de distance GP2D12 de SHARP.
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

#ifndef DIST_SNSR_H_
#define DIST_SNSR_H_

#include <incl.h>
#include <lib.h>
#include <can.h>

#include "typedefs.h"

/**
 * @class   DistSnsr
 * 
 * @brief   Classe à utiliser pour obtenir la valeur de distance lue par le
 *          capteur de distance GP2D12. La classe se charge de l'interprétation
 *          de la valeur analogique que fournit le capteur et donne une valeur
 *          normalisée de la distance (voir DistSnsr::read).
 */
class DistSnsr {

public:
    /**
     * @brief   Initialisation du détecteur. À appeler au début du programme.
     *          Met en entrée la broche pinANum du port A où le signal
     *          analogique du capteur de distance est reçu.
     * 
     * @param[in]   pinANum     La position de la broche où la sortie du capteur
     *                          est branchée.
     * 
     *                          La valeur peut prendre une de celles-ci:
     *                              [PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7]
     *                          Elles sont définies dans la librairie d'AVR.
     */
    static void     init(uint8_t pinANum);

    /**
     * @brief   Lit la valeur du capteur.
     * 
     * @return  Une valeur allant de 0 à 256 représentant la valeur de la
     *          tension émise par le capteur.
     */
    static uint8_t  read();
    /**
     * @brief   Effectue 32 lectures sur le capteur en rafale pour ensuite en
     *          faire la moyenne afin de lisser tout pic qui puisse être causé
     *          par du bruit dans le signal reçu et avoir des valeurs
     *          relativement constante et précise.
     * 
     * @return  Une valeur moyenne allant de 0 à 256 représentant la valeur de
     *          la tension émise par le capteur.
     */
    static uint8_t  readAverage();

private:
    /**
     * @brief   Numéro de la broche.
     */
    static uint8_t _PIN_A_NUM;

};

#endif  // DIST_SNSR_H_
