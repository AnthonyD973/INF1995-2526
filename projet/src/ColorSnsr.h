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
#include <lib.h>
#include <timer.h>

#include "typedefs.h"

#ifndef COLOR_SEQ_MAX
    #define COLOR_SEQ_MAX   3
#endif // COLOR_SEQ_MAX


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
    static ShapeColor read();

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
     * @brief   Seuil de tolérance permettant de décider qu'une couleur est
     *      prédominante par rapport à une autre.
     */
    static const uint16_t COLOR_UNCERT;
    
    /**
     * @brief   Seuil de rouge qui est dépassé lorsque le capteur lit du blanc.
     */
    static uint16_t _RED_THRESH_FOR_WHITE;
    /**
     * @brief   Seuil de vert qui est dépassé lorsque le capteur lit du blanc.
     */
    static uint16_t _GREEN_THRESH_FOR_WHITE;
    /**
     * @brief   Seuil de bleu qui est dépassé lorsque le capteur lit du blanc.
     */
    static uint16_t _BLUE_THRESH_FOR_WHITE;
    
    /**
     * @brief   Initialise les constantes *_THRESH pour déceler blanc.
     */
    static void _initializeConstants();
    
    /**
     * @brief   Change un tableau de couleurs selon les couleurs lues et selon
     *      un prédicat binaire.
     */
    template <class Operator>
    static void _readColors(uint16_t colors[COLOR_SEQ_MAX]);
    
};

#endif  // COLOR_SNSR_H
