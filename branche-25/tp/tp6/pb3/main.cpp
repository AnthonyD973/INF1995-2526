#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Uart.h"
#include "memoire_24.h"
#include "cstring.h"

#define EVER (;;)



/**
 * @brief Fonction principale du programme.
 */
int main() {
  Uart uart;
  Memoire24CXXX mem;
  
  /* Pour tester le programme
  uint8_t helloStr[] = {'H', 'e', 'l', 'l', 'o', '!', '\0', 0xff};
  
  mem.ecriture(0, helloStr, strlen(helloStr) + 2);
  */
  
  size_t i = 0;
  uint8_t cur;
  mem.lecture(i++, &cur);
  
  
  while(cur != 0xff) {
	uart.transmission(&cur);
	mem.lecture(i++, &cur);
  }
  
  
  return 0;
}
