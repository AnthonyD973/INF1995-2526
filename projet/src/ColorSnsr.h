/**
 * @file    ColorSnsr.h
 * 
 * @brief   Définition de ColorSnsr qui permet d'utiliser le capteur de couleur
 *      TAOS TCS230 de Parallax.
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

#ifndef COLOR_SNSR_H
#define COLOR_SNSR_H

#include <incl.h>
#include <lib.h>
#include <timer.h>

#include "typedefs.h"

#ifndef COLOR_SEQ_MAX
    #define COLOR_SEQ_MAX   3
#endif // COLOR_SEQ_MAX

#define RED_INDEX   0
#define GREEN_INDEX 1
#define BLUE_INDEX  2


/**
 * @class   ColorSnsr
 * 
 * @brief   Classe à utiliser pour obtenir la valeur de couleur lue par le
 *          capteur de couleur TAOS TCS230. La classe se charge de l'interprétation
 *          de la fréquence que fournit le capteur et donne une valeur
 *          normalisée de l'intensité de la couleur choisie (voir ColorSnsr::read).
 */
class ColorSnsr {

public:
    /**
     * @brief   Initialisation du détecteur. À appeler au ébut du programme.
     * 
     * @param[in] tec   Le compteur sur lequel la sortie du capteur est
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
     * @brief   Initialise _THRESHES_FOR_WHITE pour déceler le blanc.
     */
    static void _initializeConstants();
    
    /**
     * @brief   Lit les intensités relatives des trois filtres et change un
     *      tableau selon un prédicat binaire.
     * @tparam Operator Classe du prédicat à appliquer sur les éléments du
     *      tableau.
     * @param[in] colorsIntensity   Tableau à modifier.
     */
    template <class Operator>
    static void _readColors(uint16_t colorsIntensity[COLOR_SEQ_MAX]);
    /**
     * @brief   Décide quelle couleur est lue dépendamment des intensités
     *      relatives des couleurs.
     * @param[in] colorsIntensity   Tableau des intensités relatives des
     *      couleurs.
     * @return  La couleur lue.
     */
    static ShapeColor _decideWhichColor(uint16_t colorsIntensity[COLOR_SEQ_MAX]);
    
    
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
     * @brief   Timer utilisé pour compter le nombre de fronts montants du
     *      capteur sur une certaine période.
     */
    static Timer* _TIMER;
    
    /**
     * @brief   Seuil de tolérance permettant de décider qu'une couleur est
     *      prédominante par rapport à une autre.
     */
    static const uint16_t _COLOR_UNCERT;
    
    /**
     * @brief   Seuils qui sont dépassés lorsque le capteur lit du blanc.
     */
    static uint16_t _THRESHES_FOR_WHITE[COLOR_SEQ_MAX];
};

#endif  // COLOR_SNSR_H
