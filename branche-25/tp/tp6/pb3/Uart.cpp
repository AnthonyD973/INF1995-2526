#include "Uart.h"
#include "cstring.h"

#define IS_TRANSMISSION_FINISED (UCSR0A & (1 << UDRE0))
#define IS_RECEPTION_FINISED (UCSR0A & (1<<RXC0))


Uart::Uart() {
  initialization();
}

Uart::~Uart() { }

/**
 * @brief Initialise l'UART de l'ATMega324PA.
 */
void Uart::initialization() {

  // 2400 Bd.
  UBRR0H = 0;
  UBRR0L = 0xCF;

  // permettre la reception et la transmission par le UART0
  UCSR0A = 0; // voir pp. 185-186 de doc Atmel
         // Recevoir     Transmettre   data 8 bits
  UCSR0B =  _BV(RXEN0) | _BV(TXEN0)/*| _BV(UCSZ02)*/; // voir pp. 186-187 de doc Atmel
  
  // Format des trames: 8 bits, 1 stop bits, none parity
        // Asynchrone        data 8 bits       1 stop bit     none parity
  UCSR0C = 0x00 << UMSEL00 | 0x03 << UCSZ00 |/*_BV(USBS0) |*/ 0x00 << UPM00; // voir pp. 187-188 de doc Atmel
}

/**
 * @brief Transmet un octet via l'interface UART du ATMega324PA.
 * @param[in] donnee Donnée de 8 bits à transmettre.
 */
void Uart::transmission(uint8_t* data, size_t length) {
  for (size_t i = 0; i < length; ++i) {
	while (!IS_TRANSMISSION_FINISED);
	UDR0 = data[i];
  }
}

/**
 * @brief Transmet une chaîne C via l'UART.
 * @param[in] str Chaîne à transmettre.
 */
void Uart::transmissionCString(uint8_t* str) {
  transmission(str, strlen(str)+1);
}

/**
 * @brief Reçoit un octet via l'interface UART du ATMega324PA.
 * @return Donnée de 8 bits reçue.
 */
uint8_t Uart::reception() {
	while (!IS_RECEPTION_FINISED);
	return UDR0;
}