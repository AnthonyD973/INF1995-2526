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
void Drive::init(TimerChannelUsed tcuLeft, TimerChannelUsed tcuRight,
                 uint8_t right, uint8_t left) {
    _engL = Engine(tcuLeft);
    _engR = Engine(tcuRight);
    CONST_R = right;
    CONST_L = left;
}

/**
 * @brief   Met les moteurs sur un mode. Tient compte du fait que les deux
 *      moteurs ne tournent pas à la même vitesse.
 * @param[in] mode  Mode des moteurs à mettre. Voir engine.h.
 * @param[in] power Puissance à transmette aux moteurs. Entre 0 et 255.
 */
void Drive::setMovement(EngineMode mode, uint8_t power) {
    uint16_t tmpPwrL = power*CONST_L/0xFF;
    _engL.setPower(ENG_FORWARD, (uint8_t)tmpPwrL);
    
    uint16_t tmpPwrR = power*CONST_R/0xFF;
    _engR.setPower(ENG_FORWARD, (uint8_t)tmpPwrR);
}

void Drive::setRotation(DriveDir dir, uint8_t power) {
    EngineMode
        modeR = ENG_OFF,
        modeL = ENG_OFF;
    if (dir == DIR_RIGHT) {
        modeR = ENG_BACKWARD;
        modeL = ENG_FORWARD;
    }
    if (dir == DIR_LEFT) {
        modeR = ENG_FORWARD;
        modeL = ENG_BACKWARD;
    }

    uint16_t tmpPwrL = power*CONST_L/0xFF;
    _engL.setPower(modeL, (uint8_t)tmpPwrL);
    
    uint16_t tmpPwrR = power*CONST_R/0xFF;
    _engR.setPower(modeR, (uint8_t)tmpPwrR);
}
