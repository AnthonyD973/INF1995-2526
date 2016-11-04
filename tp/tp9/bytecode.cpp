#include "lib.h"
#include "ram.h"
#include "pinPosition.h"
#include "led.h"
#include "engine.h"
#include "defaultISR.h"

// A COMPLETER AVEC L'APPEL DES FONCTIONS ADEQUATES DES CLASSES EXISTANTES	

enum {
	// mnémonique 		instruction binaire 		Description

		dbt = 		  0x01,				// début
		att = 		  0x02,				// attendre
		dal = 		  0x44,				// allumer la DEL
		det = 		  0x45, 			// éteindre la DEL
		sgo = 		  0x48,				// jouer une sonorité
		sar = 		  0x09,				// arrêter une sonorité
		mar = 		  0x60,				// arrêter les moteurs
		mav = 		  0x62, 			// avancer
		mre = 		  0x63,				// reculer
		trd = 		  0x64,				// tourner à droite
		trg = 		  0x65,				// tourner à gauche
		dbc = 		  0xC0,				// début de boucle
		fbc = 		  0xC1,				// fin de boucle
		fin = 		  0xFF,				// fin 
	};

// Boucle d'interprétation

	void dec(uint8_t opcode) { // opcode : valeur à chercher en mémoire
	for EVER {
	switch(opcode) { // Décodage
	case dbt: // Appel de la classe LED possiblement pour allumer LED en vert par exemple ; break;
        case att:  _delay_ms(valeur lue en mémoire du deuxième opérande); break; // Appel de la classe RAM en lecture
        case dal:  // Appel de la classe LED pour allumer la LED; break;
	case det:  // Appel de la classe LED pour éteindre la LED; break;
        case sgo:  // Appel de la classe Song; break;
        case sar:  // Appel de la classe Song; break;
	case mar:  // Appel de la classe Engine pour arrêter les moteurs; break;
        case mav:  // Appel de la classe Engine pour faire avancer les moteurs en ligne droite; break;
        case mre:  // Appel de la classe Engine pour faire reculer les moteurs en ligne droite; break;
	case trd:  // Appel de la classe Engine pour faire virer les moteurs de 90 degrés à droite; break;
        case trg:  // Appel de la classe Engine pour faire virer les moteurs de 90 degrés à gauche; break;
        case dbc:  // Lecture du deuxième oprérande en mémoire pour déterminer le nombre d'exécution de la boucle;	   
		   // Lecture du prochain opérande en mémoire;
		   // Branchement à la case correspondante;
	case fbc:  // Décrémentation du compteur de boucle tant qu'il n'est pas nul; 
		   // Retour à la case dbc; break;
        case fin:  return;
	default :   // Arrêt du programme probablement, aller à la case fin
	}
}