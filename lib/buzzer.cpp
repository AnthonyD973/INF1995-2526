#include "buzzer.h"

/*  +-------------------------------------------------------------------------+
 *  | Relations entre la fréquence et la valeur du registre de comparaison:   |
 *  | f     = (F_CPU/Prescaler) * (1/OCR2A)                                   |
 *  | OCR2A = (F_CPU/Prescaler) * (1/f)                                       |
 *  +-------------------------------------------------------------------------+
 */

// NE PAS MODIFIER CES DEUX TABLEAUX

// L'index 0 représente la fréquence pour la note midi 24 (C -3, ~32.7 Hz)
const uint16_t Buzzer::_FREQS[104]={
                                  239*128/4,225*128/4,213*128/4,201*128/4,190*128/4,179*128/4,169*128/4,159*128/4,150*128/4,142*128/4,134*128/4,127*128/4,
                                  119*128/4,113*128/4,106*128/4,100*128/4,95*128/4,89*128/4,84*128/4,80*128/4,75*128/4,71*128/4,67*128/4,63*128/4,
                                  239*32/4,225*32/4,213*32/4,201*32/4,190*32/4,179*32/4,169*32/4,159*32/4,150*32/4,142*32/4,134*32/4,127*32/4,
                                  119*32/4,113*32/4,106*32/4,100*32/4,95*32/4,89*32/4,84*32/4,80*32/4,75*32/4,71*32/4,67*32/4,63*32/4,
                                  239*8/4,225*8/4,213*8/4,201*8/4,190*8/4,179*8/4,169*8/4,159*8/4,150*8/4,142*8/4,134*8/4,127*8/4,
                                  119*8/4,113*8/4,106*8/4,100*8/4,95*8/4,89*8/4,84*8/4,80*8/4,75*8/4,71*8/4,67*8/4,63*8/4,
                                  60*8/4,56*8/4,53*8/4,50*8/4,47*8/4,45*8/4,42*8/4,40*8/4,38*8/4,36*8/4,34*8/4,253/4,
                                  239/4,225/4,213/4,201/4,190/4,179/4,169/4,159/4,150/4,142/4,134/4,127/4,
                                  119/4,113/4,106/4,100/4,95/4,89/4,84/4,80/4};/*
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

// +=-=-==-=-=+
// |  Buzzer  |
// +=-=-==-=-=+

void Buzzer::init() {
    DDRD |= _BV(PD4) | _BV(PD5);
    timer1.setPrescale(P01_CLK8);
    timer1.setMode(WGM1_PWM_PFC2);
    timer1.setComNA(TOGGLE);
    timer1.setOcrNA(0x00);
    TCNT1 = 0x0000;
    
    clearTone();
}

void Buzzer::setTone(uint8_t midiTone) {
    if (midiTone >= 24 && midiTone < 128) {
        TCNT1 = 0x0000;
        //timer1.setPrescale(0x0F & (_PRESCALER[(midiTone - 24)>>2] >> (((~(midiTone - 24))&0x01) << 2)));
        timer1.setPrescale(P01_CLK8);
        timer1.setOcrNA(_FREQS[midiTone - 24]);//*/
    }
    else {
        clearTone();/*
        UART::transmitCStr("[Buzzer::setTone]: Error: Not supported Midi Tone (");
        UART::transmit((midiTone/100)|0x30);
        UART::transmit(((midiTone/10)%100)|0x30);
        UART::transmit((midiTone%10)|0x30);
        UART::transmitCStr(")\n");//*/
    }
}

void Buzzer::clearTone() {
    timer1.setMode(WGM1_PWM_PFC2);
    timer1.setPrescale(P01_NO_CLK);
    timer1.setOcrNA(0x00);//*/
}
