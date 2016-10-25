#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "can.h"
//#include "led.h"
#include "pinPosition.h"
#include "uart.h"

#define EVER (;;)

//*
typedef uint8_t Color;

const Color
    LED_OFF   = 0x00,
    LED_GREEN = 0x01,
    LED_RED   = 0x02,
    LED_AMBER = 0xff;//*/

/*
Timer0 timer0(P01_CLK1);

ISR(TIMER0_OVF_vect) { intTimerChgAmberLedsColor(&timer0); }//*/

void initialisation () {
    cli();
    
    DDRA |= 0x00;
    DDRB |= 0x03;
    
    sei();
}

/**
 * @brief Fonction principale du programme.
 */
int main() {
    /*
    LED led(B0_B1, &timer0);
    led.setColor(LED_OFF);//*/
    const uint8_t POS_LED = B0_B1;
    
    can      sensors;
    uint16_t noirceur = 0x3ff;
    const uint8_t posSenseur   = PA0;
    // Valeurs à vérifier par des tests
    const uint16_t niveauBronze = 0x37f; // = 895 (= 1024 * 7/8 - 1)
    const uint16_t niveauBrule  = 0x17f; // = 383 (= 1024 * 3/8 - 1)
    
    initialisation();
    Uart::initialization();
    
    // LED verte par défaut
    //led.setColor(LED_GREEN);
    _MASK(*getPortPtr(POS_LED), LED_GREEN << getPinNumber(POS_LED), getMask(POS_LED));
    
    uint16_t ctr1 = 1023;
    for EVER {
        noirceur = sensors.lecture(posSenseur);
        if (noirceur <= niveauBrule) { 
            //if (led.getColor() != LED_GREEN) led.setColor(LED_GREEN);
            _MASK(*getPortPtr(POS_LED), LED_GREEN << getPinNumber(POS_LED), getMask(POS_LED));
        }
        else if (noirceur <= niveauBronze) {
            //if (led.getColor() != LED_AMBER) led.setColor(LED_AMBER);
            *getPortPtr(POS_LED) ^= getMask(POS_LED); // Inverse le sens du courant dans la led
        }
        else {
            //if (led.getColor() != LED_RED) led.setColor(LED_RED);
            _MASK(*getPortPtr(POS_LED), LED_RED << getPinNumber(POS_LED), getMask(POS_LED));
        }
        if (--ctr1 == 0) {
            ctr1 = 1023;
            Uart::transmission(noirceur >> 8);
            Uart::transmission(noirceur);
        }
    }
    
    return 0;
}
