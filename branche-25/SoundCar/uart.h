#ifndef UART_H_
#define UART_H_ // INCLUDE GUARD

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

const size_t UART_BUFFER_SIZE = 256;

/**
 * @brief   Puisque c'est une classe qui agit comme interface de communication
 *          et qu'aucune information sur le protocole UART n'a besoin d'être 
 *          enregistrée, on en fait une classe 'statique' pour que l'on n'ait
 *          pas besoin de l'instancier partout où l'on en a besoin. Il suffit
 *          juste d'inclure le fichier d'entête.
 */
class UART {

public:
    static const size_t BUFFER_SIZE = 256;
    
    static void init(uint16_t baud);
    static void transmit(uint8_t data);
    static void transmit(uint8_t* data, size_t n);
    static uint8_t receive(void);
    static void receive(uint8_t* data, size_t n);
    static void emptyRecBuffer(void);
    
    static void    _rec_push_back(uint8_t data);
    static volatile uint8_t _rec_pop(void); // pop from the front;
    static bool    _rec_full(void) { return _recBufferDataCount >= BUFFER_SIZE; }
    static size_t  _rec_size(void) { return _recBufferDataCount; }
    static void    _tra_push_back(uint8_t data);
    static volatile uint8_t _tra_pop(void); // pop from the front;
    static bool    _tra_empty(void) { return _traBufferDataCount == 0; }
    static size_t  _tra_size(void) { return _traBufferDataCount; }

private:
    static volatile uint8_t _recBuffer[BUFFER_SIZE];
    static volatile size_t  _recBufferDataCount;
    static volatile uint8_t _traBuffer[BUFFER_SIZE];
    static volatile size_t  _traBufferDataCount;
};

/*
void initialisationUART ( void );
void transmissionUART ( uint8_t donnee );
uint8_t receptionUART ( );
void viderTamponDeReceptionUART();//*/

#endif // END OF INCLUDE GUARD
