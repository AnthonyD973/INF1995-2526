/* 
 * Classe permettant de suivre un chemin prédéterminé. Contient des fonctions
 * pour contrôler les moteurs et un interpréteur de bitcode pour la lecture des
 * chemins.
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

#ifndef PATH_H
#define PATH_H

#define   NB_PATHS 3

#include <lib.h>
#include <timer.h>
#include <ram.h>
#include <engine.h>

#include "typedefs.h"
#include "LineSnsr.h"
#include "DistSnsr.h"

typedef uint8_t State;

 // Constantes pour les vitesses
const uint8_t
    V_MAX = 0x8F,
    V_MOY = 0x6F,
    V_MIN = 0x00;

/**
 * @class   Path
 * 
 * @brief   Classe gérant tout ce qui à attrait au positionnement du robot par
 *          rapport à un chemin.
 */
class Path {
    
public :
    /**
     * 
     */
    static void init(Engine* engL, Engine* engR);
    /**
     * @brief   Fait avancer le robot en suivant une ligne.
     */
    static void forward();
    /**
     * @brief   Arrête le script de suivi de ligne.
     */
    static void stop();
    /**
     * 
     */
    static void turn(RotDir dir, uint8_t speed);
    /**
     * 
     */
    static void doPath(uint8_t path);
    
    //Section qui doit être utilisée uniquement avec les ISR
    static Engine* engL_;
    static Engine* engR_;
    static volatile State etat;
    
private :
    /**
     * @brief   Tableau dont chaque element est l'addresse de la première
     *          instruction d'un chemin.
     */
    static uint16_t pathAddr_[NB_PATHS]; // 3 chemins en mémoire
    /**
     * 
     */
    static void readPath_(uint16_t addr);
    
    // +=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=+
    // | instructions de l'interpréteur |
    // +=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=+
    
    static void ini(void);
    static void tnr(void);
    static void tnl(void);
    static void mdl(void);
    static void enp(void);
};


#endif /* path_h */
