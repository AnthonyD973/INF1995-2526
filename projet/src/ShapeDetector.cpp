#include "ShapeDetector.h"
#include "LineSnsr.h"
#include "path.h"

// uint8_t ShapeDetector::creaseCount_ = 0;
uint8_t ShapeDetector::min_ = 0;
uint8_t ShapeDetector::max_ = 0;
const uint8_t ShapeDetector::uncert_ = 10;
const uint8_t ShapeDetector::SQUARE_DELTA  = 0x1A;
const uint8_t ShapeDetector::OCTOGON_DELTA = 0x06;

ShapeColor ShapeDetector::checkShape() {
    Path::stop();
    
    // Initialiser
    min_ = getAverageValue_();
    max_ = min_;
    UART::transmitHex(min_);
    UART::transmit(' ');
    
    
    Path::turn(ROT_LEFT, 0x8F);
    
    _delay_ms(200.0); // On veut s'assurer que l'on est sorti de la ligne.
    
    uint8_t curDist  = min_;
        UART::transmitHex(curDist);
        UART::transmit(' ');
    
    uint8_t readsCount = 0;
    while (curDist >= max_ - uncert_ && readsCount++ < 12) { // On ne détecte que le premier maximum.
        curDist = getAverageValue_();
        UART::transmitHex(curDist);
        UART::transmit(' ');
        updateMax_(curDist);
    }
    
    UART::transmitCStr("Trouve Max. ");
    
    _MASK(PORTC, _BV(PC4), _BV(PC4) | _BV(PC5));
    while (!(LineSnsr::read() & 0x02)) { _MASK(PORTC, ~PORTC, _BV(PC4) | _BV(PC5)); } // On continue tant que l'on n'a pas détecté la ligne.
    
    Path::stop();
    
    // Prise de décision
    ShapeColor shape;
    if (max_ - min_ >= SQUARE_DELTA) {
        shape = SQUARE_BLUE;
    } else if (max_ - min_ >= OCTOGON_DELTA) {
        shape = OCTOGON_RED;
    } else {
        shape = CIRCLE_GREEN;
    }
    UART::transmitHex(max_ - min_);
    UART::transmit('\n');
    
    return shape;
}

uint8_t ShapeDetector::getAverageValue_() {
    static const uint8_t nReads = 32;
    
    uint16_t sum = 0;
    for (uint8_t i = 0; i < nReads; ++i) {
        sum += DistSnsr::read();
        _delay_ms(12.5/4.0);
    }
    
    return sum/nReads;
}

void ShapeDetector::updateMax_(uint8_t curDist) {
    if (curDist > max_) {
        max_ = curDist;
    }
}
