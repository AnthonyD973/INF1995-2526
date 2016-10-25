#include "led.h"
#include "lib.h"

/**
 * @brief Garde la LED allumée à une couleur donnée pour un temps donné.
 * @param[in] color  Couleur demandée.
 * @param[in] t100us Temps à attendre (* 100 µs).
 */
void ledControl(const uint8_t& color, const uint16_t& t100us)
{
    if (t100us == 0)
        return;
    if (color == LED_RED || color == LED_GREEN) {
        PORT_OUT = color;
        delay100MicroSeconds(t100us);
    }
    else if (color == LED_AMBER) {
        ledAmber(t100us, 4);
    }
    else {
        PORT_OUT = LED_OFF;
        delay100MicroSeconds(t100us);
    }
}

/**
 * @brief Passe la LED entre deux couleurs selon un certain ratio.
 * @param[in] color1 Couleur de la LED losrque ratio vaut 0.
 * @param[in] color2 Couleur de la LED losrque ratio vaut 16.
 * @param[in] t100us Temps à attendre (* 100 µs).
 * @param[in] ratio  Ratio entre couleur1 (0) et couleur2 (16) de la LED. On devrait avoir 0 <= ratio <= 16.
 */
void ledFade(const uint8_t& color1, const uint8_t& color2, const uint16_t& t100us, const uint8_t& ratio)
{
    if (ratio < 1) {
        ledControl(color1, t100us);
        return;
    }
    else if (ratio > 0x0f) {
        ledControl(color2, t100us);
        return;
    }
    
    uint16_t ctr1 = t100us/0x10;
    while (ctr1 > 0) {
        ledControl(color1, 0x10 - ratio);
        ledControl(color2, ratio);
        --ctr1;
    }
}

/**
 * @brief Passe la LED entre rouge et vert selon un certain ratio.
 * @param[in] t100us Temps à attendre (* 100 µs).
 * @param[in] ratio Ratio entre rouge (0) et vert (16) de la LED. On devrait avoir 0 <= ratio <= 16.
 */
void ledAmber(const uint16_t& t100us, const uint8_t& ratio)
{
    ledFade(LED_RED, LED_GREEN, t100us, ratio);
}
