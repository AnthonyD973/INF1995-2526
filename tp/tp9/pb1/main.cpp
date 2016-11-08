#include <lib.h>
#include <timer.h>
#include <buzzer.h>
//#include <uart.h>
#include "parser.h"

Timer0 timer0(P01_CLK8);
Timer1 timer1(P01_NO_CLK);
//Timer2 timer2(P2_CLK8);


int main() {
    DDRB = DDRD = 0xFF;
    Parser::init();
    Parser::parse();
    
    for EVER {
        // Busy-wait
    }
    
    return 0;
}
