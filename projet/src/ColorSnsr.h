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

typedef uint8_t TimerExternalClock;
typedef uint8_t ColorFilter;

#include <incl.h>
#include <lib.h>

// ---TimerExternalClock---
#define T0_FALLING_EDGE 0x06
#define T0_RISING_EDGE	0x07
#define T1_FALLING_EDGE	0x16
#define T1_RISING_EDGE	0x17

// ---ColorFilter---
#define FILTER_RED	 0x0
#define FILTER_BLUE  0x1
#define FILTER_CLEAR 0x2
#define FILTER_GREEN 0x3


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
     * @param[in]   tec     
     */
    static void init(TimerExternalClock tec);

    /**
     * @brief   
     * 
     * @return  
     */
    static uint8_t read(ColorFilter cf);

private:
    /**
     * @type    TimerExternalClock
     * @brief   Num�ro du compteur pour lequel utiliser l'horloge externe.
     */
    static TimerExternalClock _TEC;
    /**
     * @type    Timer*
     * @brief   Compteur utilis�.
     */
	static Timer* _TIMER

};

#endif  // COLOR_SNSR_H
