#include "defaultISR.h"

/**
 * @brief Change la couleur des leds présentement ambres gérées par un compteur.
 *      NOTE: Cette fonction n'est utilisée nulle part dans les libraires ; c'est une fonction
 *      préécrite que l'on peut utiliser, par exemple dans les routines d'interruption.
 * @param[in] timer Compteur impliqué.
 */
void intTimerChgAmberLedsColor(Timer* timer) {
    if (timer->_nLedsControlled == 0) {
        return;
    }
    
    uint16_t curAmberLeds = timer->_amberLeds;
    
    for (PinPosition curPos = 0; curPos < 32; curPos += 2) {
        bool isThisLedAmber = (curAmberLeds & 1) == 1;
        if (isThisLedAmber) {
            uint8_t mask = getMask(curPos);
            LedColor curColor  = getPinVal(curPos) & mask;
            LedColor nextColor = ~curColor & mask;
            _MASK(*getPortPtr(curPos), nextColor, mask);
        }
        
        curAmberLeds >>= 1;
    }
}
