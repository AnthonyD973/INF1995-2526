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
 * @brief   Classe � utiliser pour obtenir la valeur de couleur lue par le
 *          capteur de couleur TAOS TCS230. La classe se charge de l'interpr�tation
 *          de la fr�quence que fournit le capteur et donne une valeur
 *          normalis�e de l'intensit� de la couleur choisie (voir <ColorSnsr::read>).
 */
class ColorSnsr {

public:
    /**
     * @brief   Initialisation du d�tecteur. � appeler au d�but du programme.
     * 
     * @param[in]   tec     Le compteur sur lequel la sortie du capteur est
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
     * @brief   Compteur utilis�.
     */
	static Timer* _TIMER;
    
    /**
     * @brief   Seuil de tol�rance permettant de d�cider qu'une couleur est
     *      pr�dominante par rapport � une autre.
     */
    static const uint16_t COLOR_UNCERT;
    
    /**
     * @brief   Seuil de rouge qui est d�pass� lorsque le capteur lit du blanc.
     */
    static uint16_t _RED_THRESH_FOR_WHITE;
    /**
     * @brief   Seuil de vert qui est d�pass� lorsque le capteur lit du blanc.
     */
    static uint16_t _GREEN_THRESH_FOR_WHITE;
    /**
     * @brief   Seuil de bleu qui est d�pass� lorsque le capteur lit du blanc.
     */
    static uint16_t _BLUE_THRESH_FOR_WHITE;
    
    /**
     * @brief   Initialise les constantes *_THRESH pour d�celer blanc.
     */
    static void _initializeConstants();
    
    /**
     * @brief   Change un tableau de couleurs selon les couleurs lues et selon
     *      un pr�dicat binaire.
     */
    template <class Operator>
    static void _readColors(uint16_t colors[COLOR_SEQ_MAX]);
    
};

#endif  // COLOR_SNSR_H
