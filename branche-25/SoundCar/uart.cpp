#include "uart.h"

volatile size_t  UART::_recBufferDataCount = 0;
volatile size_t  UART::_traBufferDataCount = 0;
volatile uint8_t UART::_recBuffer[UART::BUFFER_SIZE];
volatile uint8_t UART::_traBuffer[UART::BUFFER_SIZE];

ISR (USART0_RX_vect) {
    uint8_t buff;
    while (UCSR0A & (1<<RXC0)) {
        buff = UDR0;
        UART::_rec_push_back(buff);
    }
}

ISR (USART0_UDRE_vect) {
    // S'il n'y a plus rien à transmettre...
    if (UART::_tra_empty()) {
        UCSR0B &= ~_BV(UDRIE0);// On arrête les interruptions de ce type-ci
                               // (Voir documentation p.175 s.19.7.3)
        return;
    }
    else
        UDR0 = UART::_tra_pop();
}

void UART::init(uint16_t baud) {//*
	UBRR0H = (F_CPU / (16*baud) - 1)>>8 & 0x0f; // Voir manuel p.170
	UBRR0L = (F_CPU / (16*baud) - 1);//*/
	// permettre la reception et la transmission par le UART0
	UCSR0A = 0;
	UCSR0B = _BV(RXEN0) | _BV(TXEN0)   // TXEN0: Transfer ENable on the channel 0
	                    | _BV(RXCIE0); // RXCIE0: Receive Complet Interrupt Enable on the channel 0
	                                   // RXEN0: Receive ENable on the channel 0
	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

/**
 * @brief   Utilisée dans les routine ISR de réception.
 */
inline void UART::_rec_push_back(uint8_t data) {
    // Si on recoit une donnée mais que l'on a plus de place...
    if (_rec_full()) 
        return; // On la jette.
    _recBuffer[_recBufferDataCount++] = data; // Sinon, on l'enregistre à la fin du buffer.
}

/**
 * @brief   Utilisée dans les fonctions de récupération des données reçus.
 */
inline volatile uint8_t UART::_rec_pop(void) {
    // On attend qu'une donnée soit reçue...
    while(_recBufferDataCount == 0);
    volatile uint8_t ret = _recBuffer[0];
    // Implémentation de type queue (FIFO)
    _recBufferDataCount--;
    for (volatile size_t i = 0; i < _recBufferDataCount; ++i) {
        _recBuffer[i] = _recBuffer[i + 1];
    }
    
    return ret;
}

/**
 * @brief   Utilisée dans les fonctions de transmission de données.
 */
inline void UART::_tra_push_back(uint8_t data) {
    // On attend d'avoir de l'espace pour y placer les données.
    while (_traBufferDataCount >= BUFFER_SIZE);
    _traBuffer[_traBufferDataCount++] = data;
}

/**
 * @brief   Utilisée dans les routine ISR de transmission.
 */
inline volatile uint8_t UART::_tra_pop(void) {
    // S'il n'y a plus rien à transmettre...
    if (_tra_empty())
        return -1; // On lui transmet une valeur par défault! [Erreur]
    volatile uint8_t ret = _traBuffer[0];
    // Implémentation de type queue (FIFO)
    _traBufferDataCount--;
    for (volatile size_t i = 0; i < _traBufferDataCount; ++i) {
        _traBuffer[i] = _traBuffer[i + 1];
    }
    
    return ret;
}

void UART::transmit(uint8_t data) {
    _tra_push_back(data);
    UCSR0B |= _BV(UDRIE0); // On démarre les interruptions qui s'executes
                           // lorsque le tampon de transmission est près à
                           // transmettre de nouvelles données.
}

/**
 * @brief   
 * @param[out]  data    
 * @param[in]   n       
 */
void UART::transmit(uint8_t* data, size_t n) {
    for (size_t i = 0; i < n; ++i)
        _tra_push_back(data[i]);
    UCSR0B |= _BV(UDRIE0); // On démarre les interruptions qui s'executes
                           // lorsque le tampon de transmission est près à
                           // transmettre de nouvelles données.
}

uint8_t UART::receive(void) {
    return _rec_pop();
}

/**
 * @brief   
 * @param[out]  data    
 * @param[in]   n       
 */
void UART::receive(uint8_t* data, size_t n) {
    for (size_t i = 0; i < n; ++i)
        data[i] = _rec_pop();
}

void UART::emptyRecBuffer(void) {
    _recBufferDataCount = 0;
    volatile unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

/**
 * \brief Cette fonction permet d'utiliser les fonctions de transfert via l'UART
 *        du micro controleur.
 */ /*
void initialisationUART ( void ) {
	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous éviter des complications
	UBRR0H = 0;
	UBRR0L = 0xCF; // 11001111
	// permettre la reception et la transmission par le UART0
	UCSR0A = 0;
	UCSR0B = _BV(RXEN0) | _BV(TXEN0)   // TXEN0: Transfer ENable on the channel 0
	                    | _BV(RXCIE0); // RXCIE0: Receive Complet Interrupt Enable on the channel 0
	                                   // RXEN0: Receive ENable on the channel 0
	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}//*/

/**
 * \brief Cette fonction transmet 1 octet via l'UART.
 */ /*
void transmissionUART ( uint8_t donnee ) {
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = donnee;
}//*/

/**
 * \brief Cette fonction reçoit 1 octet via l'UART.
 */ /*
uint8_t receptionUART ( ) {
	// Wait for data to be received
	while ( !(UCSR0A & (1<<RXC0)) );
	// Get and return received data from buffer
	return UDR0;
}//*/

/**
 * \brief Cette fonction vide 1 octet du tampon de réception de l'UART.
 */ /*
void viderTamponDeReceptionUART() {
	volatile unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}//*/
