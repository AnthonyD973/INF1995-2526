#ifndef PIN_POSITION_H // PIN_POSITION_H
#define PIN_POSITION_H

#include "lib.h"


typedef uint8_t PinPosition;
//const PinPosition
#define    A0_A1 0
#define    A2_A3 2
#define    A4_A5 4
#define    A6_A7 6
#define    B0_B1 8
#define    B2_B3 10
#define    B4_B5 12
#define    B6_B7 14
#define    C0_C1 16
#define    C2_C3 18
#define    C4_C5 20
#define    C6_C7 22
#define    D0_D1 24
#define    D2_D3 26
#define    D4_D5 28
#define    D6_D7 30

volatile uint8_t* getPortPtr(PinPosition pinPos);
volatile uint8_t getPinVal(PinPosition pinPos);
inline uint8_t getPinNumber(PinPosition pinPos) { return pinPos % 8; }
inline uint8_t getMask(PinPosition pinPos) { return 0x3 << getPinNumber(pinPos); }
inline uint16_t getShiftedPos(PinPosition pinPos) { return 1 << (pinPos/2); }

#endif // PIN_POSITION_H
