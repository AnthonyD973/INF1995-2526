/* 
 * Classe permettant l'acc�s au capteur de couleur TAOS TCS230.
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Emir Khaled Belhaddad, Anthony Dentinger,
 * Gergi Younis et Vincent Dandenault
 * 2016
 *
 * Code qui n'est sous aucune license.
 *
 */

#ifndef COLOR_SNSR_H
#define COLOR_SNSR_H

#include <incl.h>

typedef uint8_t TimerExternalClock;
typedef uint8_t ColorRead;
#include <lib.h>
#include <timer.h>

// ---TimerExternalClock---
#define T0_FALLING_EDGE 0x06
#define T0_RISING_EDGE	0x07
#define T1_FALLING_EDGE	0x16
#define T1_RISING_EDGE	0x17

// ---ColorRead---
#define COLOR_READ_RED	 0x0 // S3 = 0 , S2 = 0
#define COLOR_READ_WHITE 0x1 // S3 = 0 , S2 = 1
#define COLOR_READ_BLUE  0x2 // S3 = 1 , S2 = 0
#define COLOR_READ_GREEN 0x3 // S3 = 1 , S2 = 1

// ---Incertitude sur la couleur---
#define COLOR_INCERT 0xA // = ±10

/**
 * @class   ColorSnsr
 * 
 * @brief   Classe � utiliser pour obtenir la valeur de couleur lue par le
 *          capteur de couleur TAOS TCS230. La classe se charge de l'interpr�tation
 *          de la fr�quence que fournit le capteur et donne une valeur
 *          normalis�e de l'intensit� de la couleur choisie (voir <ColorSnsr::read>).
 */
class ColorSnsr {

public:
    /**
     * @brief   Initialisation du d�tecteur. � appeler au d�but du programme.
     *          Met en entr�e le num�ro du compteur pour lequel utiliser  du port A o� le signal
     *          analogique du capteur de distance est re�u.
     * 
     * @param[in]   tec     Le compteur sur lequel la sortie du capteur est branch�e.
     *  
     *                      La valeur peut prendre une de celles-ci
     *                      [T0_FALLING_EDGE, T0_RISING_EDGE, T1_FALLING_EDGE, T1_RISING_EDGE],
     *                      d�finies ci-dessus.
     */
    static void init(TimerExternalClock tec);

    /**
     * @brief   D�termine la couleur dominante vue par le capteur.
     * 
     * @return  La couleur dominante.
     */
    static ColorRead read();

private:
    /**
     * @brief   Masque de l'horloge externe.
     */
    static uint8_t _LED_MASK;
    /**
     * @brief   Num�ro du bit de S2.
     */
    static const uint8_t _S2;
    /**
     * @brief   Num�ro du bit de S0.
     */
    static const uint8_t _S0;
    /**
     * @brief   Compteur utilis�.
     */
	static Timer* _TIMER;
    /**
     * @brief   Constantes d�cid�es � l'Initialisation.
     */
    static const uint16_t
        _RED_THRESH,
        _GREEN_THRESH,
        _BLUE_THRESH;
    
    static void _initializeConstants();
    
};

#endif  // COLOR_SNSR_H
