#ifndef DEBUG_H
#define DEBUG_H

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "cstring.h"

class Uart {
public:
  Uart();
  ~Uart();
  
  /**
   * @brief Initialise l'UART de l'ATMega324PA.
   */
  void initialization();
  
  /**
   * @brief Transmet une donnée de plus d'un octet via l'UART.
   * @param[in] data Donnée de à transmettre.
   * @param[in] length Nombre d'octets de la donnée.
   */
  void transmission(uint8_t* data, size_t length = 1);
  
  /**
   * @brief Transmet une chaîne C via l'UART.
   * @param[in] str Chaîne à transmettre.
   */
  void transmissionCString(uint8_t* str);
  
  /**
   * @brief Reçoit un octet via l'interface UART du ATMega324PA.
   * @return Donnée de 8 bits reçue.
   */
  uint8_t reception();
  

};

#endif // DEBUG_H