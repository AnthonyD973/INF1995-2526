#include "buzzer.h"

/*  +-------------------------------------------------------------------------+
 *  | Relations entre la fréquence et la valeur du registre de comparaison:   |
 *  | f     = (F_CPU/Prescaler) * (1/OCR2A)                                   |
 *  | OCR2A = (F_CPU/Prescaler) * (1/f)                                       |
 *  +-------------------------------------------------------------------------+
 */

// NE PAS MODIFIER CES DEUX TABLEAUX

// L'index 0 représente la fréquence pour la note midi 24 (C -3, ~32.7 Hz)
const uint8_t Buzzer::_FREQS[104]={
                                  239/4,225/4,213/4,201/4,190/4,179/4,169/4,159/4,150/4,142/4,134/4,127/4,
                                  119/4,113/4,106/4,100/4,95/4,89/4,84/4,80/4,75/4,71/4,67/4,63/4,
                                  239/4,225/4,213/4,201/4,190/4,179/4,169/4,159/4,150/4,142/4,134/4,127/4,
                                  119/4,113/4,106/4,100/4,95/4,89/4,84/4,80/4,75/4,71/4,67/4,63/4,
                                  239/4,225/4,213/4,201/4,190/4,179/4,169/4,159/4,150/4,142/4,134/4,127/4,
                                  119/4,113/4,106/4,100/4,95/4,89/4,84/4,80/4,75/4,71/4,67/4,63/4,
                                  60/4,56/4,53/4,50/4,47/4,45/4,42/4,40/4,38/4,36/4,34/4,253/4,
                                  239/4,225/4,213/4,201/4,190/4,179/4,169/4,159/4,150/4,142/4,134/4,127/4,
                                  119/4,113/4,106/4,100/4,95/4,89/4,84/4,80/4};//*
const uint8_t Buzzer::_PRESCALER[52]={ // Optimisation de la mémoire
                                  0x5<<4|0x5,0x5<<4|0x5,0x5<<4|0x5,0x5<<4|0x5,0x5<<4|0x5,0x5<<4|0x5,
                                  0x5<<4|0x5,0x5<<4|0x5,0x5<<4|0x5,0x5<<4|0x5,0x5<<4|0x5,0x5<<4|0x5,
                                  0x4<<4|0x4,0x4<<4|0x4,0x4<<4|0x4,0x4<<4|0x4,0x4<<4|0x4,0x4<<4|0x4,
                                  0x4<<4|0x4,0x4<<4|0x4,0x4<<4|0x4,0x4<<4|0x4,0x4<<4|0x4,0x4<<4|0x4,
                                  0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,
                                  0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,
                                  0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x3,0x3<<4|0x2,
                                  0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,
                                  0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2,0x2<<4|0x2};//*/

Timer* Buzzer::_TIMER = 0;

// +=-=-==-=-=+
// |  Buzzer  |
// +=-=-==-=-=+

void Buzzer::init(Timer* timer) {
    _TIMER = timer;
    _TIMER->setPrescale(P01_CLK8);
    _TIMER->setMode(_TIMER->is8BitClock() ? WGM0_PWM_PC2 : WGM1_PWM_PFC2);
    _TIMER->setComNA(TOGGLE);
    _TIMER->setComNB(DISCONNECTED);
    _TIMER->setOcrNA(0x00);
    _TIMER->setTcntN(0x0000);
    
    clearTone();
}

void Buzzer::setTone(uint8_t midiTone) {
    if (midiTone >= 24 && midiTone < 128) {
        _TIMER->setTcntN(0x0000);
        _TIMER->setPrescale(0x0F & (_PRESCALER[(midiTone - 24) >> 1] >> (((~(midiTone - 24))&0x01) << 2)));
        _TIMER->setOcrNA(_FREQS[midiTone - 24]);//*/
    }
    else {
        clearTone();//*
        UART::transmitCStr("[Buzzer::setTone]: Error: Not supported Midi Tone (");
        UART::transmit((midiTone/100)|0x30);
        UART::transmit(((midiTone/10)%100)|0x30);
        UART::transmit((midiTone%10)|0x30);
        UART::transmitCStr(")\n");//*/
    }
}

void Buzzer::clearTone() {
    _TIMER->setPrescale(P01_NO_CLK);
}
