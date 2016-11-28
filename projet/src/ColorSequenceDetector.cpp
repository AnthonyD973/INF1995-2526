#include "ColorSequenceDetector.h"

LED* ColorSequenceDetector::LED_ = nullptr;
ShapeColor ColorSequenceDetector::colorSequence_[COLOR_SEQ_MAX];
uint8_t ColorSequenceDetector::colorSequenceCount_ = 0;
ShapeColor ColorSequenceDetector::lastColors_[LAST_COLORS_MAX] = {NO_SHAPE_WHITE, NO_SHAPE_WHITE, NO_SHAPE_WHITE};
uint8_t ColorSequenceDetector::lastColorsBeg_ = 0;


void ColorSequenceDetector::init(LED* led) {
    LED_ = led;
}

void ColorSequenceDetector::checkSequence(const ShapeColor shapeSequence[3]) {
    ShapeColor color = ColorSnsr::read();
    
    Path::forward();
    
    // On vérifie les 6 combinaisons
    for (uint8_t i = 0; i < 6; ++i) {
        color = ColorSnsr::read();
        colorSequenceCount_ = 0;
        
        for (uint8_t j = 0; j < LAST_COLORS_MAX; ++j) {
            lastColors_[j] = NO_SHAPE_WHITE;
        }
        
        while (color != NO_SHAPE_WHITE) {
            color = ColorSnsr::read();
        }
        
        // On n'a besoin que de 2 couleurs pour savoir de quelle séquence il s'agit :D
        while (colorSequenceCount_ < 2) {
            color = findColorAndAct_();
        }
        
        if (isCorrectSequence_(shapeSequence)) {
            Buzzer::clearTone();
            LED_->setColor(LED_OFF);
            Path::stop();
            break;
        }
        
        // On vérifie un 3e changement de couleur, pour la forme ;)
        while(color != NO_SHAPE_WHITE) {
            color = findColorAndAct_();
        }
        
        Buzzer::clearTone();
        LED_->setColor(LED_OFF);
    }
    
    playEndingTheme_();
}

ShapeColor ColorSequenceDetector::findColorAndAct_() {
    ShapeColor color = ColorSnsr::read();
    
    if (hasColorChanged_(color)) {
        colorSequence_[colorSequenceCount_++] = color;
    
        switch(color) {
         case OCTOGON_RED:  Buzzer::clearTone(); LED_->setColor(LED_RED);   break;
         case CIRCLE_GREEN: Buzzer::clearTone(); LED_->setColor(LED_GREEN); break;
         case SQUARE_BLUE:  Buzzer::setTone(68); // fallthrough
         default: LED_->setColor(LED_OFF);
        }
    }
    return color;
}

bool ColorSequenceDetector::hasColorChanged_(ShapeColor color) {
    // On "push_back" une nouvelle valeur dans la queue
    lastColors_[lastColorsBeg_] = color;
    ++lastColorsBeg_;
    lastColorsBeg_ %= LAST_COLORS_MAX;
    
    ShapeColor earliestColor = lastColors_[lastColorsBeg_];
    ShapeColor colorAfterEarliest = lastColors_[(lastColorsBeg_ + 1) % LAST_COLORS_MAX];
    bool hasChanged = (earliestColor != colorAfterEarliest);
    
    ShapeColor color1 = colorAfterEarliest;
    for (uint8_t i = 2; (i < LAST_COLORS_MAX) && hasChanged; ++i) {
        ShapeColor color2 = lastColors_[(lastColorsBeg_ + i) % LAST_COLORS_MAX];
        hasChanged = (color1 == color2);
        color1 = color2;
    }
    
    return hasChanged;
}

bool ColorSequenceDetector::isCorrectSequence_(const ShapeColor shapeSequence[COLOR_SEQ_MAX]) {
    bool isCorrectSeq = true;
    
    // On n'a besoin que de 2 couleurs pour savoir de quelle séquence il s'agit :D
    for (uint8_t i = 0; (i < (COLOR_SEQ_MAX - 1)) && isCorrectSeq; ++i) {
        isCorrectSeq = (shapeSequence[i] == colorSequence_[i]);
    }
    
    return isCorrectSeq;
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
    _delay_ms(delayValue*6.0);
}
