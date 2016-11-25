#ifndef SHAPE_DETECTOR_H
#define SHAPE_DETECTOR_H

#include <incl.h>

typedef uint8_t Shape;

#include "DistSnsr.h"

// ---Shape---
#ifndef CIRCLE_G
    #include "ColorSnsr.h"  // Nécessaire pour rester consistant avec les
                            // constantes de couleur du capteur.
    #define CIRCLE_G  COLOR_READ_GREEN
    #define OCTOGON_R COLOR_READ_RED
    #define SQUARE_B  COLOR_READ_BLUE
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
