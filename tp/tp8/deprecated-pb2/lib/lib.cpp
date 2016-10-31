#include "lib.h"

/**
 * @brief Interrompt l'execution du programme pour un certain temps.
 * @param[in] t100us Temps à attendre (* 100 µs).
 */
void delay100MicroSeconds(const uint16_t& t100us)
{
    for (uint16_t i = 0; i < t100us; ++i) {
        //n_delay_to_perform = t*f(Hz)/4
        _delay_loop_2(F_CPU/40000); // 100µs
    }
}

/**
 * @brief Interrompt l'execution du programme pour un certain temps.
 * @param[in] t100us Temps à attendre (* 100 µs).
 */
void delay10MiliSeconds(const uint16_t& t10ms)
{
    for (uint16_t i = 0; i < t10ms; ++i) {
        for (uint16_t j = 0; j < 100; ++j) {
            //n_delay_to_perform = t*f(Hz)/4
            _delay_loop_2(F_CPU/40000); // 100µs
        }
    }
}

/**
 * @brief Détection de fronts montants d'un port avec antirebond.
 *        Change previousPin si le front montant est détecté.
 * @param[in]     pin État du port.
 * @param[in,out] previousPin État précédent du port.
 * @return true si sur front montant, false sinon.
 */
bool risingEdge(const uint8_t& pin, uint8_t& previousPin)
{
    return anyEdge(pin, previousPin) && pin != 0x00;
}


/**
 * @brief Détection de fronts descendants d'un port avec antirebond.
 *        Change previousPin si le front descendant est détecté.
 * @param[in]     pin État du port.
 * @param[in,out] previousPin État précédent du port.
 * @return true si sur front descendant, false sinon.
 */
bool fallingEdge(const uint8_t& pin, uint8_t& previousPin)
{
    return anyEdge(pin, previousPin) && pin != 0x00;
}

/**
 * @brief Détection de fronts descendents d'un port avec antirebont.
 *        Change previousPin si un front est détecté.
 * @param[in]     pin État du port.
 * @param[in,out] previousPin État précédent du port.
 * @return true si sur front, false sinon.
 */
bool anyEdge(const uint8_t& pin, uint8_t& previousPin)
{
    if (pin != previousPin) {
        _delay_ms(1.0);
        if (pin == 0x00) {
            previousPin = pin;
            return true;
        }
    }
    return false;
}
