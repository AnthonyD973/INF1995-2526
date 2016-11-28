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
#include <led.h>
#include <buzzer.h>

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
     * @brief   Initialise l'attribut @link #LED_ @endlink. À appeler au début
     *      du programme.
     * @param[in,out] led   LED à allumer lorsqu'une LED doit l'être.
     */
    static void init(LED* led);
    /**
     * @brief   Détecte la forme d'une pièce en supposant que le robot est déjà
     *      placé au milieu. Le robot aura fait un demi-tour sur lui-même à la
     *      fin de l'appel.
     * @return  La forme de la pièce détectée.
     */
    static ShapeColor checkShape();
    
private:
    /**
     * @brief   Modifie la valeur de @link #max_ @endlink si ce paramètre est
     *      plus grand que @link #max_ @endlink.
     */
    static void updateMax_(uint8_t curDist);
    /**
     * @brief   Détermine la forme de la pièce et effectue l'action
     *      correspondante (allumer LED ou jouer un son).
     * @return  La forme de la pièce.
     */
    static ShapeColor findShapeAndAct_();
    
    /**
     * @brief   LED à allumer lorsque la pièce est circulaire ou octogonale.
     */
    static LED* LED_;
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
     * @brief   Seuil de différence entre @link #max_ @endlink et
     *      @link #min_ @endlink pour le carré. Si @link #max_ @endlink -
     *      @link #min_ @endlink est plus grand que ce seuil, la pièce est un
     *      carré.
     */
    static const uint8_t SQUARE_DELTA_;
    /**
     * @brief   Seuil de différence entre @link #max_ @endlink et
     *      @link #min_ @endlink pour l'octogone. Si @link #max_ @endlink -
     *      @link #min_ @endlink est plus grand que ce seuil, la pièce est un
     *      octogone.
     */
    static const uint8_t OCTOGON_DELTA_;
    /**
     * @brief   Nombre de lectures avant que le robot ait fait un quart de tour.
     */
    static const uint8_t N_READS_TILL_QUARTER_TURN_;
};

#endif // SHAPE_DETECTOR_H
