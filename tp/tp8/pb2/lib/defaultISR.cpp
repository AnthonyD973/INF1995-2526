#include "defaultISR.h"

/**
 * @brief Change la couleur des leds présentement ambres gérées par un compteur.
 *      NOTE: Cette fonction n'est utilisée nulle part dans les libraires ; c'est une fonction
 *      préécrite que l'on peut utiliser, par exemple dans les routines d'interruption.
 * @param[in] timer Compteur impliqué.
 */
void intTimerChgAmberLedsColor(Timer* timer) {
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
