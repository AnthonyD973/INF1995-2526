#ifndef SHAPE_DETECTOR_H
#define SHAPE_DETECTOR_H

typedef uint8_t Shape;

#include "DistSnsr.h"

// ---Shape---
#define CIRCLE  0
#define OCTOGON 1
#define SQUARE  2

class ShapeDetector {
public:
    static Shape checkShape();
    
private:
    static bool checkDirect_();
    static void checkDecreasing_(bool isDecreasing);
    
    static uint8_t creaseCount_;
    static const uint8_t uncert_;
    static bool wasDecreasing_;
    static uint8_t prevVal_;
};

#endif // SHAPE_DETECTOR_H