#ifndef PARSER_H
#define PARSER_H

#include "lib.h"
#include "ram.h"
#include "timer.h"
#include "led.h"
#include "engine.h"

class Parser {
public:
    static void parse();

private:
    static void _unitaryParse(uint16_t instr);

    static void att(uint8_t data);
    static void dal(uint8_t data);
    static void det(uint8_t data);
    static void sgo(uint8_t data);
    static void sar();
    static void mar();
    static void mav(uint8_t data);
    static void mre(uint8_t data);
    static void trd();
    static void trg();
    static void dbc(uint8_t data);
    static void fbc();
    
    static uint16_t _curAddr = 0x0002;
    
    static uint16_t _loopBegAddr = 0;
    static uint8_t  _iterator = 0, _iteratorMax = 0;
};

#endif // PARSER_H
