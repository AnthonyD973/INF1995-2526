#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#ifndef LED_H // INCLUDE GUARD
#define LED_H 1

#ifndef PORT_OUT
#define PORT_OUT PORTB
#endif

/**
 * @brief Constantes pour la DEL.
 */
const uint8_t
    LED_OFF   = 0x00,
    LED_GREEN = 0x01,
    LED_RED   = 0x02,
    LED_AMBER = 0xFF;

/**
 * @brief Garde la LED allumée à une couleur donnée pour un temps donné.
 * @param[in] color  Couleur demandée.
 * @param[in] t100us Temps à attendre (* 100 µs).
 */
void ledControl(const uint8_t& color, const uint16_t& t100us);
/**
 * @brief Passe la LED entre deux couleurs selon un certain ratio.
 * @param[in] color1 Couleur de la LED losrque ratio vaut 0.
 * @param[in] color2 Couleur de la LED losrque ratio vaut 16.
 * @param[in] t100us Temps à attendre (* 100 µs).
 * @param[in] ratio  Ratio entre couleur1 (0) et couleur2 (16) de la LED. On devrait avoir 0 <= ratio <= 16.
 */
void ledFade(const uint8_t& color1, const uint8_t& color2, const uint16_t& t100us, const uint8_t& ratio);
/**
 * @brief Passe la LED entre rouge et vert selon un certain ratio.
 * @param[in] t100us Temps à attendre (* 100 µs).
 * @param[in] ratio Ratio entre rouge (0) et vert (16) de la LED. On devrait avoir 0 <= ratio <= 16.
 */
void ledAmber(const uint16_t& t100us, const uint8_t& ratio);

#endif //INCLUDE GUARD
