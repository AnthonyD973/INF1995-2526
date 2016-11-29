/**
 * @file    uart.h
 * 
 * @brief   Définition de UART qui permet de transmettre des données par USB
 * via l'interface USART du microcontrôleur.
 *
 * @authors Belhaddad, Emir Khaled
 * @authors Dandenault, Vincent
 * @authors Dentinger, Anthony
 * @authors Younis, Gergi
 * 
 * @date Automne 2016
 *
 * @copyright Code qui n'est sous aucune license.
 */

#ifndef UART_H
#define UART_H

#include "incl.h"
#include "typedefsLib.h"

typedef uint16_t size_t;

#ifdef  DEBUG

/**
 * @brief   Transmet des données via l'interface USART du microcontrôleur.
 * 
 * Cette classe utilise des sortes de tampons 'circulaires' : L'indice 0 est
 * après l'indice #BUFFER_SIZE-1.
 */
class UART {

public:
    /**
     * @brief   Taille maximale des buffer de réception et de transmission.
     */
    static const size_t BUFFER_SIZE = 128;
    
    /**
     * @brief   Cette fonction doit être appelée avant de pouvoir transmettre
     *          et/ou recevoir des données via l'UART.
     * @param[in]   baud    La "fréquence" des flux (reception/transmission)
     *                      de données (en baud).
     */
    static void init(uint16_t baud);
    /**
     * @brief   Cette fonction assigne le mode de communication de l'UART.
     * @param[int]  commMode    Le mode de communication.
     */
    static void setMode(CommMode commMode);
    /**
     * @brief   Cette fonction ajoute 1'octet au tampon de transmission.
     *          Si le tampon est plein, la fonction bloque le thread jusqu'à ce
     *          qu'il y ait de la place.
     * @param[in]   data    L'octet à transmettre.
     */
    static void transmit(uint8_t data);
    /**
     * @brief   Cette fonction ajoute les n octets du tableau passé en paramètre au
     *          tampon de transmission.
     *          Si le tampon est plein, la fonction bloque le thread jusqu'à ce
     *          qu'il y ait de la place.
     * @param[in]   data    Le tableau contenant les données à transmettre.
     * @param[in]   n       Le nombre d'octet du tableau à transmettre.
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
     * @brief   Cette fonction convertit un octet en la chaîne de caractère
     *          de sa représentation binaire.
     *          Si le tampon est plein, la fonction bloque le thread jusqu'à ce
     *          qu'il y a de la place.
     * @param[in]   data    Donnée de 8 bits à transmettre.
     */
    static void transmitBin(uint8_t data);
    /**
     * @brief   Cette fonction convertit un octet en la chaîne de caractère
     *          de sa représentation hexadécimale.
     *          Si le tampon est plein, la fonction bloque le thread jusqu'à ce
     *          qu'il y a de la place.
     * @param[in]   data    Donnée à transmettre.
     */
    static void transmitHex(uint8_t data);
    /**
     * @brief   Cette fonction renvoie le premier octet du tampon de reception.
     *          Si le tampon est vide, la fonction bloque le thread jusqu'à ce
     *          qu'il y ait des données. [Implementation de type 'queue']
     * @return  Le premier octet du tampon de réception.
     */
    static uint8_t receive();
    /**
     * @brief   Cette fonction remplit les n premiers octets d'un tableau passé
     *          en paramètre.
     *          Si le tampon n'a pas suffisament de données pour remplir le
     *          tableau, la fonction bloque le thread jusqu'à ce qu'il y ait
     *          assez de données. [Implementation de type 'queue']
     * @param[out]  data    Le tableau recevant les données reçues. Doit être
     *                      pré-initialisé avec une taille suffisante.
     * @param[in]   n       Le nombre de données à placer dans le tableau.
     */
    static void receive(uint8_t* data, size_t n);
    /**
     * @brief   Cette fonction vide le tampon de reception logiciel et matériel.
     */
    static void emptyRecBuffer();
    
    // =============================
    // = À N'UTILISER QUE DANS LES =
    // =  ROUTINES D'INTERRUPTION  =
    // =============================
    /** @cond FALSE */ // Ne pas documenter ces méthodes
    static void    _rec_push_back(volatile uint8_t data);
    static bool    _rec_full() { return _recBufferDataCount >= BUFFER_SIZE; }
    static size_t  _rec_size() { return _recBufferDataCount; }
    static volatile uint8_t _tra_pop();
    static bool    _tra_empty() { return _traBufferDataCount == 0; }
    static size_t  _tra_size() { return _traBufferDataCount; }
    /** @endcond */

private:
    /**
     * @brief   Tampon de réception.
     */
    static volatile uint8_t _recBuffer[BUFFER_SIZE];
    /**
     * @brief   Indice du début du tampon de réception.
     */
    static volatile size_t  _recBufferDataBeg;
    /**
     * @brief   Nombre d'octets dans le tampon de réception.
     */
    static volatile size_t  _recBufferDataCount;
    /**
     * @brief   Tampon de transmission.
     */
    static volatile uint8_t _traBuffer[BUFFER_SIZE];
    /**
     * @brief   Indice du début du tampon de transmission.
     */
    static volatile size_t  _traBufferDataBeg;
    /**
     * @brief   Nombre d'octets dans le tampon de transmission.
     */
    static volatile size_t  _traBufferDataCount;
    
    /**
     * @brief   Définit si l'UART est initialisée ou non.
     */
    static bool     _initialized;
    /**
     * @brief   Mode de communication actuel.
     */
    static CommMode _commMode;
    
    /** @cond FALSE */ // Ne pas documenter ces méthodes
    static volatile uint8_t _rec_pop();
    static void    _tra_push_back(volatile uint8_t data);
    /** @endcond */
};

#else // !DEBUG
// Définition d'une classe UART qui ne fait rien pour optimiser la mémoire et
// la performance.
class UART {
public:
    static const size_t BUFFER_SIZE = 0;
    static void init(uint16_t baud) { }
    static void setMode(CommMode commMode) { }
    static void transmit(uint8_t data) { }
    static void transmit(const uint8_t* data, size_t n) { }
    static void transmitCStr(const char* str) { }
    static void transmitBin(uint8_t data) { }
    static void transmitHex(uint8_t data) { }
    static uint8_t receive(void) { return 0; }
    static void receive(uint8_t* data, size_t n) { }
    static void emptyRecBuffer(void) { }
    
    static void    _rec_push_back(volatile uint8_t data) { }
    static bool    _rec_full(void) { return true; }
    static size_t  _rec_size(void) { return 0; }
    static volatile uint8_t _tra_pop(void) { return 0; }
    static bool    _tra_empty(void) { return true; }
    static size_t  _tra_size(void) { return 0; }
};
#endif // !DEBUG
#endif // UART_H
