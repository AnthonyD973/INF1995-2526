#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define EVER (;;)


/**
 * @brief Constantes pour la DEL.
 */
const uint8_t
    C_OFF   = 0x00,
    C_GREEN = 0x01,
    C_RED   = 0x02,
    C_AMBER = 0xFF;

uint8_t ctr1 = 0;
volatile bool boutonPoussoir = false;
volatile bool minuterieExpiree = false;

ISR (TIMER1_COMPA_vect) {
	minuterieExpiree = 1;
}


void initialisation() {
    cli();
    
    DDRA = DDRB = DDRC = 0xff;
    DDRD = 0xff & ~_BV(PD2); // Tout en OUT sauf D2 (interrupt)
    
    EIMSK |= 0;
    
    EICRA |= 0;
    
    sei();
}


void ajustementPWM (const uint16_t& ratio) {
    // mise a un des sorties OC1A et OC1B sur comparaison
    // reussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10); // 10110001
	OCR1A = ratio;
    OCR1B = ratio;

    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B = _BV(CS11); // 00000010
    TCCR1C = 0;
    
}


/**
 * @brief Fonction principale du programme.
 */
int main() {
	initialisation();
	
	ajustementPWM(0);
	_delay_ms(2000.0);
	ajustementPWM(0xFF/4);
	_delay_ms(2000.0);
	ajustementPWM(0xFF/2);
	_delay_ms(2000.0);
	ajustementPWM(0xFF/4*3);
	_delay_ms(2000.0);
	ajustementPWM(0xFF/1);
	_delay_ms(2000.0);
	ajustementPWM(0);
    
    return 0;
}
