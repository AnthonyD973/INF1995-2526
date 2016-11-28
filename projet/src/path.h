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

typedef uint8_t PathState;

// Constantes pour les vitesses
const uint8_t
    V_MAX = 0x8F, /**< @brief Puissance maximale à transmettre aux moteurs. */
    V_MOY = 0x6F, /**< @brief Puissance moyenne à transmettre aux moteurs. */
    V_MIN = 0x00; /**< @brief Puissance minimale à transmettre aux moteurs. */

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
     * @brief Lit les instructions en mémoire et effectue les actions
     *      correspondantes. Voir Opcode.
     * @param[in] path  Numéro du chemin en mémoire. Théoriquement, ce
     *      paramètre pourrait avoir n'importe quelle valeur, mais, pour notre
     *      projet, nous n'utilisons que 3 chemins, donc 0 ≤ path ≤ 2.
     */
    static void doPath(uint8_t path);
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
     * @brief   Ajuste la puissance des moteurs dépendamment du
     *      @link #currPathState_ @endlink actuel.
     * 
     * La routine d'interruption qui appelle cette fonction est utilisée pour
     * faire une sorte de 'multi-threading'.
     * @warning Bien que cette méthode soit publique, seules les routines
     *      d'interruption devraient faire y faire référence.
     */
    static void updateDirection_();
    
    
    /**
     * @brief   Moteur de gauche.
     * @warning Bien que cet attribut soit publique, seules les routines
     *      d'interruption devraient faire y faire référence.
     */
    static Engine* engL_;
    /**
     * @brief   Moteur de droite.
     * @warning Bien que cet attribut soit publique, seules les routines
     *      d'interruption devraient faire y faire référence.
     */
    static Engine* engR_;
    /**
     * @brief   État actuel du suivi de ligne, par exemple :
     *      'correction à gauche', 'avancement rectiligne'.
     * @warning Bien que cet attribut soit publique, seules les routines
     *      d'interruption devraient faire y faire référence.
     */
    static volatile PathState currPathState_;
    
private:
    /**
     * @brief   Vérifie s'il le robot est rendu à un branchement.
     * @param[in] input Valeur lue du détecteur de ligne.
     * @return  Si le robot est à un embranchement.
     */
    static bool isBranch_(uint8_t input);
    /**
    * @brief   Vérifie si l'état reçu en paramètre est un état valide,
    *      c'est-à-dire, s'il s'agit d'un des états que l'on peut s'attendre à
    *      observer durant le parcours.
    * @param[in] input Valeur lue du détecteur de ligne.
    * @return  Si l'état présent est un état valide.
    */
    static bool isValidState_(uint8_t input);
    
    /**
     * @brief   Remplit le tableau pathAddr_ avec les adresses de début des
     *      chemins.
     * @param[in] fileBegAddr  Adresse de début du fichier généré par GAS.
     */
    static void populatePathAddrs_(uint16_t fileBegAddr);
    
    /**
     * @brief Valeur que DistSnsr::read doit retourner lorsque le robot est au
     *      millieu de la pièce.
     */
    static const uint8_t MIDDLE_DIST_;
    
    /**
     * @brief   Tableau dont chaque élément est l'adresse de la première
     *          instruction d'un chemin.
     */
    static uint16_t pathAddrs_[NB_PATHS];

    // ====================
    // =  INSTRUCTIONS DE = 
    // =  L'INTERPRÉTEUR  =
    // ====================
    
    /**
     * @brief   <b>INI</b>t
     * 
     * Attendre que les 5 capteurs de ligne soient actifs, puis se déplacer en
     * avant pendant une demi-seconde.
     */
    static void ini_();
    /**
     * @brief   <b>T</b>ur<b>N L</b>eft
     * 
     * Au prochain embranchement, tourner à gauche.
     */
    static void tnl_();
    /**
     * @brief   <b>T</b>ur<b>N R</b>ight
     * 
     * Au prochain embranchement, tourner à droite.
     */
    static void tnr_();
    /**
     * @brief   <b>M</b>i<b>D</b>d<b>L</b>e
     * 
     * Se mettre au milieu de la pièce.
     */
    static void mdl_();
    /**
     * @brief   <b>EN</b>d <b>P</b>ath
     * 
     * Le chemin est terminé ; les prochaines instructions sont pour le chemin suivant.
     */
    static void enp_();
};


#endif /* path_h */
