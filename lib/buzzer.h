#ifndef BUZZER_H_
#define BUZZER_H_

#include "timer.h"

/**
 * @brief   Classe gérant le piezo-electrique.
 */
class Buzzer {
public:
    /**
     * @brief   Fonction permettant d'initialiser
     */
    static void init(/* Timer timer */);
    
    static void setTone(uint8_t midiTone);
    static void clearTone();

private:
    static uint16_t FREQS_[37];
};

#endif
