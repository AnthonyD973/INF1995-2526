#ifndef SONG_H_
#define SONG_H_ // Include Guard

#ifndef F_CPU
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#endif
#include "memoire_24.h"
#include "uart.h"

enum LED {
    OFF, GREEN, RED, AMBRE=0xff
};
typedef uint8_t Tone;
const static uint16_t N_TONES_MAX = 1024;
const uint16_t BUFFER_SIZE = 128;

class SongFile;

int main(void);

class Song {
public:
    static volatile uint16_t* songsAddr; // Tableau contenant l'addresse des
                                         // chansons dans la mémoire
    static volatile uint16_t  nSongs;    // Le nombre de chansons
    static const uint16_t freqs[13];
    
    static void saveToMemory (Memoire24CXXX&);
    static bool loadFromMemory(Memoire24CXXX& ram, uint16_t addr);
    static void getSong(const uint16_t& songNbr, volatile Song& song,
                        Memoire24CXXX& ram);

    Song();
    Song(const Tone* tones_, const uint16_t& nTones_, const uint8_t& bps_ = 4);
    ~Song();
    
    friend int main(void);
    
private:
    static uint8_t buffer[BUFFER_SIZE];  // Tampon de réception
    
    static void flushBuffToRAM(Memoire24CXXX& ram, uint8_t* buffer,
                               const uint16_t& currAddr, uint16_t& lastAddr);
    
    uint8_t  bps;
    uint16_t nTones;
    Tone     tones[N_TONES_MAX];
    
    friend class SongFile;
};

#endif // Include Guard
