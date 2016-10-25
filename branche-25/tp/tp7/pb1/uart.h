#ifndef UART_H_
#define UART_H_ // INCLUDE GUARD

#define UNUSED(expr) do { (void)(expr); } while (0)

/**
 * \brief Cette fonction permet d'utiliser les fonctions de transfert via l'UART
 *        du micro controleur.
 */
void initialisationUART ( void ) {
	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous éviter des complications
	UBRR0H = 0;
	UBRR0L = 0xCF; // 11001111
	// permettre la reception et la transmission par le UART0
	UCSR0A = 0;
	UCSR0B = _BV(RXEN0) | _BV(TXEN0); // TXEN0: Transfer ENable on the channel 0
	                                  // RXEN0: Receive ENable on the channel 0
	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

/**
 * \brief Cette fonction transmet 1 octet via l'UART.
 */
void transmissionUART ( uint8_t donnee ) {
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = donnee;
}

/**
 * \brief Cette fonction reçoit 1 octet via l'UART.
 */
uint8_t receptionUART ( ) {
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

/**
 * \brief Cette fonction vide 1 octet du tampon de réception de l'UART.
 */
void viderTamponDeReceptionUART() {
	volatile unsigned char dummy = 0; UNUSED(dummy); // Pour enlever le warning
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

#endif // END OF INCLUDE GUARD
