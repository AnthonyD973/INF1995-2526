#ifndef PIN_POSITION_H // PIN_POSITION_H
#define PIN_POSITION_H

#include "lib.h"

typedef uint8_t PinPosition;
const PinPosition
    A0_A1 = 0,
    A2_A3 = 2,
    A4_A5 = 4,
    A6_A7 = 6,
    B0_B1 = 8,
    B2_B3 = 10,
    B4_B5 = 12,
    B6_B7 = 14,
    C0_C1 = 16,
    C2_C3 = 18,
    C4_C5 = 20,
    C6_C7 = 22,
    D0_D1 = 24,
    D2_D3 = 26,
    D4_D5 = 28,
    D6_D7 = 30;

volatile uint8_t* getPortPtr(PinPosition pinPos);
volatile uint8_t getPinVal(PinPosition pinPos);
inline uint8_t getPinNumber(PinPosition pinPos) { return pinPos % 8; }
inline uint8_t getMask(PinPosition pinPos) { return 0x3 << getPinNumber(pinPos); }
inline uint16_t getShiftedPos(PinPosition pinPos) { return 1 << (pinPos/2); }

#endif // PIN_POSITION_H
