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

#include <lib.h>
#include <uart.h>
#include <ram.h>
#include <led.h>

int main() {
    // Initialisation.
    uint16_t size = 0;
    uint8_t  buffer = 0;
    
    LED led(C4_C5, nullptr);
    
    DDRA = DDRB = DDRC = 0xff;
    
    UART::init(2400);
    RAM::init();
    
    
    // Recevoir taille à écrire en mémoire.
    led.setColor(LED_RED);
    
    UART::receive((uint8_t*)&size, 2);
    RAM::write(0, (uint8_t*)&size, 2);
    
    led.setColor(LED_GREEN);
    
    
    // Recevoir données.
    for (uint16_t i = 2; i < size; ++i) {
        led.setColor(LED_RED);
        buffer = UART::receive();
        led.setColor(LED_GREEN);
        RAM::write(i, buffer);
    }
    
    
    // Terminé.
    for EVER {
        led.setColor(LED_OFF);
    }
    
    return 0;
}
