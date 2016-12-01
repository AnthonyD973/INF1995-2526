/**
 * @file    LineSnsr.h
 * 
 * @brief   Définition de LineSnsr qui permet l'accès au capteur suiveur de
 *      ligne LSS05 de Cytron Technologies.
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

#ifndef LINE_SNSR_H
#define LINE_SNSR_H

#include <incl.h>
#include <lib.h>

#include "typedefs.h"

/** @cond FALSE */ // Ne pas documenter cette macro.
#define LINE_BITS_MASK 0x1F
/** @endcond */

/**
 * @brief   Classe qui permet de lire les valeurs binaires du capteur LSS05.
 * 
 * Une combinaison binaire de 5 bits en provenance du capteur indique
 * la position du robot par rapport à une ligne noire sur une surface blanche.
 * Cette indication sert à vérifier si le robot se trouve toujours sur la ligne
 * et à corriger sa position dans le cas contraire.
 */
class LineSnsr {

public:
    /**
     * @brief   Initialisation du détecteur. À appeler au début du programme.
     * 
     * @param[in] pin   Registre permettant de connaître la valeur actuelle sur les broches.
     * @param[in] port  Registre vers lequel écrire les valeurs sur les broches.
     * @param[in] ddr   Registre définissant les modes d'entrée/sortie des
     *      broches.
     */
    static void init(volatile uint8_t* pin, volatile uint8_t* port, volatile uint8_t* ddr);

    /**
     * @brief   Lit la valeur du suiveur de ligne pour donner la position du
     *      robot par rapport à la ligne.
     * 
     * <ul>
     * <li>Les bits 0 à 4 correspondent aux cinq sorties du capteur (avec
     * bit 0 => capteur de gauche).</li>
     * 
     * <li>Les bits 5, 6 et 7 sont toujours à 0.</li>
     * </ul>
     * 
     * @return  Un byte dont cinq bits sont d'intérêt.
     */
    static uint8_t read();


private:
    /**
     * @brief   Pin d'où lire les entrées du capteur.
     */
    static volatile uint8_t* _PIN;  // PIN != PORT (Ils ont des fonctions
                                    // différentes et ne retourne pas la même
                                    // chose)

};

#endif  // LINE_SNSR_H
