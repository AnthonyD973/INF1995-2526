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
#include <avr/interrupt.h>

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

volatile State state = INIT;
uint8_t ctr1 = 0;
bool direction = true;

ISR (INT0_vect) {
    _delay_ms(20);
    
    if(state < ON)
        state = (State)((uint8_t)state + 1);
    else if (state >= ON)
        state = INIT;
    
    EIFR |= (1 << INTF0) ;
}

void initialisation() {
    cli();
    
    DDRA = DDRB = DDRC = 0xff;
    DDRD = 0xff & ~_BV(PD2); // Tout en OUT sauf D2 (interrupt)
    
    state = INIT;
    
    // mise a un des sorties OC1A et OC1B sur comparaison
    // reussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    TCCR1A = 0xb1 ; // 10110001

    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B = 0x02 ; // 00000010 ... // TCCR1B = 0x12
    TCCR1C = 0;
    
    EIMSK |= _BV(INT0);
    
    EICRA |= 0x0a;
    
    sei();
}

void ajustementPWM (const uint8_t& ratio1, const uint8_t& ratio2) {
    // mise a un des sorties OC1A et OC1B sur comparaison
    // reussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    OCR1A = ratio1 ;
    OCR1B = ratio2 ;
}

/**
 * @brief Fonction principale du programme.
 */
int main() {
    initialisation();
    
    for EVER {
        //*
        if (state < ON) {
            PORTB = C_OFF;
        }
        else {
            PORTB = C_RED;
            _delay_ms(1000.0);
            PORTB = C_OFF;
            state = INIT;
        }//*/
        //*
        if (direction)
            ajustementPWM(++ctr1/3, ctr1);
        else
            ajustementPWM(--ctr1/3, ctr1);
        if ((ctr1 == 0x00) || (ctr1 == 0xff))
            direction = !direction;
        _delay_ms(2000/(256*2));//*/
    }
    
    return 0;
}
