#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "led.h"
#include "engine.h"
#include "timer.h"
#include "defaultISR.h"
#include "ram.h"
#include "uart.h" // Utile pour le debug

#define EVER (;;)

Timer0 timer0(P01_CLK8);
Timer1 timer1(P01_CLK8);

ISR(TIMER0_OVF_vect) { switchAmberLedsColor(&timer0); }
ISR(TIMER1_OVF_vect) { switchAmberLedsColor(&timer1); }
ISR(TIMER0_COMPA_vect) { }

void testerSetMode(Engine& engL, Engine& engR) {
    engL.setMode(ENG_FORWARD);
    engR.setMode(ENG_FORWARD);
    _delay_ms(5000.0); // Les deux roues devraient tourner à 100% pendant 5s.
    
    engL.setMode(ENG_OFF);
    engR.setMode(ENG_OFF);
    _delay_ms(1000.0); // Pour éviter d'abîmer les moteurs en changeant bursquement de direction. 1s.
    
    engL.setMode(ENG_BACKWARD);
    engR.setMode(ENG_BACKWARD);
    _delay_ms(5000.0); // Les deux roues devraient tourner en sens inverse à 100% pendant 5s.
    
    engL.setMode(ENG_OFF);
    engR.setMode(ENG_OFF);
    _delay_ms(1000.0); // Pour éviter d'abîmer les moteurs en changeant bursquement de direction. 1s.
    
    engL.setMode(ENG_BACKWARD);
    engR.setMode(ENG_FORWARD);
    _delay_ms(5000.0); // Le robot fait une pirouette pendant 5s.
    
    engL.setMode(ENG_OFF);
    engR.setMode(ENG_OFF);
    _delay_ms(1000.0); // Pour éviter d'abîmer les moteurs en changeant bursquement de direction. 1s.
    
    
    engL.setMode(ENG_FORWARD);
    engR.setMode(ENG_BACKWARD);
    _delay_ms(5000.0); // Le robot fait la pirouette inverse pendant 5s.
    
    for (uint8_t i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            engL.setMode(ENG_FORWARD);
            engR.setMode(ENG_FORWARD);
        }
        else {
            engL.setMode(ENG_BACKWARD);
            engR.setMode(ENG_BACKWARD);
        }
        _delay_ms(1000.0); // Le robot fait des va-et-viens chaque seconde pendant 10s.
    
        engL.setMode(ENG_OFF);
        engR.setMode(ENG_OFF);
        _delay_ms(500.0); // Pour éviter d'abîmer les moteurs en changeant bursquement de direction. Total : 5s.
    }
    
}

void testerPower(Engine& engL, Engine& engR) {
     UART::transmitCStr("\n---OFF---");
     engL.setPower(ENG_OFF, 0x00FF);
     engR.setPower(ENG_OFF, 0x00FF);
     UART::transmitBin(PORTB); UART::transmit('\n');
     _delay_ms(5000.0); // Les moteurs devraient être éteints pendant 5s.
 
 
 
    UART::transmitCStr("\n---FORW---\n");
    engL.setPower(ENG_FORWARD, 0x00FF);
    engR.setPower(ENG_FORWARD, 0x00FF);
    UART::transmitCStr("PORTB:"); UART::transmitBin(PORTB); UART::transmit('\n');
    _delay_ms(5000.0); // Les moteurs devraient tourner à 100% pendant 5s.
 
    
    
    UART::transmitCStr("\n---OFF---\n");
    engL.setPower(ENG_OFF, 0x00FF);
    engR.setPower(ENG_OFF, 0x00FF);
    UART::transmitCStr("PORTB:"); UART::transmitBin(PORTB); UART::transmit('\n');
    _delay_ms(1000.0); // Pour éviter d'abîmer les moteurs en changeant bursquement de direction. 1s.
    
    UART::transmitCStr("\n---BACK---\n");
    engL.setPower(ENG_BACKWARD, 0x00FF);
    engR.setPower(ENG_BACKWARD, 0x00FF);
    UART::transmitCStr("PORTB:"); UART::transmitBin(PORTB); UART::transmit('\n');
    _delay_ms(5000.0); // Les moteurs devraient tourner en sens inverse à 100% pendant 5s.
 
    UART::transmitCStr("\n---OFF---\n");
    engL.setPower(ENG_OFF, 0x00FF);
    engR.setPower(ENG_OFF, 0x00FF);
    UART::transmitCStr("PORTB:"); UART::transmitBin(PORTB); UART::transmit('\n');
    _delay_ms(1000.0); // Pour éviter d'abîmer les moteurs en changeant bursquement de direction. 1s.
    
    
    
    UART::transmitCStr("\n---FORW GRADUEL---\n\n");
    for (uint16_t i = 0; i < 0x00FF; ++i) {
        engL.setPower(ENG_FORWARD, i);
        engR.setPower(ENG_FORWARD, i);
        _delay_ms(39.0625); // Le moteurs devraient aller graduellement plus vite, de 0% à 100%, en 10s.
    }
    
    
    UART::transmitCStr("\n---OFF---\n\n");
    engL.setPower(ENG_OFF, 0x00FF);
    engR.setPower(ENG_OFF, 0x00FF);
    _delay_ms(5000.0); // Les moteurs devraient être éteints pendant 5s.
    
    
    UART::transmitCStr("\n---BACK GRADUEL---\n\n");
    for (uint16_t i = 0; i < 0x00FF; ++i) {
        engL.setPower(ENG_BACKWARD, i);
        engR.setPower(ENG_BACKWARD, i);
        _delay_ms(39.0625); // Le moteurs devraient aller graduellement plus vite en sens inverse, de 0% à 100%, en 10s.
    }
    
    UART::transmitCStr("\n---INVALID SET_POWER---\n\n");
    engL.setPower(12, 0); // Le PC devrait recevoir la chaîne "Engine::power : mauvaise valeur de 'mode'." et le moteur gauche devrait s'éteindre. 5s.
    _delay_ms(5000.0);
    
    
    UART::transmitCStr("\n---OFF---\n\n");
    engL.setPower(ENG_OFF, 0x00FF);
    engR.setPower(ENG_OFF, 0x00FF);
}

/**
 * @brief Fonction principale du programme.
 */
int main() {
    DDRA = DDRB = DDRC = DDRD = 0xFF;
    
    UART::init(2400);
    UART::transmitCStr("test l. 117\n");
    
    RAM::init();
    
    // timer0.modeNormal(0x7f, 0x00);
    // timer0.modePhaseCorrectPWM(0x7f, 0x00);
    // À ce propos, je crois qu'une fonction 'setMode(Mode mode)' serait préférable.
    
    LED led(B0_B1, &timer0);
    
    Engine engL(T0CA);
    Engine engR(T0CB);
    
    
    UART::transmitCStr("Setter LED vert.\n");
    led.setColor(LED_GREEN);
    //UART::transmitCStr("testerSetMode\n");
    //testerSetMode(engL, engR); // Test de 38s.
    
     // Mettre la LED rouge pour signaler la fin du test.
    UART::transmitCStr("Setter LED rouge.\n");
    led.setColor(LED_RED);
    
    UART::transmitCStr("testerPower\n");
    testerPower(engL, engR); // Test de 47s.
    
    
     // Mettre la LED verte pour signaler la fin des tests.
    UART::transmitCStr("Setter LED vert.\n");
    led.setColor(LED_GREEN);
    UART::transmitCStr("PORTB FINAL:"); UART::transmitBin(PORTB); UART::transmit('\n');
    
    
    for EVER {
        // Busy wait
    }
    
    return 0;
}
