/*              +---------------------------+
 *              |        variantState       |
 * +------------+---------------------------+
 * |État courant|      0      |      1      |
 * +------------+---------------------------+
 * |    INIT    | VARIANT/RED | VARIANT/RED |
 * |  VARIANT   |  GREEN/AMBR |  GREEN/OFF  |
 * |   GREEN    |  INIT/GREEN |  INIT/GREEN |
 * +------------+---------------------------+
 *              | Prochain État/LED Actuel  |
 *              +---------------------------+
 * NOTE 1 : Le changement d'état se fait au prochain front (montant ou descendant).
 * NOTE 2 : Lors du passage vers l'état VARIANT, variantState s'inverse.
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define EVER (;;)

enum State {
    INIT,
    VARIANT,
    GREEN,
    N_STATES
};


/**
 * @brief Constantes pour la DEL.
 */
const uint8_t
    LED_OFF   = 0x00,
    LED_GREEN = 0x01,
    LED_RED   = 0x02,
    LED_AMBER = 0xFF;

void ledControl(uint8_t color, uint16_t t100us);
void ledAmber(uint16_t t100us, uint8_t ratio);

/**
 * @brief Interrompt l'execution du programme pour un certain temps.
 * @param[in] t100us Temps à attendre (* 100 µs).
 */
void delay100MicroSeconds(uint16_t t100us) {
    for (uint16_t i = 0; i < t100us; ++i) {
        //n_delay_to_perform = t*f(Hz)/4
        _delay_loop_2(F_CPU/40000); // 100µs
    }
}

/**
 * @brief Interrompt l'execution du programme pour un certain temps.
 * @param[in] t100us Temps à attendre (* 100 µs).
 */
void delay10MiliSeconds(uint16_t t10ms) {
    for (uint16_t i = 0; i < t10ms; ++i) {
        for (uint16_t j = 0; j < 100; ++j) {
            //n_delay_to_perform = t*f(Hz)/4
            _delay_loop_2(F_CPU/40000); // 100µs
        }
    }
}

/**
 * @brief Garde la LED allumée à une couleur donnée pour un temps donné.
 * @param[in] color  Couleur demandée.
 * @param[in] t100us Temps à attendre (* 100 µs).
 */
void ledControl(uint8_t color, uint16_t t100us) {
    if (color == LED_RED || color == LED_GREEN) {
        PORTB = color;
        delay100MicroSeconds(t100us);
    }
    else if (color == LED_AMBER) {
        ledAmber(t100us, 4);
    }
    else {
        PORTB = LED_OFF;
        delay100MicroSeconds(t100us);
    }
}

/**
 * @brief Garde la LED de couleur ambre pour un temps donné.
 * @param[in] t100us Temps à attendre (* 100 µs).
 * @param[in] ratio Ratio entre le vert et le rouge de la couleur ambre. La valeur maximum supportée est 0xf .
 */
void ledAmber(uint16_t t100us, uint8_t ratio) {
    uint16_t ctr1 = t100us/0x10;
    while (ctr1 > 0) {
        ledControl(LED_RED, ratio);
        ledControl(LED_GREEN, 0x10 - ratio);
        --ctr1;
    }
}

/**
 * @brief Détection de fronts montants d'un port avec antirebond.
 *        Change previousPin si le front montant est détecté.
 * @param[in]     pin État du port.
 * @param[in|out] previousPin État précédent du port.
 * @return true si sur front montant, false sinon.
 */
bool risingEdge(const uint8_t& pin, uint8_t& previousPin)
{
    if (pin != previousPin && pin != 0x00) {
        _delay_ms(1.0);
        if (pin != 0x00) {
            previousPin = pin;
            return true;
        }
    }
    return false;
}

/**
 * @brief Détection de fronts descendants d'un port avec antirebond.
 *        Change previousPin si le front descendant est détecté.
 * @param[in]     pin État du port.
 * @param[in|out] previousPin État précédent du port.
 * @return true si sur front descendant, false sinon.
 */
bool fallingEdge(const uint8_t& pin, uint8_t& previousPin)
{
    if (pin != previousPin && pin == 0x00) {
        _delay_ms(1.0);
        if (pin == 0x00) {
            previousPin = pin;
            return true;
        }
    }
    return false;
}

/**
 * @brief Détection de fronts descendents d'un port avec antirebont.
 *        Change previousPin si un front est détecté.
 * @param[in]     pin État du port.
 * @param[in|out] previousPin État précédent du port.
 * @return true si sur front, false sinon.
 */
bool anyEdge(const uint8_t& pin, uint8_t& previousPin) {
    return risingEdge(pin, previousPin) || fallingEdge(pin, previousPin);
}

/**
 * @brief Fonction principale du programme.
 */
int main() {
    DDRA = DDRB = DDRC = 0xff;
    DDRD = 0x00;

    uint8_t oldPortD = PIND, variantState = 1;

    State state = INIT;

    for EVER {
        if (anyEdge((uint8_t)PIND, oldPortD)) {
            state = (State)(((uint8_t)state + 1) % uint8_t(N_STATES));
            if (state == VARIANT) {
                variantState ^= 1;
            }
        }


        switch (state) {
            case INIT:
                ledControl(LED_RED, 0x10);
                break;
            case VARIANT:
                if (variantState == 0x00) {
                    ledAmber(0x10, 4);
                }
                else {
                    ledControl(LED_OFF, 0x10);
                }
                break;
            case GREEN:
                ledControl(LED_GREEN, 0x10);
                break;
            default:
                state = INIT;
        }
    }

    return 0;
}
