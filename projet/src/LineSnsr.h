/* 
 * Classe permettant l'acc�s au capteur suiveur de ligne LSS05 de Cytron Technologies.
 *
 * Ecole Polytechnique de Montreal
 * D�partement de G�nie Informatique
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
 *          la position du robot par rapport � une ligne noire sur une surface blanche.
 * 	    Cette indication sert � v�rifier si le robot se trouve toujours sur la ligne
 *	    et � corriger sa position dans le cas contraire 	
 */
class LineSnsr {

public:
    /**
     * @brief   Initialisation du d�tecteur. � appeler au d�but du programme.
     *		Met en entr�e les broches du port pass� en param�tre qui re�oit les sorties du capteur.
     *
     * @param[in] pin, port, ddr
     */
    static void init(volatile uint8_t* pin, volatile uint8_t* port, volatile uint8_t* ddr);

    /**
     * @brief 	Lit la valeur du capteur pour donner la position    
     * 	      	du robot par rapport � ligne qu'il suit.
     *          Les broches 1 � 5 (bits 0 � 4) correspondent aux cinq sorties du capteur (la broche 1 
     *          correspondant au d�tecteur de gauche)
     *		La broche 6 (bit 5) est mise � 1 (pas de calibration; capteur d�j� calibr�)
     *		Les broches restantes (bits 6 et 7) ne sont pas utilis�s
     *
     * @return  Un byte dont cinq bits sont d'int�r�t (encod�s comme ci-dessus)
     */		
    static uint8_t read();


private:
    /**
     * @brief   Nom du port utilis� pour la r�ception des sorties du capteur
     */
    static volatile uint8_t* _PIN;

};

#endif  // LINE_SNSR_H
