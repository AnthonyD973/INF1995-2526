/*
 * +------------+
 * |État courant|
 * +------------+---------------------------+
 * |    INIT    |        PRESSED1/OFF       |
 * |  PRESSED1  |        PRESSED2/OFF       |
 * |  PRESSED2  |        PRESSED3/OFF       |
 * |  PRESSED3  |        PRESSED4/OFF       |
 * |  PRESSED4  |           ON/OFF          |
 * |     ON     |          INIT/RED         |
 * +------------+---------------------------+
 *              | Prochain État/LED Actuel  |
 *              +---------------------------+
 * 
 * NOTE : La transition d'état se fait au prochain front descendant, sauf
 *        pour la transition ON -> INIT qui se fait au bout d'une seconde.
 */


#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define EVER (;;)

enum State {
    INIT,
    PRESSED1,
    PRESSED2,
    PRESSED3,
    PRESSED4,
    ON
};


/**
 * @brief Constantes pour la DEL.
 */
const uint8_t
    C_OFF   = 0x00,
    C_GREEN = 0x01,
    C_RED   = 0x02,
    C_AMBER = 0xFF;

/**
 * @brief Détection de front montant d'un port avec antirebond.
 *        Change previousPin si le front montant est détecté.
 * @param[in] pin État du port.
 * @param[in] previousPin État précédent du port.
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
 * @brief Détection de front descendant d'un port avec antirebond.
 *        Change previousPin si le front descendant est détecté.
 * @param[in] pin État du port.
 * @param[in] previousPin État précédent du port.
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
 * @brief Fonction principale du programme.
 */
int main() {
    DDRA = DDRB = DDRC = 0xff;
    DDRD = 0x00;
    
    uint8_t oldPortD = PIND;
    
    State state = INIT;
    
    for EVER {
        if (risingEdge((uint8_t)PIND, oldPortD)) { }
        if (state < ON && fallingEdge((uint8_t)PIND, oldPortD)) {
            state = (State)((uint8_t)state + 1);
        }
        else if (state >= ON) {
            state = INIT;
        }
        
        //*
        if (state < ON) {
            PORTB = C_OFF;
        }
        else {
            PORTB = C_RED;
            _delay_ms(1000.0);
            PORTB = C_OFF;
        }//*/
    }
    
    return 0;
}
