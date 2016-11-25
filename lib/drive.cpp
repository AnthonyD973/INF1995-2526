/* 
 * Classe gérant les deux moteurs, pour que le robot aille droit. Et tourne
 * à 90°.
 * 
 * >>> <b>Utilisé uniquement dans le TP9.</b> <<<
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

#include "drive.h"

uint8_t Drive::CONST_R = 0xFF, Drive::CONST_L = 0xFF;

Engine Drive::_engL(0xFF);
Engine Drive::_engR(0xFF);

void Drive::init(TimerChannelUsed tcuLeft, TimerChannelUsed tcuRight, uint8_t constLeft, uint8_t constRight) {
    _engL = Engine(tcuLeft);
    _engR = Engine(tcuRight);
    CONST_L = constLeft;
    CONST_R = constRight;
}

void Drive::setMovement(EngineMode mode, uint8_t power) {
    uint16_t tmpPwrL = power*CONST_L/0xFF;
    if (tmpPwrL < 255/3) {
        tmpPwrL = 255/3;
    }
    _engL.setPower(mode, (uint8_t)tmpPwrL);
    
    uint16_t tmpPwrR = power*CONST_R/0xFF;
    if (tmpPwrR < 255/3) {
        tmpPwrR = 255/3;
    }
    _engR.setPower(mode, (uint8_t)tmpPwrR);
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
    if (tmpPwrL < 255/3) {
        tmpPwrL = 255/3;
    }
    _engL.setPower(modeL, (uint8_t)tmpPwrL);
    
    uint16_t tmpPwrR = power*CONST_R/0xFF;
    if (tmpPwrR < 255/3) {
        tmpPwrR = 255/3;
    }
    _engR.setPower(modeR, (uint8_t)tmpPwrR);
}
