#include "ShapeDetector.h"

uint8_t ShapeDetector::creaseCount_ = 0;
const uint8_t ShapeDetector::uncert_ = 5;
bool ShapeDetector::wasDecreasing_ = false;
uint8_t ShapeDetector::prevVal_ = 0;

Shape ShapeDetector::checkShape() {
    
}

bool ShapeDetector::checkDecreasing_() {
    // On récupert la distance actuelle
    uint8_t dist = DistSnsr::read();
    bool ret = wasDecreasing_;
    
    if (prevVal_ + uncert_ < dist) { // Si la valeur augmente...
        ret = false; // La distance NE décroit PAS.
    }
    else if (prevVal_ - uncert_ > dist) { // Si la valeur diminue...
        ret = true; // La distance DÉcroit.
    }
    prevVal_ = dist;
    
    return ret;
}

void ShapeDetector::updateCreaseCount_(bool isDecreasing) {
    if (!wasDecreasing_ && isDecreasing) {
        ++creaseCount_;
    }
    wasDecreasing_ = isDecreasing;
}