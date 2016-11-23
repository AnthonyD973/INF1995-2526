#ifndef BUZZER_H // BUZZER_H
#define BUZZER_H

#include "lib.h"
#include "timer.h"

/**
 * @brief   Classe gérant le piezo-electrique.
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
     * @brief   Cette fonction fait la un lien entre la table midi et les
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
};

#endif // BUZZER_H
