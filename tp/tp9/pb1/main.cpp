#include <lib.h>
#include <timer.h>
#include <buzzer.h>
#include <uart.h>
#include "parser.h"


int main() {
    DDRB = DDRD = 0xFF;
    Parser::init();
    Parser::parse();
    
    for EVER {
        // Busy-wait
    }
    
    return 0;
}
