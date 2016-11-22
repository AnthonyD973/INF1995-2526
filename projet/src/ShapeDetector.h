#ifndef SHAPE_DETECTOR_H
#define SHAPE_DETECTOR_H

#include <incl.h>

typedef uint8_t Shape;

#include "DistSnsr.h"

// ---Shape---
#ifndef CIRCLE_G
    #define CIRCLE_G  0
    #define OCTOGON_R 1
    #define SQUARE_B  2
#endif // CIRCLE_G

class ShapeDetector {
public:
    static Shape checkShape();
    
private:
    static bool checkDecreasing_();
    static void updateCreaseCount_(bool isDecreasing);
    
    static uint8_t creaseCount_;
    static const uint8_t uncert_;
    static bool wasDecreasing_;
    static uint8_t prevDist_;
};

#endif // SHAPE_DETECTOR_H