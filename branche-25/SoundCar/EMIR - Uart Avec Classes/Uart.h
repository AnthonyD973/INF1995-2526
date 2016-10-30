#ifndef DEBUG_H
#define DEBUG_H

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class Uart {
public:
  Uart();
  ~Uart();
  
  /**
   * @brief Initialise l'UART de l'ATMega324PA.
   */
  void initialisation();

  /**
   * @brief Transmet une donnée via l'interface UART du ATMega324PA.
   * @param[in] donnee Donnée de 8 bits à transmettre.
   */
  void transmission(uint8_t donnee);
  
  /**
   * @brief Reçoit un octet via l'interface UART du ATMega324PA.
   * @return Donnée de 8 bits reçue.
   */
  uint8_t reception();

};

#endif // DEBUG_H