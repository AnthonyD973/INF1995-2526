#include <lib.h>
#include <uart.h>
#include <ram.h>

#define L_OFF()   _MASK(PORTC,        0, _BV(PC4) | _BV(PC5))
#define L_RED()   _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5))
#define L_GREEN() _MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5))

int main() {
    _MASK(DDRC, _BV(PC4) | _BV(PC5), _BV(PC4) | _BV(PC5)); // pour la led
    uint16_t fileSize;
    
    UART::init(2400);
    RAM::init();
    
    L_GREEN();
    UART::receive((uint8_t*)&fileSize, 2); // On récupère la taille du fichier
    // Puis, on calcule l'addresse à laquelle le fichier vas être enregistré
    uint16_t addr = (-fileSize) - 2;
    
    // Ensuite, on écrit cette addresse à la toute fin pour pouvoir la récupéré plus tard.
    RAM::write(-2, (uint8_t*)&addr, 2);
    
    // Et enfin, on écrite la taille du fichier au début de l'espace réservé pour ce dernier.
    RAM::write(addr, (uint8_t*)&fileSize, 2);
    
    uint8_t buffer;
    for (uint16_t i = 2; i < fileSize; ++i) {
        L_RED();
        buffer = UART::receive();
        L_GREEN();
        RAM::write(addr + i, buffer);
    }
    
    L_OFF();
    
    return 0;
}
