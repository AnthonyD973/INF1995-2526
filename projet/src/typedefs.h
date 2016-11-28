/**
 * @file    typedefs.h
 * 
 * @brief   Définition des typedefs et de leurs valeurs possibles.
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

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

/**
 * @brief Type de valeurs qui expriment à la fois quel Timer utiliser pour
 *      compter, et quel mode utiliser pour cela.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 * <li>@link #T0_FALLING_EDGE @endlink</li>
 * <li>@link #T0_RISING_EDGE  @endlink</li>
 * <li>@link #T1_FALLING_EDGE @endlink</li>
 * <li>@link #T1_RISING_EDGE  @endlink</li>
 * </ul>
 */
typedef uint8_t TimerExternalClock;
#define T0_FALLING_EDGE 0x06 /**< @brief Utiliser l'horloge externe de Timer0,
                                         en comptant les fronts desendants. */
#define T0_RISING_EDGE  0x07 /**< @brief Utiliser l'horloge externe de Timer0,
                                         en comptant les fronts montants. */
#define T1_FALLING_EDGE 0x16 /**< @brief Utiliser l'horloge externe de Timer1,
                                         en comptant les fronts desendants. */
#define T1_RISING_EDGE  0x17 /**< @brief Utiliser l'horloge externe de Timer1,
                                         en comptant les fronts montants. */

                                         
/**
 * @brief   Type de valeurs qui expriment une forme ou une couleur,
 *      dépendamment de leur utilisation.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 * <li>@link #OCTOGON_RED    @endlink</li>
 * <li>@link #CIRCLE_GREEN   @endlink</li>
 * <li>@link #SQUARE_BLUE    @endlink</li>
 * <li>@link #NO_SHAPE_WHITE @endlink</li>
 * </ul>
 */
typedef uint8_t ShapeColor;
#define OCTOGON_RED    0x0 /**< @brief Correspond à la forme <i>octogone</i> et
                                       à la couleur/au filtre <i>rouge</i>. */
#define CIRCLE_GREEN   0x3 /**< @brief Correspond à la forme <i>cercle</i> et à
                                       la couleur/au filtre <i>verte</i>. */
#define SQUARE_BLUE    0x2 /**< @brief Correspond à la forme <i>carré</i> et à
                                       la couleur/au filtre <i>bleue</i>. */
#define NO_SHAPE_WHITE 0x1 /**< @brief Ne correspond à aucune forme mais
                                       correspond à la couleur/au filtre
                                       <i>blanc</i>. */


/**
 * @brief   Type de valeurs qui expriment une direction de rotation.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 * <li>@link #ROT_LEFT  @endlink</li>
 * <li>@link #ROT_RIGHT @endlink</li>
 * </ul>
 */
typedef bool RotDir;
#define ROT_LEFT    true  /**< @brief Rotation à gauche. */
#define ROT_RIGHT   false /**< @brief Rotation à droite. */



/**
 * @brief   Type de valeurs qui expriment un opcode d'un fichier généré par GAS.
 * 
 * <b>Valeurs possibles:</b>
 * <ul>
 * <li>@link #NOP_OP @endlink</li>
 * <li>@link #INI_OP @endlink</li>
 * <li>@link #TNL_OP @endlink</li>
 * <li>@link #TNR_OP @endlink</li>
 * <li>@link #MDL_OP @endlink</li>
 * <li>@link #ENP_OP @endlink</li>
 * </ul>
 */
typedef uint8_t Opcode;
#define NOP_OP 0x00 /**< @brief <b>N</b>o <b>OP</b>eration: Ne rien faire. */
#define INI_OP 0x10 /**< @brief <b>INI</b>t: Attendre que les 5 capteurs de
                                ligne soient actifs, puis se déplacer en avant
                                pendant une demi-seconde. */
#define TNL_OP 0x20 /**< @brief <b>T</b>ur<b>N L</b>eft: Au prochain
                                embranchement, tourner à gauche. */
#define TNR_OP 0x21 /**< @brief <b>T</b>ur<b>N R</b>ight: Au prochain
                                embranchement, tourner à droite. */
#define MDL_OP 0x30 /**< @brief <b>M</b>i<b>D</b>d<b>L</b>e: Se mettre au
                                milieu de la pièce. */
#define ENP_OP 0xF0 /**< @brief <b>EN</b>d <b>P</b>ath: Le chemin est terminé ;
                                les prochaines instructions sont pour le chemin
                                suivant. */

#endif // TYPEDEFS_H