#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "led.h"
#include "lib.h"

#define EVER (;;)


/**
 * @brief Fonction principale du programme.
 */
int main() {
    DDRD = 0x00;		// Entrées
    DDRA = DDRB = DDRC = 0xff;	// Sorties
    
    
    const uint16_t WAIT_TIME_100us = 30000 / (16 + 1);
    uint8_t curRatio;
    
    // Boucle d'exécution infinie.
    for EVER {
        curRatio = 16;
        while (curRatio <= 16) {
            ledFade(LED_OFF, LED_RED, WAIT_TIME_100us, curRatio);
            --curRatio;
        }
    }
    
    
    return 0;
}
