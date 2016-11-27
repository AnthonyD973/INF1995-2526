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

#define RED_INDEX   0
#define GREEN_INDEX 1
#define BLUE_INDEX  2


/**
 * @class   ColorSnsr
 * 
 * @brief   Classe � utiliser pour obtenir la valeur de couleur lue par le
 *          capteur de couleur TAOS TCS230. La classe se charge de l'interpr�tation
 *          de la fr�quence que fournit le capteur et donne une valeur
 *          normalis�e de l'intensit� de la couleur choisie (voir ColorSnsr::read).
 */
class ColorSnsr {

public:
    /**
     * @brief   Initialisation du d�tecteur. � appeler au d�but du programme.
     * 
     * @param[in] tec   Le compteur sur lequel la sortie du capteur est
     *      branch�e.
     */
    static void init(TimerExternalClock tec);

    /**
     * @brief   D�termine la couleur dominante vue par le capteur.
     * 
     * @return  La couleur dominante.
     */
    static ShapeColor read();

private:
    /**
     * @brief   Initialise _THRESHES_FOR_WHITE pour d�celer le blanc.
     */
    static void _initializeConstants();
    
    /**
     * @brief   Lit les intensit�s relatives des trois filtres et change un
     *      tableau selon un pr�dicat binaire.
     * @tparam Operator Classe du pr�dicat � appliquer sur les �l�ments du
     *      tableau.
     * @param[in] colorsIntensity   Tableau � modifier.
     */
    template <class Operator>
    static void _readColors(uint16_t colorsIntensity[COLOR_SEQ_MAX]);
    /**
     * @brief   D�cide quelle couleur est lue d�pendamment des intensit�s
     *      relatives des couleurs.
     * @param[in] colorsIntensity   Tableau des intensit�s relatives des
     *      couleurs.
     * @return  La couleur lue.
     */
    static ShapeColor _decideWhichColor(uint16_t colorsIntensity[COLOR_SEQ_MAX]);
    
    
    /**
     * @brief   Masque du bit de LED du capteur.
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
     * @brief   Timer utilis� pour compter le nombre de fronts montants du
     *      capteur sur une certaine p�riode.
     */
    static Timer* _TIMER;
    
    /**
     * @brief   Seuil de tol�rance permettant de d�cider qu'une couleur est
     *      pr�dominante par rapport � une autre.
     */
    static const uint16_t _COLOR_UNCERT;
    
    /**
     * @brief   Seuils qui sont d�pass�s lorsque le capteur lit du blanc.
     */
    static uint16_t _THRESHES_FOR_WHITE[COLOR_SEQ_MAX];
};

#endif  // COLOR_SNSR_H
