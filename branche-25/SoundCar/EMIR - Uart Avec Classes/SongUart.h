#ifndef UART_H_
#define UART_H_ // INCLUDE GUARD

#include "Uart.h"
#include "memoire_24.h"
#include "SongMemory.h"

enum LED {
    OFF, GREEN, RED, AMBRE=0xff
};

const uint16_t BUFFER_SIZE = 1024;
const uint8_t  N_SONGS_MAX = 32;

volatile uint16_t songsAddr[N_SONGS_MAX]; // Tableau contenant l'addresse des
                                          // chansons dans la mémoire
volatile uint16_t nSongs = 0;             // Le nombre de chansons
         uint8_t  buffer[BUFFER_SIZE];    // Tampon de réception


class SongUart : public Uart {
public:
  void transferSongsToMemory (SongMemory&);
};


void flushBuffToRAM(Memoire24CXXX& ram, uint8_t* buffer,
                    const uint16_t& currAddr, uint16_t& lastAddr);



/**
 * @brief Cette fonction vide 1 octet du tampon de réception de l'UART.
 */
void viderTamponDeReceptionUART() {
	volatile unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

/**
 * @brief Cette fonction a pour seul but de récupérer les données des chansons
 *        et de les transférer sur la RAM tout en préservant l'addresse où se
 *        trouve chaque chanson dans la mémoire.
 */
void SongUart::transferSongsToMemory(Memoire24CXXX& ram) {
    cli();
    
    PORTB = GREEN;
    
    uint8_t fileID[6];
    for (uint8_t i = 0; i < 6; ++i)
        fileID[i] = reception();
    if (fileID[0] != 'E' || fileID[1] != 'M' ||
        fileID[2] != 'B' || fileID[3] != 'E' ||
        fileID[4] != 'N' || fileID[5] != 'D')
        return;
    
    nSongs = 0;
    for (uint8_t i = 0; i < 2; ++i)
        nSongs |= (uint16_t(reception()) << (8*i));
    
    uint16_t songsAddr[nSongs]; // Contient l'addresse de chaque chanson
    uint16_t currAddr = 0x00, // L'address mémoire dans la RAM
             buffer16 = 0; // Tampon pour les données de 16 bits
    uint8_t  buffer8 = 0;  // Tampon pour les données de 8 bits
    uint16_t lastAddr = 0; // L'addresse (+1) à laquelle on a écrit dans la RAM
                           // pour la dernière fois.
    for (uint16_t i = 0; i < nSongs; ++i) {
        songsAddr[i] = currAddr;
        
        PORTB = GREEN;
        
        buffer8 = reception(); // Récupération du BPS
        buffer[currAddr++ - lastAddr] = buffer8;
        flushBuffToRAM(ram, buffer, currAddr, lastAddr);
        // On a pas besoin d'attendre 5 ms car on ne vas pas lire dans la
        // RAM d'ici la fin de la fonction.
        
        buffer16 = 0;
        for(uint8_t j = 0; j < 2; ++j) { // Récupération du nombre de notes
            buffer16 |= (uint16_t(reception()) << (8*j));
        }
        for (uint16_t j = 0; j < 2; ++j) {
            buffer[currAddr - lastAddr] = *((uint8_t*)(&buffer16) + j);
        }
        currAddr += 2;
        flushBuffToRAM(ram, buffer, currAddr, lastAddr);
        
        PORTB = RED;
        for (uint16_t j = 0; j < buffer16; ++j) {
            buffer[currAddr++ - lastAddr] = reception();
            flushBuffToRAM(ram, buffer, currAddr, lastAddr);
        }
    }
    
    flushBuffToRAM(ram, buffer, currAddr, lastAddr);
    _delay_ms(5);
    
    transmission(48+nSongs);
    
    PORTB = 0x0;
    
    sei();
}

/**
 * @brief Cette fonction vide le tampon de lecture dans la RAM seulement s'il
 *        a atteint sa taille maximum.
 */
void flushBuffToRAM(Memoire24CXXX& ram, uint8_t* buffer,
                    const uint16_t& currAddr, uint16_t& lastAddr) {
    if (currAddr - lastAddr >= BUFFER_SIZE) {
        ram.ecriture(lastAddr, buffer, currAddr - lastAddr);
        lastAddr = currAddr;
        PORTB = GREEN;
    }
}

#endif // END OF INCLUDE GUARD
