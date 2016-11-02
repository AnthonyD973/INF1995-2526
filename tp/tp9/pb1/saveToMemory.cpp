#include "saveToMemory.h"

const uint16_t BUFFER_SIZE = 128;
uint8_t buffer[BUFFER_SIZE];

void flushBuffToRAM(uint8_t* buffer,
                    const uint16_t currAddr, uint16_t lastAddr) {
    if (currAddr - lastAddr >= BUFFER_SIZE) {
        RAM::write(lastAddr, buffer, currAddr - lastAddr);
        lastAddr = currAddr;
        _delay_ms(5);
        for (;;) {
            if (UART::_rec_size() > 0) break;
            UART::transmit(currAddr);
        }
    }
}

void saveToMemory (void) {
    // On empêche les interruption du boutton-pousoire
    uint8_t int0mask = EIMSK;
    EIMSK &= ~_BV(INT0);
    
    uint16_t currAddr = 0x00; // L'addresse mémoire dans la RAM (compteur)
    uint16_t lastAddr = currAddr; // L'addresse (+1) à laquelle on a écrit dans
                           // la RAM pour la dernière fois.
    uint16_t fileLen = 0;  // La taille du fichier à recevoire.
    
    // Récupération de la taille du fichier
    for (uint8_t i = 0; i < 2; ++i) {
        fileLen |= (uint16_t(UART::receive()) << (8*i));
    }
    // Tamporisation de la donnée
    for (uint8_t i = 0; i < 2; ++i) {
        buffer[currAddr++ - lastAddr] = ((uint8_t*)&fileLen)[i];
        flushBuffToRAM(buffer, currAddr, lastAddr);
    }
    
    // Récupération du reste des données
    for (uint16_t i = 0; i < fileLen; ++i) {
        // Tamporisation de la donnée
        buffer[currAddr++ - lastAddr] = UART::receive();
        flushBuffToRAM(buffer, currAddr, lastAddr);
    }
    
    // Flush forcé dans la RAM
    if (currAddr - lastAddr > 0) {// ...seulement s'il y a quelque chose à vider
        RAM::write(lastAddr, buffer, currAddr - lastAddr);
        lastAddr = currAddr;
        _delay_ms(5);
    }
    
    // Puis on restore les Interruptions
    EIMSK = int0mask;
    return;
}
