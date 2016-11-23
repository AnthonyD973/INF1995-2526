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
    static uint8_t getAverageValue_();
    static void updateMax_(uint8_t curDist);
    
//     static uint8_t creaseCount_;
    static uint8_t min_;
    static uint8_t max_;
    static const uint8_t uncert_;
    static const uint8_t SQUARE_DELTA;
    static const uint8_t OCTOGON_DELTA;
};

#endif // SHAPE_DETECTOR_H