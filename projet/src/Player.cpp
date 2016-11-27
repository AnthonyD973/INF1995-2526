#include "Player.h"

uint16_t Player::songFileAddr = 0;
uint16_t Player::nNotes = 0;
uint16_t Player::begNotesAddr = 0;

void Player::init() {
    RAM::read(-2, (uint8_t*)&songFileAddr, 2);
    RAM::read(songFileAddr + 2, (uint8_t*)&nNotes, 2);
    begNotesAddr = songFileAddr + 4;
}

void Player::play() {
    uint8_t duration, tone;
    
    for (uint16_t i = 0; i < nNotes; ++i){
        RAM::read(begNotesAddr + i*2, &duration);
        RAM::read(begNotesAddr + i*2 + 1, &tone);
        
        Buzzer::setTone(tone);
        
        for (uint8_t j = 0; j < (1 << (duration-1)); ++j) {
            _delay_ms(31.25); // 1000.0ms / 32
        }
    }
    Buzzer::clearTone();
}
