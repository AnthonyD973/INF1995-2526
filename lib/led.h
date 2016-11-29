/**
 * @file    led.h
 * 
 * @brief   Définition de LED qui permet, comme son nom l'indique, d'utiliser
 *      une %LED.
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

#ifndef LED_H
#define LED_H

#include "incl.h"
#include "typedefsLib.h"
#include "lib.h"
#include "timer.h"


// ===============================
// =   GESTION DES LED AMBRES    =
// ===============================

/**
 * @brief Change la couleur des leds présentement ambres gérées par un compteur.
 *      NOTE: Cette fonction n'est utilisée nulle part dans les libraires ; c'est une fonction
 *      préécrite que l'on peut utiliser dans les routines d'interruption.
 * @param[in,out] timer Compteur impliqué. E.g., si la routine d'interruption
 *      qui utilise cette méthode est TIMER0_OVF_vec, alors timer doit valoir
 *      &timer0.
 */
void switchAmberLedsColor(Timer* timer);

// ===============
// =     LED     =
// ===============

/**
 * @brief   Classe permettant, comme son nom l'indique, de contrôler une LED.
 * 
 * Règle particulière pour la LED ambre (<b>qui n'est pas utilisée dans le
 * projet</b>):
 * 
 * La LED doit être associée à un Timer. La routine d'interruption TIMERN_OVF
 * doit faire appel à la routine switchAmberLedsColor, qui se chargera
 * d'effectivment inverser la couleur de la LED.
 */
class LED {
public:
    /**
     * @brief   Construit une LED en fonction de sa position. Spécifie aussi
     *      le Timer qui gèrera la couleur ambre de la LED.
     * @param[in] ledPos    Position de la LED sur les broches. Voir lib.h.
     * @param[in] timer Timer pour lequel l'interruption TIMER_N_OVF gèrera
     *      la couleur ambre de la LED. Si la LED n'utilise pas la couleur
     *      ambre, mettre timer à nullptr.
     */
    LED(LedPosition ledPos, Timer* timer);
    
    /**
     * @brief   Met la LED à une certaine couleur.
     * @param[in] color Couleur à mettre sur la LED.
     */
    void setColor(volatile LedColor color);
    
    /**
     * @brief   Accède à la couleur présente de la LED.
     * @return  La couleur de la LED.
     */
    LedColor getColor();
    
    /**
     * @brief   Accède à la position de la LED sur les broches.
     * @return  La position de la LED sur les broches.
     */
    LedPosition getLedPos();
    
    /**
     * @brief   Change le Timer qui gèrera la couleur ambre de la LED.
     * @param[in] timer Timer pour lequel l'interruption TIMER_N_OVF gèrera
     *      la couleur ambre de la LED.
     */
    void setTimer(Timer* timer);
    /**
     * @brief   Accède au Timer qui gère la couleur ambre de la LED.
     * @return  Le Timer qui gère la couleur ambre de la LED.
     */
    Timer* getTimer();
    
private:
    /**
     * @brief   Met la LED sur la couleur ambre et informe le Timer d'une
     *      nouvelle LED ambre à gérer.
     */
    void _setColorAmber();
    /**
     * @brief   Met la LED sur la couleur ambre et informe le Timer qu'une LED
     *      n'est plus ambre.
     */
    void _unsetColorAmber();
    
    /**
     * @brief   Timer qui gère la couleur ambre de la LED.
     */
    Timer* _timer;
    /**
     * @brief   Position de la LED sur les broches. Voir lib.h.
     */
    const LedPosition _ledPos;
    /**
     * @brief   Couleur actuelle de la LED.
     */
    volatile LedColor _color;
    
    /**
     * @brief   Valeur à mettre sur le port lorsqu'on met la LED verte.
     */
    const uint8_t _GREEN;
    /**
     * @brief   Valeur à mettre sur le port lorsqu'on met la LED rouge.
     */
    const uint8_t _RED;
    
    /**
     * @brief   Masque du port : les bits à 1 sont les bits utilisés par la LED.
     */
    const uint8_t _THIS_MASK;
    /**
     * @brief   Port sur lequel la LED est placée.
     */
    volatile uint8_t* const _PORT;
};

#endif // LED_H
