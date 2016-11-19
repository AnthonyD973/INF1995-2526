/* 
 * Classe permettant l'accès au capteur suiveur de ligne LSS05 de Cytron Technologies.
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

#ifndef LINE_SNSR_H
#define LINE_SNSR_H

#include <incl.h>

/**
 * @class   LineSnsr
 * 
 * @brief   Classe qui permet de lire les valeurs binaires du capteur LSS05 
 *          Une combinaison binaire de 5 bits en provenance du capteur indique
 *          la position du robot par rapport à une ligne noire sur une surface blanche.
 * 	    Cette indication sert à vérifier si le robot se trouve toujours sur la ligne
 *	    et à corriger sa position dans le cas contraire 	
 */
class LineSnsr {

public:
    /**
     * @brief   Initialisation du détecteur. À appeler au début du programme.
     *		Met en entrée les broches du port passé en paramètre qui reçoit les sorties du capteur.
     *
     * @param[in] pin, port, ddr
     */
    static void init(volatile uint8_t* pin, volatile uint8_t* port, volatile uint8_t* ddr);

    /**
     * @brief 	Lit la valeur du capteur pour donner la position    
     * 	      	du robot par rapport à ligne qu'il suit.
     *          Les broches 1 à 5 (bits 0 à 4) correspondent aux cinq sorties du capteur (la broche 1 
     *          correspondant au détecteur de gauche)
     *		La broche 6 (bit 5) est mise à 1 (pas de calibration; capteur déjà calibré)
     *		Les broches restantes (bits 6 et 7) ne sont pas utilisés
     *
     * @return  Un byte dont cinq bits sont d'intérêt (encodés comme ci-dessus)
     */		
    static uint8_t read();


private:
    /**
     * @brief   Nom du port utilisé pour la réception des sorties du capteur
     */
    static volatile uint8_t* _PIN;

};

#endif  // LINE_SNSR_H
