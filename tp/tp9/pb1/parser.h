#include "lib.h"
#include "timer.h"
#include "led.h"
#include "engine.h"

#define OPCODE_MASK 0xFF00
#define DATA_MASK   0x00FF

typedef uint16_t Opcode;
const Opcode
    DBT  = 0x0100,
    ATT  = 0x0200,
    DAL  = 0x4400,
    DET  = 0x4500,
    SGO  = 0x4800,
    SAR  = 0x0900,
    MAR1 = 0x6000,
    MAR2 = 0x6100,
    MAV  = 0x6200,
    MRE  = 0x6300,
    TRD  = 0x6400,
    TRG  = 0x6500,
    DBC  = 0xC000,
    FBC  = 0xC100,
    FIN  = 0xFF00;

void parse(uint16_t instr);