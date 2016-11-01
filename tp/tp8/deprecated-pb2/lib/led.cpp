#include "led.h"

// PUBLIC:

LED::LED(PinPosition pinPos, Timer* timer)
    : _timer(timer), _pinPos(pinPos), _GREEN(LED_GREEN << getPinNumber(pinPos)),
      _RED(LED_RED << getPinNumber(pinPos)), _THIS_MASK(getMask(pinPos)),
      _PORT(getPortPtr(pinPos))
{ }


void LED::setColor(LedColor color) {
    if (_color == LED_AMBER) {
        _unsetColorAmber();
    }
    
    switch(color) {
        case LED_GREEN: _MASK(*_PORT, _GREEN, _THIS_MASK); break;
        case LED_RED:   _MASK(*_PORT, _RED,   _THIS_MASK); break;
        case LED_AMBER: _setColorAmber(); break;
        case LED_OFF:   // fallthrough
        default:        _MASK(*_PORT,  0x00,  _THIS_MASK); break;
    }
	
	_color = color;
}

volatile LedColor LED::getColor() {
    return _color;
}


PinPosition LED::getPinPos() {
    return _pinPos;
}


void LED::setTimer(Timer* timer) {
    if (_color == LED_AMBER) {
        _unsetColorAmber();
        _timer = timer;
        _setColorAmber();
        return;
    }
    _timer = timer;
    return;
}

Timer* LED::getTimer() {
    return _timer;
}

// PRIVATE:

void LED::_setColorAmber() {
    ++(_timer->_nAmberLeds);
    _MASK(*_PORT, _GREEN, _THIS_MASK);
    _MASK(_timer->_amberLeds, getShiftedPos(_pinPos), getShiftedPos(_pinPos)); // Une division par 2 car les positions sont des multiples de 2
}

void LED::_unsetColorAmber()  {
    --(_timer->_nAmberLeds);
    _MASK(*_PORT,  0x00,  _THIS_MASK);
    _MASK(_timer->_amberLeds, 0x0, getShiftedPos(_pinPos));
}
