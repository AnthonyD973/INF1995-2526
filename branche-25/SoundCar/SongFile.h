#ifndef SONGFILE_H_
#define SONGFILE_H_ // Include Guard

#ifndef F_CPU
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#endif
#include "Song.h"

const uint8_t N_SONGS_MAX = 12;

class SongFile {
public:
    SongFile(const uint16_t& nSongs_ = 0);
    ~SongFile();
    
    friend int main(void);
    
private:
    uint16_t nSongs;
    Song*    songs;
    
};

#endif // Include Guard
