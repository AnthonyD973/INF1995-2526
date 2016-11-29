/**
 * @file    buzzer.h
 * 
 * @brief   Définition des Buzzer qui permet l'utilisation du piézo-électrique.
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

#ifndef BUZZER_H
#define BUZZER_H

#include "incl.h"
#include "lib.h"
#include "timer.h"

#define NO_TONE 0x00 /**< @brief Valeur représentant une absence de son. */

/**
 * @brief   Classe gérant le piézo-électrique.
 */
class Buzzer {
public:
    /**
     * @brief   Fonction permettant d'initialiser le buzzer.
     *
     * @param   timer   Timer générant le son
     */
    static void init(Timer* timer);
    
    /**
     * @brief   Cette fonction fait le un lien entre la table midi et les
     *          fréquences à jouer sur le buzzer.
     *
     * @param[in]   midi    La note midi à jouer.
     */
    static void setTone(uint8_t midiTone);
    /**
     * @brief   Cette fonction arrête tout son qui joue sur le buzzer.
     */
    static void clearTone();

private:
    /**
     * @brief   Table de correspondance entre les notes midis et la valeur à
     *          mettre dans OCR2A pour obtenir la fréquence qui leur correspond.
     *          Les notes midis vont de 24 inclusivement à 127 inclusivement.
     */
    static const uint8_t _FREQS[104];
    /**
     * @brief   Table des valeurs de prescaler correspondant à la valeur de
     *          OCR1A du même index dans le tableau Buzzer::_FREQS.
     */
    static const uint8_t _PRESCALER[52];
    /**
     * @brief   Pointeur vers le timer utilisé pour générer le son.
     */
    static Timer* _TIMER;
    /**
     * @brief   Note midi actuellemtn jouée.
     */
    static uint8_t _currTone;
};

#endif // BUZZER_H
