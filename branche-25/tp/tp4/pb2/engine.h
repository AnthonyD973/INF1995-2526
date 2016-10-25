#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#ifndef LED_H // INCLUDE GUARD
#define LED_H 1

#ifndef PORT_OUT
#define PORT_OUT PORTB
#endif

/**
 * @brief Constantes pour les moteurs.
 */
const uint8_t
    ENG_OFF   = 0x00,
    ENG_ON    = 0x02,
    
    ENG_FW    = 0x00,
    ENG_BW    = 0x01,
    
    ENG_L = 0x00,
    ENG_R = 0x02;

/**
 * @brief Garde la LED allumée à une couleur donnée pour un temps donné.
 * @param[in] color  Couleur demandée.
 * @param[in] t100us Temps à attendre (* 100 µs).
 */
void engineControl(const uint8_t& state, const uint8_t& side);
/**
 * @brief Change l'état des deux moteurs en générant un signal PWM pendant 2 secondes.
 * @param[in] frequency Fréquence du signal PWM (Hz). Doit valoir 60 ou 400.
 * @param[in] ratio	Ratio de niveau haut. Doit valoir 0, 25, 50, 75 ou 100.
 */
void enginePower(const uint16_t& frequency, const uint8_t& ratio);

#endif // INCLUDE GUARD
