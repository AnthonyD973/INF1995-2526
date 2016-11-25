#ifndef COLOR_SEQUENCE_DETECTOR_H
#define COLOR_SEQUENCE_DETECTOR_H

#include <incl.h>
#include <buzzer.h>
#include "ColorSnsr.h"
#include "path.h"
typedef uint8_t Color;

// ---Shape---
#ifndef CIRCLE_G
    #define CIRCLE_G  COLOR_READ_GREEN
    #define OCTOGON_R COLOR_READ_RED
    #define SQUARE_B  COLOR_READ_BLUE
#endif // CIRCLE_G

#define COLOR_SEQ_MAX 3
#define INPUT_SEQ_MAX 4

class ColorSequenceDetector {
    
public:
    static void checkSequence(const Color shapeSequence[3]);

private:
    static bool checkColorChange(Color color);
    
    static Color colorSequence_[COLOR_SEQ_MAX];
    static uint8_t colorSequenceCount_;
    static Color inputSequence_[INPUT_SEQ_MAX];
    static uint8_t inputSequenceBeg_;
};

#endif // COLOR_SEQUENCE_DETECTOR_H
