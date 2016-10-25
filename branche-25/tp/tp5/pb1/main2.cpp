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
#define Tone uint16_t

void ajustementPWM (const uint16_t& ratio1, const uint16_t& ratio2);

enum State {
    INIT,
    SONG1,
    SONG2,
    SONG3,
    SONG4,
    N_STATE
};


/**
 * @brief Constantes pour la DEL.
 */
const uint8_t
    C_OFF   = 0x00,
    C_GREEN = 0x01,
    C_RED   = 0x02,
    C_AMBER = 0xFF;

volatile uint16_t ctr1 = ~(uint16_t(0));
volatile State state = INIT;
bool direction = true;

const Tone C = 523, Cs = 554, Df = Cs, D = 587, Ds = 622, Ef = Ds, E = 659, Es = 698, Ff = E, F = Es, Fs = 740, Gf = Fs, G = 784, Gs = 830, Af = Gs, A = 880, As = 932, Bf = As, B = 988, Bs = C*2, Cf = B/2;

Tone tones1[] = {C,D,E,F,G,A,B,C*2};
uint8_t l1 = 8;
uint8_t s1 = 4; // speed: 1 note = 1/4 de sec
Tone tones2[] = {A,A,B,B, B,B,G,G, G,G,Fs,Fs, Fs,Fs,E,E, E,E,E,E, E,E,E,E, E,E,E,E, E,E,E,E};
uint8_t l2 = 32;
uint8_t s2 = 4; // speed: 1 note = 1/4 de sec
Tone tones3[] = {B/2,Cs,D,B/2, Fs,0,0,Fs, 0,0,E,E, 0,0,0,0, B/2,Cs,D,B/2, E,0,0,E, 0,0,D,D, D,Cs,B/2,0,
                 B/2,Cs,D,B/2, D,D,D,D, E,E,Cs,Cs, Cs,B/2,A/2,A/2, A/2,0,A/2,A/2, E,E,E,E, D,D,D,D, 0,0,0,0,
                 B/2,Cs,D,B/2, Fs,0,0,Fs, 0,0,E,E, 0,0,0,0, B/2,Cs,D,B/2, A,A,A,A, Cs,Cs,D,D, Cs,Cs,B/2,0,
                 B/2,Cs,D,B/2, D,D,D,D, E,E,Cs,Cs, Cs,B/2,A/2,A/2, A/2,0,A/2,A/2, E,E,E,E, D,D,D,D, 0,0,0,0};
uint8_t l3 = 128;
uint8_t s3 = 2; // speed: 1 note = 1/8 de sec
Tone tones4[] = {
    B/2,B/2,0,0, B/2,B/2,B/2,B/2, Ds,Ds,E,E, Fs,Fs,0,0, A,A,A,A, 0,0,0,0, E,E,E,E, 0,0,0,0,
    B/2,B/2,0,0, B/2,B/2,B/2,B/2, Ds,Ds,E,E, Fs,Fs,0,0, A,A,0,0, A,A,A,A, E,E,E,E, 0,0,0,0,
    B/2,B/2,0,0, B/2,B/2,B/2,B/2, Ds,Ds,E,E, Fs,Fs,0,0, A,A,A,A, 0,0,0,0, E,E,E,E, 0,0,0,0,
    B/2,B/2,0,0, B/2,B/2,B/2,B/2, Ds,Ds,E,E, Fs,Fs,0,0, A,A,0,0, A,A,A,A, E,E,E,E, 0,0,0,0,
    
    B/2,B/2,0,0, B,0,B,0, Ds*2,Ds*2,Ds*2,Ds*2, B,B,0,0, Cs*2,Cs*2,Cs*2,Cs*2, A,A,0,0, E,E,E,E, 0,0,0,0,
    B/2,B/2,0,0, B/2,B/2,B/2,B/2, B,0,B,0, B,0,B,0, A,A,A,A, B,B,0,0, E,E,E,E, 0,0,0,0,
    B/2,B/2,0,0, B,0,B,0, Ds*2,Ds*2,Ds*2,Ds*2, B,B,0,0, Cs*2,Cs*2,Cs*2,Cs*2, A,A,0,0, E,E,E,E, 0,0,0,0,
    B/2,B/2,0,0, B/2,B/2,B/2,B/2, B,0,B,0, B,0,B,0, A,A,A,A, Cs*2,Cs*2,0,0, B,B,B,B, 0,0,B/4,B/4,
    
    D,D,D,D, D,D,B/2,B/2, B/4,B/4,B/4,B/4, D,D,D,D, D,D,B/2,B/2, B/4,B/4,B/4,B/4, D,D,D,D, D,D,B/2,B/2,
    A/4,A/4,A/4,A/4, D,D,D,D, D,D,B/2,B/2, A/4,A/4,A/4,A/4, D,D,A/4,A/4, B/2,B/2,A/4,A/4, A/2,A/2,As/2,As/2, B/2,B/2,A/4,A/4,
    D,D,D,D, D,D,B/2,B/2, Gs/4,Gs/4,Gs/4,Gs/4, D,D,D,D, D,D,B/2,B/2, Gs/4,Gs/4,Gs/4,Gs/4, D,D,D,D, D,D,B/2,B/2,
    E/4,E/4,E/4,E/4, D,D,D,D, D,D,B/2,B/2, E/4,E/4,E/4,E/4, D,D,E/4,E/4, B/2,B/2,E/4,E/4, A/2,A/2,As/2,As/2, B/2,B/2,E/4,E/4,
    
    Fs,Fs,Fs,Fs, Fs,Fs,D,D, B/4,B/4,B/4,B/4, Fs,Fs,Fs,Fs, Fs,Fs,D,D, B/4,B/4,B/4,B/4, Fs,Fs,Fs,Fs, Fs,Fs,D,D,
    A/4,A/4,A/4,A/4, Fs,Fs,Fs,Fs, Fs,Fs,D,D, A/4,A/4,A/4,A/4, Fs,Fs,A/4,A/4, D,D,A/4,A/4, C,C,Cs,Cs, D,D,A/4,A/4,
    Fs,Fs,Fs,Fs, Fs,Fs,D,D, Gs/4,Gs/4,Gs/4,Gs/4, Fs,Fs,Fs,Fs, Fs,Fs,D,D, Gs/4,Gs/4,Gs/4,Gs/4, Fs,Fs,Fs,Fs, Fs,Fs,D,D,
    E/4,E/4,E/4,E/4, Fs,Fs,Fs,Fs, Fs,Fs,D,D, E/4,E/4,E/4,E/4, Fs,Fs,E/4,E/4, D,D,E/4,E/4, C,C,Cs,Cs, D,D,E/4,E/4
};
uint16_t l4 = 512;
uint8_t s4 = 1; // speed: 1 note = 1/16 de sec

ISR (INT0_vect) {
    _delay_ms(20);
    
    if(state < N_STATE)
        state = (State)((uint8_t)state + 1);
    else if (state >= N_STATE)
        state = INIT;
    ctr1 = ~(uint16_t(0));
    ajustementPWM(0,0);
    _delay_ms(250);
    
    EIFR |= (1 << INTF0) ;
}

void initialisation() {
    cli();
    
    DDRA = DDRB = DDRC = 0xff;
    DDRD = 0xff & ~_BV(PD2); // Tout en OUT sauf D2 (interrupt) en IN
    
    state = INIT;
    ctr1 = ~(uint16_t(0));
    
    // mise a un des sorties OC1A et OC1B sur comparaison
    // reussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    TCCR1A = 0x40 ; // 01000000

    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B = 0x09 ; // 00001010
    TCCR1C = 0;
    
    EIMSK |= _BV(INT0);
    
    EICRA |= 0x0a;
    
    sei();
}

void ajustementPWM (const uint16_t& ratio1, const uint16_t& ratio2) {
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
    volatile Tone tone = 0, tone2 = 0;
    uint8_t speedFactor = 0;
    _delay_ms(500);
    for EVER {
        /*
        if (direction)
            ajustementPWM(++ctr1, (ctr1)/3);
        if (!direction)
            ajustementPWM(--ctr1, (ctr1)/3);
        if (ctr1 == 0x00 || ctr1 == 0xff)
            direction = !direction;
        _delay_ms(2000/256);//*/
        //*/
        switch(state) {
            case INIT:
                tone = 0;
                break;
            case SONG1:
                tone = tones1[++ctr1 % l1];
                speedFactor = s1;
                break;
            case SONG2:
                tone = tones2[++ctr1 % l2];
                speedFactor = s2;
                break;
            case SONG3:
                tone = tones3[++ctr1 % l3];
                speedFactor = s3;
                break;
            case SONG4:
                tone = tones4[++ctr1 % l4];
                speedFactor = s4;
                break;
            default:
                state = INIT;
                tone = 0;
                speedFactor = 0;
                break;
        }
        //tone2 = tones4_2[ctr1 % l4_2];
        
        ajustementPWM(tone != 0 ? F_CPU/(tone) : 0, tone2 != 0 ? F_CPU/(tone2) : 0);
        for (uint8_t i = 0; i < speedFactor; ++i)
            _delay_ms(125/2);
        if (ctr1%2 && speedFactor == 1) _delay_ms(1);//*/
    }
    
    return 0;
}
