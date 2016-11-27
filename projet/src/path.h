/**
 * @file    path.h
 * @brief   Définition de Path qui permet de suivre un chemin prédéterminé.
 * 
 * Contient des fonctions pour contrôler les moteurs et un interpréteur de
 * bytecode pour la lecture des chemins.
 *
 * @authors Belhaddad, Emir Khaled
 * @authors Dandenault, Vincent
 * @authors Dentinger, Anthony
 * @authors Younis, Gergi
 * 
 * @date 2016
 *
 * @copyright Code qui n'est sous aucune license.
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
 * @brief   Classe gérant tout ce qui a trait au positionnement du robot par
 *      rapport à un chemin.
 * 
 * Path peut lire un chemin prédéterminé et effetuer les actions correspondantes
 * et fournit également des méthodes publiques plus flexibles pour contrôler le
 * robot.
 */
class Path {
    
public :
    /**
     * @brief   Initialisation de la classe. À appeler au début du programme.
     * @param[in,out] engL  Moteur de gauche.
     * @param[in,out] engR  Moteur de droite.
     */
    static void init(Engine* engL, Engine* engR);
    /**
     * @brief   Fait avancer le robot en suivant la ligne.
     */
    static void forward();
    /**
     * @brief   Arrête le script de suivi de ligne et arrête les moteurs.
     */
    static void stop();
    /**
     * @brief   Fait tourner le robot, indépendamment des lignes sur le sol.
     * @param[in] dir   Direction de la rotation.
     * @param[in] speed Puissance de la rotation. Entre 0 (min) et 255 (max).
     */
    static void turn(RotDir dir, uint8_t speed);
    /**
     * @brief Lit les instructions en mémoire et effectue les actions
     *      correspondantes. Voir Opcode.
     * @param[in] path  Numéro du chemin en mémoire. Théoriquement, ce
     *      paramètre pourrait avoir n'importe quelle valeur, mais, pour notre
     *      projet, nous n'utilisons que 3 chemins, donc 0 ≤ path ≤ 2.
     */
    static void doPath(uint8_t path);
    
    
    /**
     * @brief   Moteur de gauche.
     * @warning Ne pas utiliser, sauf dans les routines d'interruption.
     */
    static Engine* engL_;
    /**
     * @brief   Moteur de droite.
     * @warning Ne pas utiliser, sauf dans les routines d'interruption.
     */
    static Engine* engR_;
    /**
     * @brief   État actuel du suivi de ligne, par exemple :
     *      'correction à gauche', 'avancement rectiligne'.
     * @warning Ne pas utiliser, sauf dans les routines d'interruption.
     */
    static volatile State etat;
    
private :
    /**
     * @brief   Tableau dont chaque élément est l'adresse de la première
     *          instruction d'un chemin.
     */
    static uint16_t pathAddr_[NB_PATHS];
    /**
     * @brief   Remplit le tableau pathAddr_ avec les adresses de début des
     *      chemins.
     * @param[in] addr  Adresse de début du fichier généré par GAS.
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
