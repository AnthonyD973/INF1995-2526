#ifndef UART_H_
#define UART_H_ // INCLUDE GUARD

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

/**
 * @brief   Puisque c'est une classe qui agit comme interface de communication
 *          et qu'aucune information sur le protocole UART n'a besoin d'être 
 *          enregistrée, on en fait une classe 'statique' pour que l'on n'ait
 *          pas besoin de l'instancier partout où l'on en a besoin. Il suffit
 *          juste d'inclure le fichier d'entête et d'utiliser les fonctions.
 *          Cette classe utilise des tampon de type 'queue'.
 */
class UART {

public:
    /**
     * @brief   Taille maximale des buffer de réception et de transmission.
     */
    static const size_t BUFFER_SIZE = 256;
    
    /**
     * @brief   Cette fonction doit être appelée avant de pouvoir transmettre
     *          et/ou recevoir des données via l'UART.
     * @param[in]   baud    La "fréquence" des flux (reception/transmission)
     *                      de données (en baud).
     */
    static void init(uint16_t baud);
    /**
     * @brief   Cette fonction ajoute 1 octet au tampon de transmission.
     *          Si le tampon est plein, la fonction bloque le thread jusqu'à ce
     *          qu'il y a de la place.
     * @param[in]   data    L'octet à transmettre.
     */
    static void transmit(uint8_t data);
    /**
     * @brief   Cette fonction ajoute n octet(s) du tableau passé en paramètre au
     *          tampon de transmission.
     *          Si le tampon est plein, la fonction bloque le thread jusqu'à ce
     *          qu'il y a de la place.
     * @param[in]   data    Le tableau contenant les données à transmettre.
     * @param[in]   n       Le nombre d'octet du tableau à transmettre. Commence
     *                      de l'index 0 jusqu'à l'index n-1;
     */
    static void transmit(const uint8_t* data, size_t n);
    /**
     * @brief   Cette fonction ajoute une chaîne de caractères au tampon de
     *          transmission.
     *          Si le tampon est plein, la fonction bloque le thread jusqu'à ce
     *          qu'il y a de la place.
     * @param[in]   str     La chaîne de caratères à transmettre.
     */
    static void transmitCStr(const char* str);
    /**
     * @brief   Cette fonction convertie un octet en une chaîne de caractère
     *          contenant sa représentation binaire sur 8 bits.
     *          Si le tampon est plein, la fonction bloque le thread jusqu'à ce
     *          qu'il y a de la place.
     * @param[in]   data    Donnée à transmettre.
     */
    static void transmitBin(uint8_t data);
    /**
     * @brief   Cette fonction renvoie le premier octet du tampon de reception.
     *          Si le tampon est vide, la fonction bloque le thread jusqu'à ce
     *          qu'il y ait des données. [Implementation de type 'queue']
     * @return  Le premier octet du tampon de réception.
     */
    static uint8_t receive(void);
    /**
     * @brief   Cette fonction remplie les n premiers octet d'un tableau passé
     *          en paramètre.
     *          Si le tampon n'a pas suffisament de données pour remplir le
     *          tableau, la fonction bloque le thread jusqu'à ce qu'il y ait
     *          assez de données. [Implementation de type 'queue']
     * @param[out]  data    Le tableau recevant les données reçu. Doit être
     *                      pré-initialisé avec une taille suffisante.
     * @param[in]   n       Le nombre de donnée à placer dans le tableau.
     */
    static void receive(uint8_t* data, size_t n);
    /**
     * @brief   Cette fonction vide le tampon de reception logiciel et matériel.
     */
    static void emptyRecBuffer(void);
    
    static void    _rec_push_back(uint8_t data);
    static bool    _rec_full(void) { return _recBufferDataCount >= BUFFER_SIZE; }
    static size_t  _rec_size(void) { return _recBufferDataCount; }
    static volatile uint8_t _tra_pop(void);// "pop" le premier élément du tampon
    static bool    _tra_empty(void) { return _traBufferDataCount == 0; }
    static size_t  _tra_size(void) { return _traBufferDataCount; }

private:
    static volatile uint8_t _recBuffer[BUFFER_SIZE];
    static volatile size_t  _recBufferDataCount;
    static volatile uint8_t _traBuffer[BUFFER_SIZE];
    static volatile size_t  _traBufferDataCount;
    
    static volatile uint8_t _rec_pop(void);// "pop" le premier élément du tampon
    static void    _tra_push_back(uint8_t data);
};

/*
void initialisationUART ( void );
void transmissionUART ( uint8_t donnee );
uint8_t receptionUART ( );
void viderTamponDeReceptionUART();//*/

#endif // END OF INCLUDE GUARD
