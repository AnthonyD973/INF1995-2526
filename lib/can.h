/*
 * Classe permettant l'acces au convertisseur analogique/numerique
 * du microcontroleur ATMega16 de Atmel.
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Matthew Khouzam et Jerome Collin
 * 2005-2006
 *
 * Modifié par Emir Khaled Belhaddad
 * 2016
 *
 * Code qui n'est sous aucune license.
 *
 */

#ifndef CAN_H
#define CAN_H

#include "incl.h"

/**
 * @class   CAN
 * @brief   Le constructeur initialise le convertisseur.
 *          Une lecture enclanche une conversion et le resultat
 *          est retourne sur 16 bits.
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
     * @brief   Retourne la valeur numerique correspondant a la valeur
     *          analogique sur le port A.
     * @param[in]   pos     Position sur le port A. Doit etre entre 0 et 7
     *                      inclusivement.
     * @return  La valeur numerique correspondant a la valeur analogique sur le
     *          port A. Seulement les 10 bits de poids faible sont
     *          significatifs.
     */
    static uint16_t read(uint8_t pos);

private:
    // Donnees membres
    
    /**
     * @brief   Etat convertisseur analogique-numerique, i.e. allume ou eteint.
     *          true:   Le convertisseur est allume et pret a lire des donnees.
     *          false:  Le convertisseur est eteint et ne peut pas lire de
     *                  valeurs analogique.
     */
    static bool active;

};

#endif /* CAN_H */
