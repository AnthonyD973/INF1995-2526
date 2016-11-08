#ifndef PARSER_H
#define PARSER_H

#include <lib.h>
#include <ram.h>
#include <timer.h>
#include <led.h>
#include <engine.h>
#include <buzzer.h>
#include <drive.h>

class Parser {
public:
    static void init();
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
    
    static uint16_t _curAddr;
    
    static uint16_t _loopBegAddr;
    static uint8_t  _iterator, _iteratorMax;
};

#endif // PARSER_H
