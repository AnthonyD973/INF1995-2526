#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Uart.h"
#include "cstring.h"

#define EVER (;;)



/**
 * @brief Fonction principale du programme.
 */
int main() {
  Uart uart;
  
  uint8_t mots[] = "Hello, World!\nThis is iRobot.\n";

  uint8_t i;
  for ( i = 0; i < 100; i++ ) {
	uart.transmissionCString(mots);
  }
  
  
  return 0;
}
