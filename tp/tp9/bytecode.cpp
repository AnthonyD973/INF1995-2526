#include "lib.h"
#include "ram.h"
#include "pinPosition.h"
#include "led.h"
#include "engine.h"
#include "defaultISR.h"

// A COMPLETER AVEC L'APPEL DES FONCTIONS ADEQUATES DES CLASSES EXISTANTES	

enum {
	// mn�monique 		instruction binaire 		Description

		dbt = 		  0x01,				// d�but
		att = 		  0x02,				// attendre
		dal = 		  0x44,				// allumer la DEL
		det = 		  0x45, 			// �teindre la DEL
		sgo = 		  0x48,				// jouer une sonorit�
		sar = 		  0x09,				// arr�ter une sonorit�
		mar = 		  0x60,				// arr�ter les moteurs
		mav = 		  0x62, 			// avancer
		mre = 		  0x63,				// reculer
		trd = 		  0x64,				// tourner � droite
		trg = 		  0x65,				// tourner � gauche
		dbc = 		  0xC0,				// d�but de boucle
		fbc = 		  0xC1,				// fin de boucle
		fin = 		  0xFF,				// fin 
	};

// Boucle d'interpr�tation

	void dec(uint8_t opcode) { // opcode : valeur � chercher en m�moire
	for EVER {
	switch(opcode) { // D�codage
	case dbt: // Appel de la classe LED possiblement pour allumer LED en vert par exemple ; break;
        case att:  _delay_ms(valeur lue en m�moire du deuxi�me op�rande); break; // Appel de la classe RAM en lecture
        case dal:  // Appel de la classe LED pour allumer la LED; break;
	case det:  // Appel de la classe LED pour �teindre la LED; break;
        case sgo:  // Appel de la classe Song; break;
        case sar:  // Appel de la classe Song; break;
	case mar:  // Appel de la classe Engine pour arr�ter les moteurs; break;
        case mav:  // Appel de la classe Engine pour faire avancer les moteurs en ligne droite; break;
        case mre:  // Appel de la classe Engine pour faire reculer les moteurs en ligne droite; break;
	case trd:  // Appel de la classe Engine pour faire virer les moteurs de 90 degr�s � droite; break;
        case trg:  // Appel de la classe Engine pour faire virer les moteurs de 90 degr�s � gauche; break;
        case dbc:  // Lecture du deuxi�me opr�rande en m�moire pour d�terminer le nombre d'ex�cution de la boucle;	   
		   // Lecture du prochain op�rande en m�moire;
		   // Branchement � la case correspondante;
	case fbc:  // D�cr�mentation du compteur de boucle tant qu'il n'est pas nul; 
		   // Retour � la case dbc; break;
        case fin:  return;
	default :   // Arr�t du programme probablement, aller � la case fin
	}
}