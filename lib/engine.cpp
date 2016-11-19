#include "engine.h"

Timer* getTimerFromTCU(TimerChannelUsed tcu) {
    switch(tcu) {
        case T0CA: // fallthrough
        case T0CB: return &timer0;
        case T1CA: // fallthrough
        case T1CB: return &timer1;
//         case T2CA: // fallthrough
//         case T2CB: return &timer2;
        default: return 0;
    }
}

uint8_t getIsOnChannelAFromTCU(TimerChannelUsed tcu) {
    switch (tcu) {
     case T0CA: // fallthrough
     case T1CA: return 1;
     // case T2CA: return 1;
     case T0CB: // fallthrough
     case T1CB: return 0;
     // case T2CB: return 0;
     default: return 0;
    }
}

uint8_t getForwardFromTCU(TimerChannelUsed tcu) {
    switch (tcu) {//    ENABLE   (DIRECTION = 0)
     case T0CA: return _BV(PB3); // 00001000
     case T0CB: return _BV(PB4); // 00010000
     case T1CA: return _BV(PD5); // 00100000
     case T1CB: return _BV(PD4); // 00010000
//      case T2CA: return _BV(PD7); // 10000000
//      case T2CB: return _BV(PD6); // 01000000
     default:   return 0;
    }
}

uint8_t getBackwardFromTCU(TimerChannelUsed tcu) {
    switch (tcu) {//    ENABLE   DIRECTION
     case T0CA: return _BV(PB3) | _BV(PB2); // 00001100
     case T0CB: return _BV(PB4) | _BV(PB5); // 00110000
     case T1CA: return _BV(PD5) | _BV(PD3); // 00101000
     case T1CB: return _BV(PD4) | _BV(PD2); // 00010100
//      case T2CA: return _BV(PD7) | _BV(???); // 10000000
//      case T2CB: return _BV(PD6) | _BV(???); // 01000000
     default:   return 0;
    }
}

uint8_t getThisMaskFromTCU(TimerChannelUsed tcu) {
    switch (tcu) { //    ENABLE   DIRECTION
     case T0CA: return _BV(PB3)  | _BV(PB2); // 00001100
     case T0CB: return _BV(PB4)  | _BV(PB5); // 00110000
     case T1CA: return _BV(PD5)  | _BV(PD3); // 00101000
     case T1CB: return _BV(PD4)  | _BV(PD2); // 00010100
//      case T2CA: return _BV(PD7) | _BV(???); // 10000000
//      case T2CB: return _BV(PD6) | _BV(???); // 01000000
     default:   return 0;
    }
}

volatile uint8_t* getPortPtrFromTCU (TimerChannelUsed tcu) {
    switch (tcu) {
     case T0CA: DDRB |= _BV(PB2) | _BV(PB3); return &PORTB;
     case T0CB: DDRB |= _BV(PB4) | _BV(PB5); return &PORTB;
     case T1CA: DDRD |= _BV(PD3) | _BV(PD5); return &PORTD;
     case T1CB: DDRD |= _BV(PD2) | _BV(PD4); return &PORTD;
//      case T2CA: return &PORTD;
//      case T2CB: return &PORTD;
     default: return 0;
    }
}

// ===========================
// =         ENGINE          =
// ===========================

// PUBLIC:

Engine::Engine(TimerChannelUsed tcu)
    : _timer(getTimerFromTCU(tcu)),
    _isOnChannelA(getIsOnChannelAFromTCU(tcu)),
    _FORWARD(getForwardFromTCU(tcu)),
    _BACKWARD(getBackwardFromTCU(tcu)),
    _THIS_MASK(getThisMaskFromTCU(tcu)),
    _PORT(getPortPtrFromTCU(tcu))
{
    if (_timer != 0) {
        _timer->setPrescale(P01_CLK8);
        setMode(ENG_OFF);
        _timer->setMode(WGM0_PWM_F1);
        if (_isOnChannelA) {
            _timer->setComNA(CLEAR);
            _timer->setOcrNA(0x00FF);
        }
        else {
            _timer->setComNB(CLEAR);
            _timer->setOcrNB(0x00FF);
        }
    }
}

void Engine::setPower(EngineMode mode, uint16_t occrNX) {
    // Utiliser le timer, et changer la valeur de OCCRNX.
    if (_isOnChannelA) {
        _timer->setComNA(CLEAR);
        _timer->setOcrNA(occrNX);
    }
    else {
        _timer->setComNB(CLEAR);
        _timer->setOcrNB(occrNX);
    }
    
    // Mettre le bit de direction du port à 0 (forward) ou 1 (backward).
    switch(mode) {
     case ENG_FORWARD:  _MASK(*_PORT, _FORWARD,  _THIS_MASK); break;
     case ENG_BACKWARD: _MASK(*_PORT, _BACKWARD, _THIS_MASK); break;
     case ENG_OFF: setMode(ENG_OFF); break;
     default: UART::transmitCStr("Engine::power : mauvaise valeur de 'mode'.\n"); setMode(ENG_OFF);
    }
    
}


/**
 * @brief   Met le moteur sur un certain mode. Le compteur ne sera plus utilisé :
 *      le moteur est sur ce mode jusqu'à nouvel ordre.
 * @param[in] mode  Mode du moteur à mettre.
 */
void Engine::setMode(EngineMode mode) {
    uint8_t valueToSet;
    
    switch(mode) {
     case ENG_OFF:      valueToSet = 0; break;
     case ENG_FORWARD:  valueToSet = _FORWARD; break;
     case ENG_BACKWARD: valueToSet = _BACKWARD; break;
     default:           valueToSet = 0;
    }
    
    if (_isOnChannelA) {
        _timer->setComNA(DISCONNECTED);
    }
    else {
        _timer->setComNB(DISCONNECTED);
    }
    
    _MASK(*_PORT, valueToSet, _THIS_MASK);
    
}


Timer* Engine::getTimer() {
     return _timer;
}
