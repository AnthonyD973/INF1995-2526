/*
 * Classe permettant l'utilisation d'une LED.
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

#ifndef LED_H
#define LED_H

#include "incl.h"

typedef uint8_t LedColor;
typedef uint8_t PinPosition;

#include "lib.h"
#include "timer.h"


/**
 * @brief Constantes pour la DEL.
 */
// ---LedColor---
#define    LED_OFF   0x00
#define    LED_GREEN 0x01
#define    LED_RED   0x02
#define    LED_AMBER 0xFF

// ---PinPosition---
#define    A0_A1 0
#define    A2_A3 2
#define    A4_A5 4
#define    A6_A7 6
#define    B0_B1 8
#define    B2_B3 10
#define    B4_B5 12
#define    B6_B7 14
#define    C0_C1 16
#define    C2_C3 18
#define    C4_C5 20
#define    C6_C7 22
#define    D0_D1 24
#define    D2_D3 26
#define    D4_D5 28
#define    D6_D7 30


// ===============================
// =   GESTION DES LED AMBRES    =
// ===============================

/**
 * @brief Change la couleur des leds présentement ambres gérées par un compteur.
 *      NOTE: Cette fonction n'est utilisée nulle part dans les libraires ; c'est une fonction
 *      préécrite que l'on peut utiliser dans les routines d'interruption.
 * @param[in] timer Compteur impliqué.
 */
void switchAmberLedsColor(Timer* timer);

// ===============
// =     LED     =
// ===============

class LED {
public:
    /**
     * @brief   Construit une LED en fonction de sa position. Spécifie aussi
     *      le Timer qui gèrera la couleur ambre de la LED.
     * @param[in] pinPos    Position de la LED sur les broches. Voir lib.h.
     * @param[in] timer Timer pour lequel l'interruption TIMER_N_OVF gèrera
     *      la couleur ambre de la LED. Si la LED n'utilise pas la couleur
     *      ambre, mettre timer à nullptr.
     */
    LED(PinPosition pinPos, Timer* timer);
    
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
    PinPosition getPinPos();
    
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
     * @param[in] timer Timer pour lequel l'interruption TIMER_N_OVF gèrera
     *      la couleur ambre de la LED.
     */
    void _setColorAmber();
    /**
     * @brief   Met la LED sur la couleur ambre et informe le Timer qu'une LED
     *      n'est plus ambre.
     * @param[in] timer Timer pour lequel l'interruption TIMER_N_OVF gèrera
     *      la couleur ambre de la LED.
     */
    void _unsetColorAmber();
    
    /**
     * @brief   Timer qui gère la couleur ambre de la LED.
     */
    Timer* _timer;
    /**
     * @brief   Position de la LED sur les broches. Voir lib.h.
     */
    const PinPosition _pinPos;
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
