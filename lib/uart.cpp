#ifdef DEBUG
#include "uart.h"

// +=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=+
// | Initialisation des variables statiques |
// +=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=+

volatile size_t  UART::_recBufferDataBeg = 0;
volatile size_t  UART::_traBufferDataBeg = 0;
volatile size_t  UART::_recBufferDataCount = 0;
volatile size_t  UART::_traBufferDataCount = 0;
volatile uint8_t UART::_recBuffer[UART::BUFFER_SIZE];
volatile uint8_t UART::_traBuffer[UART::BUFFER_SIZE];

bool     UART::_initialized = false;
CommMode UART::_commMode    = UART_INTERRUPT;

// Implementation de strlen de la librairie <string.h> qui nous permet de ne pas
// avoir à inclure toute la librairie.
static size_t strlen(const char* str) {
    size_t len = 0;
    while (*str != '\0') {
        ++str;
        ++len;
    }
    return len;
}

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
    cli();
    
    UBRR0H = (F_CPU / (16*baud) - 1)>>8 & 0x0f; // Voir manuel p.170
    UBRR0L = (F_CPU / (16*baud) - 1);
    // permettre la reception et la transmission par le UART0
    UCSR0A = 0;
    UCSR0B = _BV(RXEN0) | _BV(TXEN0); // TXEN0: Transfer ENable on the channel 0
                                      // RXEN0: Receive ENable on the channel 0
    // RXCIE0: Receive Complet Interrupt Enable on the channel 0
    _MASK(UCSR0B, (_commMode) ? ~_BV(RXCIE0) : _BV(RXCIE0), _BV(RXCIE0));
    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
    DDRD |= 0x02;
    _recBufferDataBeg = 0;
    _recBufferDataCount = 0;
    _initialized = true;
    
    sei();
}

void UART::setMode(CommMode commMode) {
    cli();
    
    _commMode = commMode;
    _MASK(UCSR0B, (commMode) ? ~_BV(RXCIE0) : _BV(RXCIE0), _BV(RXCIE0));
    
    sei();
}

/**
 * @brief   Utilisée dans les routine ISR de réception.
 */
__attribute__ ((always_inline))
inline void UART::_rec_push_back(volatile uint8_t data) {//*
    if (!_initialized) return;
    // Si on recoit une donnée mais que l'on a plus de place...
    if (_rec_full())
        return; // On la jette.
    // Sinon, on l'enregistre à la fin du buffer.
    _recBuffer[(_recBufferDataBeg + _recBufferDataCount++) % BUFFER_SIZE] = data;//*/
}

/**
 * @brief   Utilisée dans les fonctions de récupération des données reçus.
 */
__attribute__ ((always_inline))
inline volatile uint8_t UART::_rec_pop(void) {
    if (!_initialized) return 0;
    
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
__attribute__ ((always_inline))
inline void UART::_tra_push_back(volatile uint8_t data) {
    if (!_initialized) return;
    // On attend d'avoir de l'espace pour y placer les données.
    while (_traBufferDataCount >= BUFFER_SIZE);
    _traBuffer[(_traBufferDataBeg + _traBufferDataCount++)
        % BUFFER_SIZE] = data;
}

/**
 * @brief   Utilisée dans les routine ISR de transmission.
 */
__attribute__ ((always_inline))
inline volatile uint8_t UART::_tra_pop(void) {
    if (!_initialized) return 0;
    
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

void UART::transmit(uint8_t data) {
    if (!_initialized) return;
    
    if (_commMode == UART_INTERRUPT) {
        _tra_push_back(data);
        UCSR0B |= _BV(UDRIE0); // On démarre les interruptions qui s'executes
                               // lorsque le tampon de transmission (matériel) est
                               // près à transmettre de nouvelles données.
    }
    else {
        while ( !( UCSR0A & (1<<UDRE0)) );
        UDR0 = data;
    }
}

void UART::transmit(const uint8_t* data, size_t n) {
    if (!_initialized) return;
    
    if (_commMode == UART_INTERRUPT) {
        for (size_t i = 0; i < n; ++i)
            _tra_push_back(data[i]);
        UCSR0B |= _BV(UDRIE0); // On démarre les interruptions qui s'exécutes
                               // lorsque le tampon de transmission (matériel)
                               // est prêt à transmettre de nouvelles données.
    }
    else {
        for (size_t i = 0; i < n; ++i) {
            while (!( UCSR0A & (1<<UDRE0)));
            UDR0 = data[i];
        }
    }
}

void UART::transmitCStr(const char* str) {
    if (!_initialized) return;
    transmit((const uint8_t*&)str, strlen(str)+1);
}

void UART::transmitBin(uint8_t data) {
    if (!_initialized) return;
    for (uint8_t i = 0; i < 8; ++i) {
        transmit((data & 0x80) >> 7 | '0');
        data <<= 1;
    }
}

/**
 * @brief Transmet les chiffires hexa d'un octet via l'interface UART du ATMega324PA.
 * @param[in] data      Donnée de 8 bits à transmettre.
 */
void UART::transmitHex(uint8_t data) {
    for (uint8_t i = 0; i < 2; ++i) {
        uint8_t hexNum = (data & 0xF0) >> 4;
        if (hexNum < 10) { // 0-9
            uint8_t charToDisplay = hexNum | '0';
        }
        else { // A-F
          uint8_t charToDisplay = (hexNum - 10) | 'A';
        }
        transmit(charToDisplay);
        data <<= 4;
    }
}


uint8_t UART::receive(void) {
    if (!_initialized) return 0;
    
    if (_commMode == UART_INTERRUPT) {
        return _rec_pop();
    }
    else {
        while ( !(UCSR0A & (1<<RXC0)) );
        return UDR0;
    }
}

void UART::receive(uint8_t* data, size_t n) {
    if (!_initialized) return;
    
    if (_commMode == UART_INTERRUPT) {
        for (size_t i = 0; i < n; ++i)
            data[i] = _rec_pop();
    }
    else {
        for (size_t i = 0; i < n; ++i) {
            while (!(UCSR0A & (1<<RXC0)));
            data[i] = UDR0;
        }
    }
}

void UART::emptyRecBuffer(void) {
    if (_commMode == UART_INTERRUPT)
        _recBufferDataCount = 0;
    
    // Ignorer le warning pour la variable 'dummy' : c'est bien ce que
    // l'on veut faire.
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable" 
    volatile unsigned char dummy;
    while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}
#endif
