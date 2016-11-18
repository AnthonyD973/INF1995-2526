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

#define SENSOR_PORT		PORTC
#define SENSOR_DIRECTION	DDRC

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
     *		Met en entr�e les broches du port C qui re�oit les sorties du capteur
     *          Met en entr�e le num�ro du compteur qui sera utilis� pour g�n�rer des 
     *          interruptions � une fr�quence de 100 Hz afin de mettre � jour la lecture
     * 		du capteur
     *
     * @param[in] port
     */
    static void init(volatile uint8_t* port);

    /**
     * @brief 	Lit la valeur du capteur pour donner la position    
     * 	      	du robot par rapport � ligne qu'il suit
     * @return  Un byte dont cinq bits sont d'int�r�t. Deux bits du milieu servent
     *		d'indicateur pour un d�placement suivant la ligne, i.e. 0b00110 ou 0b01100
     *		Toute combinaison diff�rente n�cessite une correction 
     */		
    static uint8_t read();

// Une m�thode estSurLaligne() qui retourne un bool�en pourrait �tre �galement int�ressante;
// son r�sultat d�clencherait l'appel de l'algorithme de correction de trajectoire ...

private:
    /**
     * @brief   Nom du port utilis� pour la r�ception des sorties du capteur
     */
    static uint8_t _PORT;

};

#endif  // LINE_SNSR_H
