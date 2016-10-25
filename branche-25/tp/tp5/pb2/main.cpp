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

ISR (INT0_vect) {
    boutonPoussoir = true;
	_delay_ms(20);
    
    
    EIFR |= _BV(INTF0);
}

void initialisation() {
    cli();
    
    DDRA = DDRB = DDRC = 0xff;
    DDRD = 0xff & ~_BV(PD2); // Tout en OUT sauf D2 (interrupt)
    
    EIMSK |= _BV(INT0);
    
    EICRA |= 0x03;
    
    sei();
}

void partirMinuterie(uint16_t duree) {
	minuterieExpiree = 0;
	TCNT1 = 0;
	OCR1A = duree;
	
    TCCR1A = _BV(COM1A1) | _BV(COM1A0) ; // 11000000
    TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10) ; // 00001101
    TCCR1C = 0;

	TIMSK1 = _BV(OCIE1A);
}


/**
 * @brief Fonction principale du programme.
 */
int main() {
	initialisation();

	PORTB = C_OFF;
	
	_delay_ms(10000.0);
	PORTB = C_RED;

	_delay_ms(100.0);
	PORTB = C_OFF;

	partirMinuterie(F_CPU/1024);
	
    do {
		
	} while(!minuterieExpiree && !boutonPoussoir);

	cli();

	
	if (boutonPoussoir) {
		PORTB = C_GREEN;
	}
	else {
		PORTB = C_RED;
	}

    
    for EVER { }
    
    return 0;
}
