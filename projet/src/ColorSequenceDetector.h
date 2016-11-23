#ifndef COLOR_SEQUENCE_DETECTOR_H
#define COLOR_SEQUENCE_DETECTOR_H

#include <incl.h>
#include "ColorSnsr.h"
typedef uint8_t Color;

// ---Shape---
#ifndef CIRCLE_G
    #define CIRCLE_G  0
    #define OCTOGON_R 1
    #define SQUARE_B  2
#endif // CIRCLE_G

class ColorSequenceDetector {
    
public:
    static void checkSequence(Color shapeSequence[3]);

private:
    static bool checkColorChange();
    
    static Color colorSequence_[2];
    static uint8_t colorSequenceCount_;
    static Color inputSequence_[4];
    static uint8_t inputSequenceCount_;
};

#endif // COLOR_SEQUENCE_DETECTOR_H
