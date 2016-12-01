/**
 * @file    Player.h
 * 
 * @brief   Définition de Player qui permet de jouer une chanson à la fin de
 *      l'épreuve.
 * 
 * @warning Player n'est pas utilisée pour l'épreuve ; elle est utilisée
 *      juste après la fin de l'épreuve.
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

#ifndef PLAYER_H
#define PLAYER_H // Include Guard

#include <buzzer.h>
#include <ram.h>
#include <uart.h>

/**
 * @brief   Classe qui permet de jouer une chanson à la fin de l'épreuve \\(^_^)/
 * @warning Cette classe n'est pas utilisée pour l'épreuve ; elle est utilisée
 *      juste après la fin de l'épreuve.
 */
class Player {

/** @cond FALSE */ // Ne pas documenter cette classe.

public:
    static void init();
    static void play();
    
private:
    static uint16_t songFileAddr;
    static uint16_t nNotes;
    static uint16_t begNotesAddr;

/** @endcond */

};

#endif // PLAYER_H
