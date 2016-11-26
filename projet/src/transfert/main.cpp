/*
 * Fichier d'entrée du programme permettant le chargement de données dans la
 * mémoire du robot.
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Emir Khaled Belhaddad, Anthony Dentinger,
 * Gergi Younis et Vincent Dandenault
 * 2016
 *
 * Code qui n'est sous aucune license.
 *
 */

#include "lib.h"
#include "uart.h"
#include "ram.h"
#include "led.h"

int main() {
    uint16_t size = 0;
    uint8_t  buffer = 0;
    
    DDRA = DDRB = DDRC = 0xff;
    
    UART::init(2400);
    RAM::init();
    
    PORTB = LED_RED;
    
    for (uint8_t i = 0; i < 2; ++i) {
        buffer = UART::receive();
        size += (buffer << (8*(i)));
    }
    
    RAM::write(0, (uint8_t*)&size, 2);
    
    PORTB = LED_GREEN;
    
    for (uint16_t i = 2; i < size; ++i) {
        PORTB = LED_RED;
        buffer = UART::receive();
        PORTB = LED_GREEN;
        RAM::write(i, buffer);
    }
    
    for EVER {
        PORTB = LED_OFF;
    }
    
    return 0;
}
