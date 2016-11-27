/**
 * Classe permettant de détecter la séquence de couleurs sur laquelle s'arrêter.
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

#include "ColorSequenceDetector.h"

Color ColorSequenceDetector::colorSequence_[COLOR_SEQ_MAX];
uint8_t ColorSequenceDetector::colorSequenceCount_ = 0;
Color ColorSequenceDetector::lastColors_[LAST_COLORS_MAX] = {COLOR_READ_WHITE,COLOR_READ_WHITE,COLOR_READ_WHITE,COLOR_READ_WHITE};
uint8_t ColorSequenceDetector::lastColorsBeg_ = 0;

void ColorSequenceDetector::checkSequence(const Color shapeSequence[3]) {
    Color color = ColorSnsr::read();
    
    Path::forward();
    
    // On vérifie les 6 combinaisons
    for (uint8_t i = 0; i < 6; ++i) {
        color = ColorSnsr::read();
        colorSequenceCount_ = 0;
        
        for (uint8_t i = 0; i < LAST_COLORS_MAX; ++i) {
            lastColors_[i] = COLOR_READ_WHITE;
        }
        
        while (color != COLOR_READ_WHITE) {
            color = ColorSnsr::read();
        }
        
        // On n'a besoin que de 2 couleurs savoir de quelle séquence il s'agit :D
        while (colorSequenceCount_ < 2) {
            color = findColorAndAct_();
        }
        
        if (shapeSequence[0] == colorSequence_[0] && shapeSequence[1] == colorSequence_[1]) {
            Buzzer::clearTone();
            _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
            Path::stop();
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
            color = findColorAndAct_();
        }
        
        Buzzer::clearTone();
        _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
    }
    
    playEndingTheme_();
}

Color ColorSequenceDetector::findColorAndAct_() {
    Color color = ColorSnsr::read();
    
    if (checkColorChanged_(color)) {
        colorSequence_[colorSequenceCount_++] = color;
    
        switch(color) {
         case OCTOGON_R:        Buzzer::clearTone(); _MASK(PORTC, _BV(PC5), _BV(PC4) | _BV(PC5)); break;
         case CIRCLE_G:         Buzzer::clearTone(); _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5)); break;
         case SQUARE_B:         Buzzer::setTone(68); // fallthrough
         default: _MASK(PORTC, 0, _BV(PC4) | _BV(PC5));
        }
    }
    return color;
}

bool ColorSequenceDetector::checkColorChanged_(Color color) {
    bool ret = false;
    
    // On "push_back" une nouvelle valeur dans la queue...
    lastColors_[lastColorsBeg_] = color; // On la met à la fin, puis...
    ++lastColorsBeg_;
    lastColorsBeg_ %= LAST_COLORS_MAX; // On avance le pointeur de début.
    
    // Si le premier est différent des 3 derniers et que les 3 derniers sont
    // identiques...
    if ((lastColors_[lastColorsBeg_] != lastColors_[(lastColorsBeg_+1) % LAST_COLORS_MAX]) &&
        (lastColors_[(lastColorsBeg_+1) % LAST_COLORS_MAX] == lastColors_[(lastColorsBeg_+2) % LAST_COLORS_MAX]) &&
        (lastColors_[(lastColorsBeg_+2) % LAST_COLORS_MAX] == lastColors_[(lastColorsBeg_+3) % LAST_COLORS_MAX])) {
        // Il y a eu un changement de couleur !
        ret = true;
    }
    
    return ret;
}


void ColorSequenceDetector::playEndingTheme_() {
    const float delayValue = 150.0;
    
    Buzzer::setTone(67);
    _delay_ms(delayValue);
    Buzzer::setTone(66);
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
    _delay_ms(delayValue);
    Buzzer::clearTone();
}