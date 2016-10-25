#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "memoire_24.h"

#define EVER (;;)

/**
 * @brief Constantes pour la DEL.
 */
const uint8_t
    C_OFF   = 0x00,
    C_GREEN = 0x01,
    C_RED   = 0x02,
    C_AMBER = 0xFF;


/**
 * @brief Compare deux chaînes C.
 * 
 * @param[in] str1 Chaîne à comparer.
 * @param[in] str2 Chaîne à comparer.
 * 
 * @return true si le test est concluant.
 */
bool strcmp(uint8_t* str1, uint8_t* str2) {
  uint16_t i = 0;
  bool areEqual = true;
  
  while (str1[i] != '\0' && str2[i] != '\0') {
	if (str1[i] != str2[i]) {
	  areEqual = false;
	  break;
	}
	++i;
  }
  
  // Traiter le cas où une des deux chaînes est vide.
  if (str1[i] != str2[i]) {
	areEqual = false;
  }
  
  return areEqual;
}


/**
 * @brief Fonction principale du programme.
 */
int main() {
  
  DDRB = 0x03;
  
  const uint8_t STR_LEN = 39;
  uint8_t readStr[STR_LEN+1], writtenStr[STR_LEN+1] = "*E*C*O*L*E* *P*O*L*Y*T*E*C*H*N*I*Q*U*E*";
  
  Memoire24CXXX mem;
  
  mem.ecriture(0, writtenStr, STR_LEN+1);
  _delay_ms(5.0);
  mem.lecture(0, readStr, STR_LEN+1);
  
  if (strcmp(writtenStr, readStr)) {
	PORTB = C_GREEN;
  }
  else {
	PORTB = C_RED;
  }
  
    
    return 0;
}
