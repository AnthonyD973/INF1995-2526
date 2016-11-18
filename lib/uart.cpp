#ifdef DEBUG
#include "uart.h"

volatile uint8_t  UART::_recBufferDataBeg = 0;
volatile uint8_t  UART::_traBufferDataBeg = 0;
volatile size_t  UART::_recBufferDataCount = 0;
volatile size_t  UART::_traBufferDataCount = 0;
volatile uint8_t UART::_recBuffer[UART::BUFFER_SIZE];
volatile uint8_t UART::_traBuffer[UART::BUFFER_SIZE];

bool UART::_initialized = false;

ISR (USART0_RX_vect) {
    volatile uint8_t buff;
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
    UBRR0L = (F_CPU / (16*baud) - 1);
    // permettre la reception et la transmission par le UART0
    UCSR0A = 0;
    UCSR0B = _BV(RXEN0) | _BV(TXEN0)   // TXEN0: Transfer ENable on the channel 0
                        ;//| _BV(RXCIE0); // RXCIE0: Receive Complet Interrupt Enable on the channel 0
                                       // RXEN0: Receive ENable on the channel 0
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
    DDRD |= 0x02;
    _recBufferDataBeg = 0;
    _recBufferDataCount = 0;
    _initialized = true;
}

/**
 * @brief   Utilisée dans les routine ISR de réception.
 */
inline void UART::_rec_push_back(volatile uint8_t data) {//*
    // Si on recoit une donnée mais que l'on a plus de place...
    if (_rec_full())
        return; // On la jette.
    _recBuffer[(_recBufferDataBeg + _recBufferDataCount++) % BUFFER_SIZE] = data; // Sinon, on l'enregistre à la fin du buffer.//*/
}

/**
 * @brief   Utilisée dans les fonctions de récupération des données reçus.
 */
inline volatile uint8_t UART::_rec_pop(void) {
    volatile uint8_t ret = 0;//*
    // On attend qu'une donnée soit reçue...
    while(_recBufferDataCount == 0);
    ret = _recBuffer[_recBufferDataBeg];
    // Implémentation de type queue (FIFO)
    --_recBufferDataCount;
    ++_recBufferDataBeg %= BUFFER_SIZE;//*/
    
    return ret;
}

/**
 * @brief   Utilisée dans les fonctions de transmission de données.
 */
inline void UART::_tra_push_back(volatile uint8_t data) {//*
    // On attend d'avoir de l'espace pour y placer les données.
    while (_traBufferDataCount >= BUFFER_SIZE);
    _traBuffer[(_traBufferDataBeg + _traBufferDataCount++) % BUFFER_SIZE] = data;//*/
}

/**
 * @brief   Utilisée dans les routine ISR de transmission.
 */
inline volatile uint8_t UART::_tra_pop(void) {
    volatile uint8_t ret = 0;//*
    // S'il n'y a plus rien à transmettre...
    if (_tra_empty()) {
        UCSR0B &= ~_BV(UDRIE0); // On arrête la routine d'envoie et...
        return uint8_t(-1); // On transmet une valeur par défault! [Erreur]
    }
    ret = _traBuffer[_traBufferDataBeg];
    // Implémentation de type queue (FIFO)
    --_traBufferDataCount;
    ++_traBufferDataBeg %= BUFFER_SIZE;//*/
    
    return ret;
}

void UART::transmit(uint8_t data) {//*
    _tra_push_back(data);
    UCSR0B |= _BV(UDRIE0);/*/ // On démarre les interruptions qui s'executes
                           // lorsque le tampon de transmission (matériel) est
                           // près à transmettre de nouvelles données.
    if (!_initialized) return;
    while ( !( UCSR0A & (1<<UDRE0)) );
    UDR0 = data;//*/
}

/**
 * @brief   
 * @param[in]  data    
 * @param[in]   n       
 */
void UART::transmit(const uint8_t* data, size_t n) {//*
    for (size_t i = 0; i < n; ++i)
        _tra_push_back(data[i]);
    UCSR0B |= _BV(UDRIE0);/*/ // On démarre les interruptions qui s'exécutes
                           // lorsque le tampon de transmission (matériel) est
                           // près à transmettre de nouvelles données.
    if (!_initialized) return;
    while ( !( UCSR0A & (1<<UDRE0)) );
    for (size_t i = 0; i < n; ++i)
        UDR0 = data[i];//*/
}

/**
 * @brief   Transmet une chaîne C via l'UART.
 * @param[in]  str  Chaîne à transmettre
 */
void UART::transmitCStr(const char* str) {
    transmit((const uint8_t*&)str, strlen(str)+1);
}

/**
 * @brief Transmet les bits d'un octet via l'interface UART du ATMega324PA.
 * @param[in] data      Donnée de 8 bits à transmettre.
 */
void UART::transmitBin(uint8_t data) {
    for (uint8_t i = 0; i < 8; ++i) {
        transmit((data & 0x80) >> 7 | 0x30);
        data <<= 1;
    }
}


uint8_t UART::receive(void) {/*
    return _rec_pop();/*/
    if (!_initialized) return 0;
    while ( !(UCSR0A & (1<<RXC0)) );
    return UDR0;//*/
}

/**
 * @brief   
 * @param[out]  data    
 * @param[in]   n       
 */
void UART::receive(uint8_t* data, size_t n) {/*
    for (size_t i = 0; i < n; ++i)
        data[i] = _rec_pop();/*/
    if (!_initialized) return;
    for (size_t i = 0; i < n; ++i) {
        while ( !(UCSR0A & (1<<RXC0)) );
        data[i] = UDR0;
    }//*/
}

void UART::emptyRecBuffer(void) {
    _recBufferDataCount = 0;
    
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable" // Ignorer le warning pour la variable 'dummy' : c'est bien ce que l'on veut faire.
    volatile unsigned char dummy;
    while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}
#endif
