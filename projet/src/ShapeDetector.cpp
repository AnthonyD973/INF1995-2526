#include "ShapeDetector.h"
#include "LineSnsr.h"
#include "path.h"

uint8_t ShapeDetector::creaseCount_ = 0;
const uint8_t ShapeDetector::uncert_ = 15;
bool ShapeDetector::wasDecreasing_ = true;
uint8_t ShapeDetector::prevDist_ = 0;
uint8_t ShapeDetector::prevDist_ = 0;

Shape ShapeDetector::checkShape() {
    // Initialiser
    creaseCount_ = 0;
    wasDecreasing_ = true;
    prevDist_ = 0;
    
    
    
    Path::turn(ROT_RIGHT, 0x7F);
    
    _delay_ms(200.0); // On veut s'assurer que l'on est sorti de la ligne.
    
    // On continue tant que l'on n'a pas d�tect� la ligne.
    while (LineSnsr::read() < 0x10) {
        bool isDecreasing = checkDecreasing_();
        updateCreaseCount_(isDecreasing);
    }
    
    Path::stop();
    
    // Prise de d�cision
    Shape shape;
    if (creaseCount_ <= 1) {
        shape = CIRCLE_G;
    } else if (creaseCount_ >= 4) {
        shape = OCTOGON_R;
    } else {
        shape = SQUARE_B;
    }
    UART::transmitHex(creaseCount_);
    
    return shape;
}

bool ShapeDetector::checkDecreasing_() {
    // On r�cupert la distance actuelle
    uint8_t dist = DistSnsr::read();
    bool ret = wasDecreasing_;
    
    if (prevDist_ + uncert_ < dist) { // Si la valeur augmente...
        ret = false; // La distance NE d�croit PAS.
    }
    else if (prevDist_ - uncert_ > dist) { // Si la valeur diminue...
        ret = true; // La distance D�croit.
    }
    prevDist_ = dist;
    
    UART::transmitHex(dist);
    UART::transmit(' ');
    
    return ret;
}

void ShapeDetector::updateCreaseCount_(bool isDecreasing) {
    if (!wasDecreasing_ && isDecreasing) {
        ++creaseCount_;
    }
    wasDecreasing_ = isDecreasing;
}