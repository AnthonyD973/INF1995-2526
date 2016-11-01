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

void _unitaryParse(uint16_t instr);

void parse(uint16_t addrBeg) {}

inline void dbt();
inline void att(uint8_t data);
inline void dal(uint8_t data);
inline void det(uint8_t data);
inline void sgo(uint8_t data);
inline void sar();
inline void mar();
inline void mav(uint8_t data);
inline void mre(uint8_t data);
inline void trd();
inline void trg();
inline void dbc(uint8_t data);
inline void fbc();
inline void fin();

void _unitaryParse(uint16_t instr) {
    Opcode op = _OP(instr);
    uint8_t data = _DATA(instr);
    
    switch (op) {
     case DBT:  dbt(); break;
     case ATT:  att(data); break;
     case DAL:  dal(data); break;
     case DET:  det(data); break;
     case SGO:  sgo(data); break;
     case SAR:  sar(); break;
     case MAR1: // fallthrough
     case MAR2: mar(); break;
     case MAV:  mav(data); break;
     case MRE:  mre(data); break;
     case TRD:  trd(); break;
     case TRG:  trg(); break;
     case DBC:  dbc(data); break;
     case FBC:  fbc(); break;
     case FIN:  fin(); break;
     default: UART::transmitCStr("_unitaryParse : mauvaise valeur de l'opcode(");
              UART::transmit((op%16)|0x20);
              UART::transmit((op/16)|0x20);
              UART::transmitCStr(").\n");
    }
}

inline void dbt() {
    
}

inline void att(uint8_t data) {
    
}

inline void dal(uint8_t data) {
    
}

inline void det(uint8_t data) {
    
}

inline void sgo(uint8_t data) {
    
}

inline void sar() {
    
}

inline void mar() {
    
}

inline void mav(uint8_t data) {
    
}

inline void mre(uint8_t data) {
    
}

inline void trd() {
    
}

inline void trg() {
    
}

inline void dbc(uint8_t data) {
    
}

inline void fbc() {
    
}

inline void fin() {
    
}
