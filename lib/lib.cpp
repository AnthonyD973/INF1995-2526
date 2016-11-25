/*
 * Fichier de symboles divers utilisés dans la librarie.
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

#include "lib.h"

// ===============================
// = FONCTIONS UTILISABLES DANS  =
// = LES ROUTINES D'INTERRUPTION =
// ===============================

void switchAmberLedsColor(Timer* timer) {
    // Test fréquemment vrai, alors effectué au début.
    if (timer->_nAmberLeds == 0) {
        return;
    }
    
    // Changer la couleur des LED actuellement ambres.
    uint16_t curAmberLeds  = timer->_amberLeds;
    uint8_t nAmberLedsLeft = timer->_nAmberLeds;
    volatile uint8_t* curPort;
    for (PinPosition portBeginNum = 0; portBeginNum < 32 && nAmberLedsLeft != 0; portBeginNum += 8) {
        curPort = getPortPtr(portBeginNum);
        uint8_t amberLedsMask = 0;
        
        for (uint8_t pinNumberDivBy2 = 0; pinNumberDivBy2 < 4 && nAmberLedsLeft != 0; ++pinNumberDivBy2) {
            bool isThisLedAmber = (curAmberLeds & 1) == 1;
            if (isThisLedAmber) {
                --nAmberLedsLeft;
                amberLedsMask |= getMask(portBeginNum + 2*pinNumberDivBy2);
            }
            curAmberLeds >>= 1;
        }
        
        _MASK(*curPort, ~(*curPort), amberLedsMask);
    }
}


// ===============================
// =   GESTION DE PinPosition    =
// ===============================

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