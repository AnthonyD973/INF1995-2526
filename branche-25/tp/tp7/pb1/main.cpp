#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"

#define EVER (;;)

/**
 * @brief Constantes pour la DEL.
 */
const uint8_t
    C_OFF   = 0x00,
    C_GREEN = 0x01,
    C_RED   = 0x02,
    C_AMBER = 0xFF;

volatile uint16_t ctr1 = 0;

ISR (TIMER1_COMPA_vect) {
	ctr1++;
	TCNT1 += !(ctr1 % 4);
}

void partirCompteur(uint16_t duree) {
	ctr1 = 0;
	TCNT1 = 0;
	OCR1A = duree;
	
    TCCR1A = _BV(COM1A1) | _BV(COM1A0) ; // 11000000
    TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10) ; // 00001101
    TCCR1C = 0;

	TIMSK1 = _BV(OCIE1A);
}

void initialisation () {
    cli();
    
    DDRB |= 0x03;
    DDRD &= ~_BV(PD2);
    
    sei();
}

/**
 * @brief Fonction principale du programme.
 */
int main() {
    initialisation();
    volatile uint16_t ctr1End = 0;
    volatile uint16_t ctr1tmp = 0;
    uint16_t ctr2 = 0;
    
    partirCompteur(781);
    
    for EVER {
        while ((PIND & _BV(PD2))) asm("nop");
        
        ctr1 = 0;
        
        while (!(PIND & _BV(PD2)) && (ctr1 < 120)) asm("nop");
        ctr1tmp = ctr1End = ctr1;
        
        transmissionUART((uint8_t)ctr1End);
        
        while ((ctr1 - ctr1tmp) < 5) {
            PORTB = 0x01 & ~(ctr1 - ctr1tmp);
        }
        ctr1tmp = ctr1;
        PORTB = C_OFF;
        
        while ((ctr1 - ctr1tmp) < 20) asm("nop");
        ctr1tmp = ctr1;
        
        ctr2 = 0;
        while (ctr2 < (ctr1End / 2)) {
            PORTB = C_RED;
            while (((((ctr1 - ctr1tmp) * 10) >> 2) & 0x01) == 0);
            PORTB = C_OFF;
            while (((((ctr1 - ctr1tmp) * 10) >> 2) & 0x01) == 1);
            ctr2++;
        }
        PORTB = C_OFF;
    }
    
    return 0;
}
