#include "parser.h"

void parse(uint16_t instr) {
 uint16_t op = instr & OPCODE_MASK;
    
    switch (op) {
     case DBT:  dbt(instr); break;
     case ATT:  att(instr); break;
     case DAL:  dal(instr); break;
     case DET:  det(instr); break;
     case SGO:  sgo(instr); break;
     case SAR:  sar(instr); break;
     case MAR1: // fallthrough
     case MAR2: mar(instr); break;
     case MAV:  mav(instr); break;
     case MRE:  mre(instr); break;
     case TRD:  trd(instr); break;
     case TRG:  trg(instr); break;
     case DBC:  dbc(instr); break;
     case FBC:  fbc(instr); break;
     case FIN:  fin(instr); break;
     default: UART::transmitCStr("parse : mauvaise valeur de l'opcode.");
    }
}

inline void dbt(uint16_t instr) {
    
}

inline void att(uint16_t instr) {
    uint16_t data = instr & DATA_MASK;
    
}

inline void dal(uint16_t instr) {
    uint16_t data = instr & DATA_MASK;
    
}

inline void det(uint16_t instr) {
    uint16_t data = instr & DATA_MASK;
    
}

inline void sgo(uint16_t instr) {
    uint16_t data = instr & DATA_MASK;
    
}

inline void sar(uint16_t instr) {
    
}

inline void mar(uint16_t instr) {
    
}

inline void mav(uint16_t instr) {
    uint16_t data = instr & DATA_MASK;
    
}

inline void mre(uint16_t instr) {
    uint16_t data = instr & DATA_MASK;
    
}

inline void trd(uint16_t instr) {
    
}

inline void trg(uint16_t instr) {
    
}

inline void dbc(uint16_t instr) {
    uint16_t data = instr & DATA_MASK;
    
}

inline void fbc(uint16_t instr) {
    
}

inline void fin(uint16_t instr) {
    
}

inline void dbt(uint16_t instr) {
    
}