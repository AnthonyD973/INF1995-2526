#include "parser.h"

#define _OP(op)     ((Opcode)((op)>>8))
#define _DATA(op)   ((uint8_t)((op)&0xFF))

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

void Parser::parse() {
    _curAddr = 0x0002;
    uint8_t curOp, curData;
    
    do {
        RAM::read(_curAddr, &curOp);
        _curAddr += 2;
    } while(curOp != DBT);
    
    _curAddr += 2;
    
    
    
    for EVER {
        RAM::read(_curAddr++, &curOp);
        RAM::read(_curAddr++, &curData);
        
        if(curOp == FIN) {
            break;
        }
        
        uint16_t instr = curOp << 8 + curData;
        _unitaryParse(instr);
    }
    
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
     default: UART::transmitCStr("_unitaryParse : mauvaise valeur de l'opcode(");
              UART::transmit((op%16)|0x20);
              UART::transmit((op/16)|0x20);
              UART::transmitCStr(").\n");
    }
}

void Parser::att(uint8_t data) {
    
}

void Parser::dal(uint8_t data) {
    
}

void Parser::det(uint8_t data) {
    
}

void Parser::sgo(uint8_t data) {
    
}

void Parser::sar() {
    
}

void Parser::mar() {
    
}

void Parser::mav(uint8_t data) {
    
}

void Parser::mre(uint8_t data) {
    
}

void Parser::trd() {
    
}

void Parser::trg() {
    
}

void Parser::dbc(uint8_t data) {
    _loopBegAddr = _curAddr + 2;
    _iteratorMax = data;
    _iterator = 0;
}

void Parser::fbc() {
    if (_iterator <= _iteratorMax) {
        _curAddr = _loopBegAddr;
    }
    ++_iterator;
}