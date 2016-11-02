#include "drive.h"

Engine Drive::_engL(0xFF);
Engine Drive::_engR(0xFF);

/**
 * @brief   Initialise les objets Engine.
 * @param[in] tcuLeft   Sert à définir sur quelles broches le moteur gauche est
 *      branché. Voir engine.h.
 * @param[in] tcuRight  Sert à définir sur quelles broches le moteur droit est
 *      branché. Voir engine.h.
 */
void Drive::init(TimerChannelUsed tcuLeft, TimerChannelUsed tcuRight) {
    _engL = Engine(tcuLeft);
    _engR = Engine(tcuRight);
}

/**
 * @brief   Met les moteurs sur un mode. Tient compte du fait que les deux
 *      moteurs ne tournent pas à la même vitesse.
 * @param[in] mode  Mode des moteurs à mettre. Voir engine.h.
 * @param[in] power Puissance à transmette aux moteurs. Entre 0 et 255.
 */
void Drive::setPower(EngineMode mode, uint8_t power) {
    if (mode == ENG_FORWARD) {
        _forward(power);
    }
    
}


void Drive::_forward(uint8_t power) {
    uint16_t tmpPwrL = power;
    _engL.setPower(ENG_FORWARD, (uint8_t)tmpPwrL);
    
    uint16_t tmpPwrR = power*127/255;
    _engR.setPower(ENG_FORWARD, (uint8_t)tmpPwrR);
}