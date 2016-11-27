#ifndef PLAYER_H
#define PLAYER_H // Include Guard

#include <buzzer.h>
#include <ram.h>
#include <uart.h>

class Player {
    
public:
    static void init();
    static void play();
    
private:
    static uint16_t songFileAddr;
    static uint16_t nNotes;
    static uint16_t begNotesAddr;
};

#endif // PLAYER_H
