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

#ifndef DISTSNSR_H_ // Include Guard
#define DISTSNSR_H_

typedef uint8_t PinAPos;

#include <incl.h>
#include <can.h>

/**
 * @class   DistSnsr
 * 
 * @brief   Classe à utiliser pour obtenir la valeur de distance lue par le
 *          capteur de distance GP2D12. La classe se charge de l'interprétation
 *          de la valeur analogique que fourni le capteur et donne une valeur
 *          normalisée de la distance (voir <DistSnsr::read>).
 */
class DistSnsr {

public:
    /**
     * @brief   Initialisation du détecteur. À appeler au début du programme.
     *          Met en entrée la broche <pinANum> du port A où le signal
     *          analogique du capteur de distance est reçu.
     * 
     * @param[in]   pinANum     La position de la broche où la sortie du capteur
     *                          est branchée.
     * 
     *                          La valeur peut prendre une de celles-ci:
     *                              [PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7]
     *                          Elles sont définit dans la librairie d'AVR.
     */
    static void     init(PinAPos pinANum);

    /**
     * @brief   Lit la valeur du capteur et l'interprète pour retourner une
     *          de ditance relative (voir l'explication dans @return).
     * 
     * @return  Une valeur allant de 0 à 255 représentant des distances allant
     *          respectivement de 10 à 80 cm (Ex.: 10 cm => 0x00, 80 cm => 0xFF,
     *          45 cm => 0x7F).
     */
    static uint8_t  read();

private:
    /**
     * @type    PinAPos
     * @brief   Numéro de la broche.
     */
    static PinAPos _PINA_NUM;

};

#endif  // Include Guard