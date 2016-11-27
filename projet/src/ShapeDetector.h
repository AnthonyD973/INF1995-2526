#ifndef SHAPE_DETECTOR_H
#define SHAPE_DETECTOR_H

#include <incl.h>

#include "typedefs.h"
#include "DistSnsr.h"

class ShapeDetector {
public:
    static ShapeColor checkShape();
    
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
