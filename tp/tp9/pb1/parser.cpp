#include "parser.h"

#define _OP(op)     ((Opcode)((op)>>8))
#define _DATA(op)   ((uint8_t)((op)&0xFF))
#define _PORT       PORTB

const uint16_t ROT_TIME_CST_LEFT  = 26;
const uint16_t ROT_TIME_CST_RIGHT = 26;
uint16_t Parser::_curAddr = 0x0002;

uint16_t Parser::_loopBegAddr = 0;
uint8_t  Parser::_iterator = 0, Parser::_iteratorMax = 0;

typedef uint8_t Opcode;
const Opcode
    DBT  = 0x01,
    ATT  = 0x02,
    DAL  = 0x44,
    DET  = 0x45,
    SGO  = 0x48,
    SAR  = 0x09,
    MAR1 = 0x60,
    MAR2 = 0x61,
    MAV  = 0x62,
    MRE  = 0x63,
    TRD  = 0x64,
    TRG  = 0x65,
    DBC  = 0xC0,
    FBC  = 0xC1,
    FIN  = 0xFF;

void Parser::init() {
    DDRB = 0x3F;
    RAM::init();
    Drive::init(T0CA, T0CB, 255, 255);
    Buzzer::init();
    
    //Buzzer::setTone(24);
    //Buzzer::clearTone();
}

void Parser::parse() {
    _curAddr = 0x0002;
    uint8_t curOp, curData;
    
    do {
        RAM::read(_curAddr, &curOp);
        _curAddr += 2;
    } while(curOp != DBT);
    
    for EVER {
        RAM::read(_curAddr++, &curOp);
        RAM::read(_curAddr++, &curData);
        
        if(curOp == FIN) {
            break;
        }
        
        uint16_t instr = (curOp << 8) + curData;
        _unitaryParse(instr);
    }
    
    sar();
    mar();
    
}

void Parser::_unitaryParse(uint16_t instr) {
    Opcode op = _OP(instr);
    uint8_t data = _DATA(instr);
    
    switch (op) {
     case ATT:  att(data); break;
     case DAL:  dal(data); break;
     case DET:  det(data); break;
     case SGO:  sgo(data); break;
     case SAR:  sar();     break;
     case MAR1: // fallthrough
     case MAR2: mar();     break;
     case MAV:  mav(data); break;
     case MRE:  mre(data); break;
     case TRD:  trd();     break;
     case TRG:  trg();     break;
     case DBC:  dbc(data); break;
     case FBC:  fbc();     break;
     default: /*UART::transmitCStr("_unitaryParse : mauvaise valeur de l'opcode(");
              UART::transmit((op%10)|0x30);
              UART::transmit(((op/10)%100)|0x30);
              UART::transmit((op/100)|0x30);
              UART::transmitCStr(").\n")*/;
    }
}

void Parser::att(uint8_t data) {
    for (uint8_t i = 0; i < data; ++i) {
        _delay_ms(25.0);
    }
}

void Parser::dal(uint8_t data) {
    if (data & 0x01)
        _PORT = LED_GREEN;
}

void Parser::det(uint8_t data) {
    if (data & 0x01)
        _PORT = LED_OFF;
}

void Parser::sgo(uint8_t data) {
    if (data >= 45 && data <= 81) {
        Buzzer::setTone(data);
    }
}

void Parser::sar() {
    Buzzer::clearTone();
}

void Parser::mar() {
    Drive::setMovement(ENG_OFF, 0);
}

void Parser::mav(uint8_t data) {
    Drive::setMovement(ENG_FORWARD, data);
}

void Parser::mre(uint8_t data) {
    Drive::setMovement(ENG_BACKWARD, data);
}

void Parser::trd() {
    Drive::setRotation(DIR_RIGHT, 255);
    for (uint16_t i = 0; i < ROT_TIME_CST_RIGHT; ++i) {
        _delay_ms(25);
    }
    Drive::setMovement(ENG_OFF, 0);
}

void Parser::trg() {
    Drive::setRotation(DIR_LEFT, 255);
    for (uint16_t i = 0; i < ROT_TIME_CST_LEFT; ++i) {
        _delay_ms(25);
    }
    Drive::setMovement(ENG_OFF, 0);
}

void Parser::dbc(uint8_t data) {
    _loopBegAddr = _curAddr;
    _iteratorMax = data;
    _iterator = 0;
}

void Parser::fbc() {
    if (_iterator < _iteratorMax) {
        _curAddr = _loopBegAddr;
    }
    ++_iterator;
}
