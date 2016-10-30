#include "Song.h"

volatile uint16_t* Song::songsAddr;
volatile uint16_t  Song::nSongs = 0;
uint8_t Song::buffer[BUFFER_SIZE];
const uint16_t Song::freqs[13]{0,523,554,587,622,659,698,740,784,830,880,932,988};

Song::Song() : bps(1), nTones(1) {
    tones[0] = 0;
}

Song::Song(const Tone* tones_, const uint16_t& nTones_, const uint8_t& bps_) : bps(bps_), nTones(nTones_) {
    uint16_t k = (nTones > N_TONES_MAX) ? N_TONES_MAX : nTones;
    for (uint16_t i = 0; i < k; ++i)
        tones[i] = tones_[i];
}

Song::~Song() {
}

/**
 * \brief Cette fonction a pour seul but de récupérer les données des chansons
 *        et de les transférer sur la RAM tout en préservant l'addresse où se
 *        trouve chaque chanson dans la mémoire.
 */
void Song::saveToMemory(Memoire24CXXX& ram) {
    uint8_t int0mask = EIMSK;
    EIMSK &= ~_BV(INT0);
    
    uint16_t currAddr = 0x00, // L'addresse mémoire dans la RAM
             buffer16 = 0; // Tampon pour les données de 16 bits
    uint16_t lastAddr = currAddr; // L'addresse (+1) à laquelle on a écrit dans
                           // la RAM pour la dernière fois.
    PORTB = GREEN;
    
    uint8_t fileID[6];
    for (uint8_t i = 0; i < 6; ++i) {
        PORTB = GREEN;
        fileID[i] = UART::receive();
    }
    PORTB = RED;
    if (fileID[0] != 'E' || fileID[1] != 'M' ||
        fileID[2] != 'B' || fileID[3] != 'E' ||
        fileID[4] != 'N' || fileID[5] != 'D')
        return;
    for (uint8_t i = 0; i < 6; i++) {
        buffer[currAddr++ - lastAddr] = fileID[i];
        flushBuffToRAM(ram, buffer, currAddr, lastAddr);
    }
    
    nSongs = 0;
    for (uint8_t i = 0; i < 2; ++i) {
        nSongs |= (uint16_t(UART::receive()) << (8*i));
        PORTB = RED;
    }
    for (uint8_t i = 0; i < 2; ++i) {
        buffer[currAddr++ - lastAddr] = ((uint8_t*)&nSongs)[i];
        flushBuffToRAM(ram, buffer, currAddr, lastAddr);
    }
    
    uint16_t songsAddr2[nSongs]; // Contient l'addresse de chaque chanson
    songsAddr = &songsAddr2[0];
    for (uint16_t i = 0; i < nSongs; ++i) {
        songsAddr[i] = currAddr;
        
        PORTB = GREEN;
        
        // Récupération du BPS
        buffer[currAddr++ - lastAddr] = UART::receive();
        PORTB = RED;
        flushBuffToRAM(ram, buffer, currAddr, lastAddr);
        // On a pas besoin d'attendre 5 ms car on ne vas pas lire dans la
        // RAM d'ici la fin de la fonction.
        
        buffer16 = 0;
        for(uint8_t j = 0; j < 2; ++j) { // Récupération du nombre de notes
            buffer16 |= (uint16_t(UART::receive()) << (8*j));
            PORTB = RED;
            flushBuffToRAM(ram, buffer, currAddr, lastAddr);
        }
        for (uint16_t j = 0; j < 2; ++j) {
            buffer[currAddr++ - lastAddr] = *((uint8_t*)(&buffer16) + j);
            flushBuffToRAM(ram, buffer, currAddr, lastAddr);
        }
        
        PORTB = RED;
        for (uint16_t j = 0; j < buffer16; ++j) {
            buffer[currAddr++ - lastAddr] = UART::receive();
            PORTB = RED;
            flushBuffToRAM(ram, buffer, currAddr, lastAddr);
        }
    }
    
    // Flush forcé dans la RAM
    if (currAddr - lastAddr > 0) {// ...seulement s'il y a quelque chose à vider
        ram.ecriture(lastAddr, buffer, currAddr - lastAddr);
        lastAddr = currAddr;
        PORTB = GREEN;
    }
    
    for (;;) {
        PORTB ^= 0x3;
        if (UART::_rec_size() > 0) {
            UART::_rec_pop();
            break;
        }
        UART::transmit(nSongs);
    }
    
    PORTB = 0x0;
    
    EIMSK = int0mask;
    return;
}

/**
 * \brief Cette fonction vide le tampon de lecture dans la RAM seulement s'il
 *        a atteint sa taille maximum.
 */
void Song::flushBuffToRAM(Memoire24CXXX& ram, uint8_t* buffer,
                    const uint16_t& currAddr, uint16_t& lastAddr) {
    if (currAddr - lastAddr >= BUFFER_SIZE) {
        ram.ecriture(lastAddr, buffer, currAddr - lastAddr);
        lastAddr = currAddr;
        PORTB = GREEN;
        _delay_ms(5);
        for (;;) {
            if (UART::_rec_size() > 0) break;
            UART::transmit(currAddr);
        }
    }
}

bool Song::loadFromMemory(Memoire24CXXX& ram, uint16_t addr) {
    cli();
    
    uint16_t currAddr = addr, // L'addresse mémoire dans la RAM
             buffer16 = 0; // Tampon pour les données de 16 bits
    PORTB = GREEN;
    
    uint8_t fileID[6];
    for (uint8_t i = 0; i < 6; ++i)
        ram.lecture(currAddr++, &fileID[i]);
    PORTB = RED;
    if (fileID[0] != 'E' || fileID[1] != 'M' ||
        fileID[2] != 'B' || fileID[3] != 'E' ||
        fileID[4] != 'N' || fileID[5] != 'D') {
        return false;
    }
    
    nSongs = 0;
    for (uint8_t i = 0; i < 2; ++i) {
        ram.lecture(currAddr++, (((uint8_t*)&nSongs)+i));
        PORTB = RED;
    }
    
    uint16_t songsAddr2[nSongs]; // Contient l'addresse de chaque chanson
    songsAddr = &songsAddr2[0];
    for (uint16_t i = 0; i < nSongs; ++i) {
        songsAddr[i] = currAddr;
        
        PORTB = GREEN;
        
        // Récupération du BPS
        currAddr++;
        PORTB = RED;
        
        buffer16 = 0;
        for(uint8_t j = 0; j < 2; ++j) { // Récupération du nombre de notes
            ram.lecture(currAddr++, (((uint8_t*)&buffer16)+j));
        }
        
        PORTB = RED;
        for (uint16_t j = 0; j < buffer16; ++j) {
            currAddr++;
            PORTB = RED;
        }
    }
    
    PORTB = GREEN;
    _delay_ms(200);
    
    PORTB = 0x0;
    
    sei();
    return true;
}

void Song::getSong(const uint16_t& songNbr, volatile Song& song,
                   Memoire24CXXX& ram) {
    uint8_t buff = 0;
    
    _delay_ms(5);
    ram.lecture(songsAddr[songNbr], &buff);
    song.bps = buff;
    ram.lecture(songsAddr[songNbr]+1, &buff);
    song.nTones = buff;
    ram.lecture(songsAddr[songNbr]+2, &buff);
    song.nTones |= (uint16_t(buff) << 8);
    for (uint16_t i = 0; i < song.nTones; ++i)
        ram.lecture(songsAddr[songNbr]+3+i, (uint8_t*)(song.tones + i));
    _delay_ms(5);
}

