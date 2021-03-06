/*
 * Classe permettant l'utilisation du piézo-électrique.
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

#include "buzzer.h"

/*  +-------------------------------------------------------------------------+
 *  | Relations entre la fréquence et la valeur du registre de comparaison:   |
 *  | f     = (F_CPU/Prescaler) * (1/OCR2A)                                   |
 *  | OCR2A = (F_CPU/Prescaler) * (1/f)                                       |
 *  +-------------------------------------------------------------------------+
 */

// NE PAS MODIFIER CES DEUX TABLEAUX

/**
 * @brief   Tableau de valeurs à mettre dans l'OCRNX pour générer une fréquence
 *      donnée.
 * 
 * L'indice 0 représente la valeur du OCRNX pour la note midi 24
 * (C-3, ~32.7 Hz)
 */
const uint8_t Buzzer::_FREQS[104]={
                                  239,225,213,201,190,179,169,159,150,142,134,127,
                                  119,113,106,100,95,89,84,80,75,71,67,63,
                                  239,225,213,201,190,179,169,159,150,142,134,127,
                                  119,113,106,100,95,89,84,80,75,71,67,63,
                                  239,225,213,201,190,179,169,159,150,142,134,127,
                                  119,113,106,100,95,89,84,80,75,71,67,63,
                                  60,56,53,50,47,45,42,40,38,36,34,253,
                                  239,225,213,201,190,179,169,159,150,142,134,127,
                                  119,113,106,100,95,89,84,80};
/**
 * @brief   Tableau contenant les index de prescaler des tables P_VAL[N] (de 0
 *      à 3) correspondant aux valeurs de chaque note MIDI.
 * 
 * L'indice 0 représente la valeur du prescale pour les notes midi 24
 * (les 4 bits de poids fort, C-3, ~32.7 Hz) et 25 (les 4 bits de poids faible).
 */
const uint8_t Buzzer::_PRESCALER[52]={ // Optimisation de la mémoire
                                  0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,
                                  0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,
                                  0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,
                                  0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,
                                  0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,
                                  0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,
                                  0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x1,0x1<<4|0x0,
                                  0x0<<4|0x0,0x0<<4|0x0,0x0<<4|0x0,0x0<<4|0x0,0x0<<4|0x0,0x0<<4|0x0,
                                  0x0<<4|0x0,0x0<<4|0x0,0x0<<4|0x0,0x0<<4|0x0};//*/
static const uint8_t P_VAL01[4] = {P01_CLK8, P01_CLK64, P01_CLK256, P01_CLK1024};
static const uint8_t  P_VAL2[4] = { P2_CLK8,  P2_CLK64,  P2_CLK256,  P2_CLK1024};

Timer* Buzzer::_TIMER = nullptr;

uint8_t Buzzer::_currTone = NO_TONE;

// +=-=-==-=-=+
// |  Buzzer  |
// +=-=-==-=-=+

void Buzzer::init(Timer* timer) {
    _TIMER = timer;
    _TIMER->setMode(_TIMER->is8BitClock() ? WGM02_CTC : WGM1_CTC1);
    _TIMER->setComNA(TOGGLE);
    _TIMER->setComNB(DISCONNECTED);
    _TIMER->setOcrNA(0x00);
    _TIMER->setTcntN(0x0000);
    
    clearTone();
}

void Buzzer::setTone(uint8_t midiTone) {
    if (midiTone >= 24 && midiTone < 128) {
        if (midiTone != _currTone) {
            _currTone = midiTone;
            _TIMER->setTcntN(0x0000);
            
            uint8_t index = midiTone - 24;
            bool shouldShift = ~index % 2;
            uint8_t prescale = (_PRESCALER[index/2] >> (shouldShift * 4)) & 0x0F;
            const uint8_t* prescaler = (_TIMER->isAsync() ? P_VAL2 : P_VAL01);
            _TIMER->setPrescale(prescaler[prescale]);
            _TIMER->setOcrNA(_FREQS[index]/2);
        }
    }
    else {
        clearTone();
        UART::transmitCStr("[Buzzer::setTone]: Error: Not supported Midi Tone (");
        UART::transmit((midiTone/100)|0x30);
        UART::transmit(((midiTone/10)%100)|0x30);
        UART::transmit((midiTone%10)|0x30);
        UART::transmitCStr(")\n");
    }
}

void Buzzer::clearTone() {
    if (_currTone != NO_TONE) {
        _currTone = NO_TONE;
        _TIMER->setPrescale(P01_NO_CLK);
    }
}
