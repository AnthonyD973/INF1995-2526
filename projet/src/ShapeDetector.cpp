#include "ShapeDetector.h"
#include "LineSnsr.h"
#include "path.h"

LED* ShapeDetector::LED_ = nullptr;
uint8_t ShapeDetector::min_ = 0;
uint8_t ShapeDetector::max_ = 0;
const uint8_t ShapeDetector::SQUARE_DELTA_  = 0x1A;
const uint8_t ShapeDetector::OCTOGON_DELTA_ = 0x06;
const uint8_t ShapeDetector::N_READS_TILL_QUARTER_TURN_ = 12;

void ShapeDetector::init(LED* led) {
    LED_ = led;
}

ShapeColor ShapeDetector::checkShape() {
    Path::stop();
    
    // Initialiser
    min_ = DistSnsr::readAverage();
    max_ = min_;
    UART::transmitHex(min_);
    UART::transmit(' ');
    
    
    Path::turn(ROT_LEFT, V_MAX);
    
    _delay_ms(200.0); // S'assurer que l'on est sorti de la ligne.
    
    uint8_t curDist  = min_;
    uint8_t readsCount = 0;
    while (readsCount++ < N_READS_TILL_QUARTER_TURN_) {
        curDist = DistSnsr::readAverage();
        updateMax_(curDist);
        _delay_ms(50.0);
    }
    
    Path::turn(ROT_LEFT, V_MOY); // Tourner plus lentement pour éviter de
                                 // dépasser la ligne.
    
    while (!(LineSnsr::read() & 0x02)) { } // Continuer à tourner tant que l'on
                                           // n'a pas détecté la ligne.
    Path::stop();
    
    return findShapeAndAct_();
}

void ShapeDetector::updateMax_(uint8_t curDist) {
    if (curDist > max_) {
        max_ = curDist;
    }
}

ShapeColor ShapeDetector::findShapeAndAct_() {
    ShapeColor shape;
    
    const uint8_t DELTA = max_ - min_;
    if (DELTA >= SQUARE_DELTA_) {
        shape = SQUARE_BLUE;
    } else if (DELTA >= OCTOGON_DELTA_) {
        shape = OCTOGON_RED;
    } else {
        shape = CIRCLE_GREEN;
    }
    
    
    Buzzer::clearTone();
    LED_->setColor(LED_OFF);
    
    switch (shape) {
     case CIRCLE_GREEN:  LED_->setColor(LED_GREEN); _delay_ms(2000.0); break;
     case OCTOGON_RED:   LED_->setColor(LED_RED);   _delay_ms(2000.0); break;
     case SQUARE_BLUE:   Buzzer::setTone(68);       _delay_ms(2000.0); break;
     default: ;
    }
    
    Buzzer::clearTone();
    LED_->setColor(LED_OFF);
    
    return shape;
}
