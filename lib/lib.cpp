#include "lib.h"

// +-----------------------------+
// | FONCTIONS UTILISABLES DANS  |
// | LES ROUTINES D'INTERRUPTION |
// +-----------------------------+

void switchAmberLedsColor(Timer* timer) {
    // Test fréquemment vrai, alors effectué au début.
    if (timer->_nAmberLeds == 0) {
        return;
    }
    
    uint16_t curAmberLeds = timer->_amberLeds;
    uint8_t nAmberLedsLeft = timer->_nAmberLeds;
    volatile uint8_t* curPort;
    for (PinPosition portBeginNum = 0; portBeginNum < 32 && nAmberLedsLeft != 0; portBeginNum += 8) {
        curPort = getPortPtr(portBeginNum);
        uint8_t amberLedsMask = 0;
        
        for (uint8_t pinNumberOnPortDiv2 = 0; pinNumberOnPortDiv2 < 4 && nAmberLedsLeft != 0; ++pinNumberOnPortDiv2) {
            bool isThisLedAmber = (curAmberLeds & 1) == 1;
            if (isThisLedAmber) {
                --nAmberLedsLeft;
                amberLedsMask |= getMask(portBeginNum + 2*pinNumberOnPortDiv2);
            }
            curAmberLeds >>= 1;
        }
        
        _MASK(*curPort, ~(*curPort), amberLedsMask);
    }
}


// +------------------------+
// | GESTION DE PinPosition |
// +------------------------+

volatile uint8_t* getPortPtr(PinPosition pinPos) {
    switch (pinPos / 8) {
        case 0:  return &PORTA; break;
        case 1:  return &PORTB; break;
        case 2:  return &PORTB; break;
        default: return &PORTD; break;
    }
}

uint8_t getPinVal(PinPosition pinPos) {
    switch (pinPos / 8) {
        case 0:  return PINA; break;
        case 1:  return PINB; break;
        case 2:  return PINB; break;
        default: return PIND; break;
    }
}