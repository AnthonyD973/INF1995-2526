/**
 * @file    can.h
 * 
 * @brief   Définition de la classe CAN qui permet l'accès au convertisseur
 *      analogique/numerique du microcontrôleur.
 *
 * @authors Khouzam, Matthew
 * @authors Collin, Jérôme
 * 
 * @date 2005-2006
 * 
 * @copyright Code qui n'est sous aucune license.
 */

#ifndef CAN_H
#define CAN_H

#include "incl.h"

/**
 * @brief   Une lecture enclanche une conversion et le résultat
 *          est retourné sur 16 bits.
 */
class CAN {

public:

    /**
     * @brief   Initialisation du convertisseur. Doit être appelé au début du
     *          programme, et uniquement au début.
     */
    static void init();
    /**
     * @brief   Arrête le convertisseur pour sauver sur la consommation.
     */
    static void terminate();

    /**
     * @brief   Retourne la valeur numérique correspondant à la valeur
     *          analogique sur le port A.
     * @param[in]   pos     Position sur le port A. Doit être entre 0 et 7
     *                      inclusivement.
     * @return  La valeur numérique correspondant à la valeur analogique sur le
     *          port A. Seulement les 10 bits de poids faible sont
     *          significatifs.
     */
    static uint16_t read(uint8_t pos);

private:
    /**
     * @brief   Etat convertisseur analogique-numerique, i.e. allumé ou éteint.
     */
    static bool active;

};

#endif // CAN_H
