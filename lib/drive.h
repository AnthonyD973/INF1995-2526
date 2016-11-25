/* 
 * Classe gérant les deux moteurs, pour que le robot aille droit. Et tourne
 * à 90°. <b>Utilisé uniquement dans le TP9.</b>
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

#ifndef DRIVE_H
#define DRIVE_H

#include "incl.h"

typedef uint8_t DriveDir;

#include "lib.h"
#include "engine.h"

// ---DriveDir---
#define    DIR_OFF 0x00
#define    DIR_RIGHT 0x01
#define    DIR_LEFT 0x02

class Drive {
public:
    /**
     * @brief   Initialise les objets Engine.
     * @param[in] tcuLeft   Sert à définir sur quelles broches le moteur gauche est
     *      branché. Voir engine.h.
     * @param[in] tcuRight  Sert à définir sur quelles broches le moteur droit est
     *      branché. Voir engine.h.
     * @param[in] constLeft     Constante pour le balancement du moteur gauche du
     *      robot.
     * @param[in] constRight    Constante pour le balancement du moteur droit du
     *      robot.
     */
    static void init(TimerChannelUsed tcuLeft, TimerChannelUsed tcuRight,
                     uint8_t constLeft, uint8_t constRight);
    /**
     * @brief   Met les moteurs sur un mode. Tient compte du fait que les deux
     *      moteurs ne tournent pas à la même vitesse.
     * @param[in] mode  Mode des moteurs à mettre. Voir engine.h.
     * @param[in] power Puissance à transmette aux moteurs. Entre 0 et 255.
     */
    static void setMovement(EngineMode mode, uint8_t power);
    /**
     * @brief   Fait pivoter le robot sans déplacer son centre de rotation.
     * @param[in] dir   Direction de la rotation.
     * @param[in] power Puissance de la rotation.
     */
    static void setRotation(DriveDir dir, uint8_t power);
    
private:
    static Engine _engL, _engR;
    static uint8_t CONST_R, CONST_L;
};

#endif // DRIVE_H
