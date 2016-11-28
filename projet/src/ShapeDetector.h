/**
 * @file    ShapeDetector.h
 * 
 * @brief   Définition de ShapeDetector qui utilise DistSnsr afin de déterminer
 *      la forme d'une pièce.
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

#ifndef SHAPE_DETECTOR_H
#define SHAPE_DETECTOR_H

#include <incl.h>

#include "typedefs.h"
#include "DistSnsr.h"

/**
 * @brief   Classe utilisant DistSnsr afin de déterminer la forme d'une pièce.
 * 
 * ShapeDetector décide en fonction de la différence de distance entre le
 * minimum et le maximum mesuré sur environ un quart de tour.
 */
class ShapeDetector {
public:
    /**
     * @brief   Détecte la forme d'une pièce en supposant que le robot est déjà
     *      placé au milieu. Le robot aura fait un demi-tour sur lui-même à la
     *      fin de l'appel.
     * 
     * @return  La forme de la pièce détectée.
     */
    static ShapeColor checkShape();
    
private:
    /**
     * @brief   Effectue 32 lectures en rafale sur le capteur et en fait la
     *      moyenne pour avoir un signal plus constant entre deux lectures.
     * 
     * @return  Une valeur moyenne allant de 0 à 256 représentant la valeur de
     *          la tension émise par le capteur.
     */
    static uint8_t getAverageValue_();
    /**
     * @brief   Modifie la valeur de @link max_ @endlink si ce paramètre est
     *      plus grand que @link max_ @endlink.
     */
    static void updateMax_(uint8_t curDist);
    
    /**
     * @brief   Distance mesurée alors que le robot fait dos à l'entrée de la
     *      pièce.
     */
    static uint8_t min_;
    /**
     * @brief   Distance maximale mesurée sur environ un quart de tour.
     */
    static uint8_t max_;
    /**
     * @brief   Incertitude en-deçà de laquelle on est certain que la distance
     *      est en train de diminuer. Si la distance diminue, on peut arrêter
     *      la prise de mesures.
     */
    static const uint8_t uncert_;
    /**
     * @brief   Seuil de différence entre @link max_ @endlink et
     *      @link min_ @endlink pour le carré. Si @link max_ @endlink -
     *      @link min_ @endlink est plus grand que ce seuil, la pièce est un
     *      carré.
     */
    static const uint8_t SQUARE_DELTA;
    /**
     * @brief   Seuil de différence entre @link max_ @endlink et
     *      @link min_ @endlink pour l'octogone. Si @link max_ @endlink -
     *      @link min_ @endlink est plus grand que ce seuil, la pièce est un
     *      octogone.
     */
    static const uint8_t OCTOGON_DELTA;
};

#endif // SHAPE_DETECTOR_H
