#ifndef DEBUG_H
#define DEBUG_H

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

class Uart {
public:
  //Uart();
  //~Uart();
  
  static void initialization();
  
  static void transmission(uint8_t data); // Pour envoyer une constante par exemple
  static void transmission(const char* data, size_t length = 1);
  static void transmissionCString(const char* str);
  
  static uint8_t reception();
  static void reception(uint8_t*& data, size_t length);
};

#endif // DEBUG_H
