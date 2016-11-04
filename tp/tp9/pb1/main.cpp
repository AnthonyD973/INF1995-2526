#include "drive.h"

Timer0 timer0(P01_CLK8);
Timer1 timer1(P01_CLK8);

int main() {
    Parser.init();
    Parser.parse();
    
    for EVER {
        // Busy-wait
    }
    
    return 0;
}
