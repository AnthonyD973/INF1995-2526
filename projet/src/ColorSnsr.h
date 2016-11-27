/* 
 * Classe permettant d'utiliser le capteur de couleur TAOS TCS230.
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
#define COLOR_INCERT 0x30 // = ±48

/**
 * @class   ColorSnsr
 * 
 * @brief   Classe à utiliser pour obtenir la valeur de couleur lue par le
 *          capteur de couleur TAOS TCS230. La classe se charge de l'interprétation
 *          de la fréquence que fournit le capteur et donne une valeur
 *          normalisée de l'intensité de la couleur choisie (voir <ColorSnsr::read>).
 */
class ColorSnsr {

public:
    /**
     * @brief   Initialisation du détecteur. À appeler au début du programme.
     * 
     * @param[in]   tec     Le compteur sur lequel la sortie du capteur est
     *      branchée.
     */
    static void init(TimerExternalClock tec);

    /**
     * @brief   Détermine la couleur dominante vue par le capteur.
     * 
     * @return  La couleur dominante.
     */
    static ColorRead read();

private:
    /**
     * @brief   Masque du bit de LED du capteur.
     */
    static uint8_t _LED_MASK;
    /**
     * @brief   Numéro du bit de S2.
     */
    static const uint8_t _S2;
    /**
     * @brief   Numéro du bit de S0.
     */
    static const uint8_t _S0;
    /**
     * @brief   Compteur utilisé.
     */
	static Timer* _TIMER;
    /**
     * @brief   Seuil de rouge qui est dépassé lorsque le capteur lit du blanc.
     */
    static uint16_t _RED_THRESH;
    /**
     * @brief   Seuil de vert qui est dépassé lorsque le capteur lit du blanc.
     */
    static uint16_t _GREEN_THRESH;
    /**
     * @brief   Seuil de bleu qui est dépassé lorsque le capteur lit du blanc.
     */
    static uint16_t _BLUE_THRESH;
    
    /**
     * @brief Initialise les constantes *_THRESH pour déceler blanc.
     */
    static void _initializeConstants();
    
};

#endif  // COLOR_SNSR_H
