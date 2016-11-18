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

#define SENSOR_PORT		PORTC
#define SENSOR_DIRECTION	DDRC

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
     *		Met en entrée les broches du port C qui reçoit les sorties du capteur
     *          Met en entrée le numéro du compteur qui sera utilisé pour générer des 
     *          interruptions à une fréquence de 100 Hz afin de mettre à jour la lecture
     * 		du capteur
     *
     * @param[in] port
     */
    static void init(volatile uint8_t* port);

    /**
     * @brief 	Lit la valeur du capteur pour donner la position    
     * 	      	du robot par rapport à ligne qu'il suit
     * @return  Un byte dont cinq bits sont d'intérêt. Deux bits du milieu servent
     *		d'indicateur pour un déplacement suivant la ligne, i.e. 0b00110 ou 0b01100
     *		Toute combinaison différente nécessite une correction 
     */		
    static uint8_t read();

// Une méthode estSurLaligne() qui retourne un booléen pourrait être également intéressante;
// son résultat déclencherait l'appel de l'algorithme de correction de trajectoire ...

private:
    /**
     * @brief   Nom du port utilisé pour la réception des sorties du capteur
     */
    static uint8_t _PORT;

};

#endif  // LINE_SNSR_H
