#include "ColorSequenceDetector.h"

Color ColorSequenceDetector::colorSequence_[COLOR_SEQ_MAX];
uint8_t ColorSequenceDetector::colorSequenceCount_ = 0;
Color ColorSequenceDetector::inputSequence_[INPUT_SEQ_MAX] = {COLOR_READ_WHITE,COLOR_READ_WHITE,COLOR_READ_WHITE,COLOR_READ_WHITE};
uint8_t ColorSequenceDetector::inputSequenceBeg_ = 0;

void ColorSequenceDetector::checkSequence(const Color shapeSequence[3]) {
    uint8_t colorCount = 0;
    Color color = ColorSnsr::read();
    Color prevColor = COLOR_READ_WHITE;
    
    Path::forward();
    
    // On vérifie les 6 combinaisons
    for (uint8_t i = 0; i < 6; ++i) {
        color = ColorSnsr::read();
        colorSequenceCount_ = 0;
        colorCount = 0;
        inputSequence_[0] = inputSequence_[1] = inputSequence_[2] = inputSequence_[3] = COLOR_READ_WHITE;
        
        // On attend de commencer sur du blanc...
        while (color != COLOR_READ_WHITE) { color = ColorSnsr::read(); }
        
        //
        while (colorCount < 2) {
            color = ColorSnsr::read();
            
            if (checkColorChange(color)) {
                colorSequence_[colorSequenceCount_++] = color;
                ++colorCount;
            }
            
            if (color != prevColor) {
                switch(color) {
                 case OCTOGON_R:        Buzzer::clearTone();_MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5)); break;
                 case CIRCLE_G:         Buzzer::clearTone();_MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); break;
                 case SQUARE_B:         Buzzer::setTone(68); // fallthrough
                 case COLOR_READ_WHITE: // fallthrough
                 default: _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
                }
                prevColor = color;
            }
        }
        
        if (shapeSequence[0] == colorSequence_[0] && shapeSequence[1] == colorSequence_[1]) {
            break;
        }
        
        UART::transmitHex(colorSequence_[0]);
        UART::transmit(' ');
        UART::transmitHex(shapeSequence[0]);
        UART::transmit(' ');
        UART::transmitHex(colorSequence_[1]);
        UART::transmit(' ');
        UART::transmitHex(shapeSequence[1]);
        UART::transmit(' ');
        UART::transmitHex(colorSequence_[2]);
        UART::transmit(' ');
        UART::transmitHex(shapeSequence[2]);
        UART::transmit('\n');
        
        // On vérifie un 3e changement de couleur, pour la forme ;)
        while(color != COLOR_READ_WHITE) {
            color = ColorSnsr::read();
            
            if (checkColorChange(color)) {
                colorSequence_[colorSequenceCount_++] = color;
                ++colorCount;
            }
            
            if (color != prevColor) {
                switch(color) {
                 case OCTOGON_R:        Buzzer::clearTone();_MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5)); break;
                 case CIRCLE_G:         Buzzer::clearTone();_MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); break;
                 case SQUARE_B:         Buzzer::setTone(68); // fallthrough
                 case COLOR_READ_WHITE: // fallthrough
                 default: _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
                }
                prevColor = color;
            }
        }
        
        Buzzer::clearTone();
        _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
    }
    
    Buzzer::clearTone();
    _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
    Path::stop();
    
    const float delayValue = 150.0;
	
	Buzzer::setTone(67);
	_delay_ms(delayValue);
	/**/Buzzer::setTone(66);
	_delay_ms(delayValue);
	Buzzer::setTone(63);
	_delay_ms(delayValue);
	Buzzer::setTone(57);
	_delay_ms(delayValue);
	Buzzer::setTone(56);
	_delay_ms(delayValue);
	Buzzer::setTone(64);
	_delay_ms(delayValue);
	Buzzer::setTone(68);
	_delay_ms(delayValue);
	Buzzer::setTone(72);
	_delay_ms(delayValue);//*/
	
	Buzzer::clearTone();
}

bool ColorSequenceDetector::checkColorChange(Color color) {
    bool ret = false;
    
    // On "push_back" une nouvelle valeur dans la queue...
    inputSequence_[inputSequenceBeg_] = color; // On la met à la fin, puis...
    ++inputSequenceBeg_ %= INPUT_SEQ_MAX; // On avance le pointeur de début.
    
    // Si le premier est différent des 3 derniers et que les 3 derniers sont
    // identiques...
    if ((inputSequence_[inputSequenceBeg_] != inputSequence_[(inputSequenceBeg_+1) % INPUT_SEQ_MAX]) &&
        (inputSequence_[(inputSequenceBeg_+1) % INPUT_SEQ_MAX] == inputSequence_[(inputSequenceBeg_+2) % INPUT_SEQ_MAX]) &&
        (inputSequence_[(inputSequenceBeg_+2) % INPUT_SEQ_MAX] == inputSequence_[(inputSequenceBeg_+3) % INPUT_SEQ_MAX])) {
        // Il y a eu un changement de couleur !
        ret = true;
    }
    
    return ret;
}
