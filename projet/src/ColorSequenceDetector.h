/**
 * Classe permettant de détecter la séquence de couleurs sur laquelle s'arrêter.
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

#ifndef COLOR_SEQUENCE_DETECTOR_H
#define COLOR_SEQUENCE_DETECTOR_H

#include <incl.h>
#include <buzzer.h>
#include <led.h>

#include "typedefs.h"
#include "ColorSnsr.h"
#include "path.h"

#ifndef COLOR_SEQ_MAX
    #define COLOR_SEQ_MAX   3
#endif // COLOR_SEQ_MAX

#define LAST_COLORS_MAX 4


class ColorSequenceDetector {
public:
    /**
     * @brief   Initialise l'attribut @link #LED_ @endlink. À appeler au début
     *      du programme.
     * @param[in,out] led   LED à allumer lorsqu'une LED doit l'être.
     */
    static void init(LED* led);
    /**
     * @brief   Fait le robot suivre la ligne jusqu'à ce qu'il rencontre la
     *      bonne séquence de couleurs.
     * @param[in] shapeSequence Séquence de couleur cherchée. L'indice 0
     *      correspond à la première couleur de la séquence, c'est-à-dire à la
     *      forme de la dernière pièce.
     */
    static void checkSequence(const ShapeColor shapeSequence[COLOR_SEQ_MAX]);

private:
    /**
     * @brief   Utilise ColorSnsr pour détecter la couleur présente et
     *      effectue l'action correspondante (allumer LED ou jouer un son).
     * @return  La couleur actuelle.
     */
    static ShapeColor findColorAndAct_();
    /**
     * @brief   Vérifie si la couleur a changé en comparant les valeurs des
     *      derniers résultats.
     * @param[in] color Couleur lue actuellement.
     * @return  Si la couleur a changé. La couleur a changé si elle est restée
     *      la même sur plusieurs lectures d'affilée, mais est différente d'une
     *      lecture plus ancienne.
     */
    static bool hasColorChanged_(ShapeColor color);
    /**
     * @brief   Vérifie si la séquence de couleur du papier au-dessus duquel est
     *      le robot correspond à la séquence recherchée.
     * @param[in] shapeSequence Séquence de couleur cherchée. L'indice 0
     *      correspond à la première couleur de la séquence, c'est-à-dire à la
     *      forme de la dernière pièce.
     * @return Si  la séquence de couleur du papier au-dessus duquel est
     *      le robot correspond à la séquence recherchée.
     */
    static bool isCorrectSequence_(const ShapeColor shapeSequence[COLOR_SEQ_MAX]);
    /**
     * @brief   Joue une musique pour fêter la fin de l'épreuve \(^_^)/
     */
    static void playEndingTheme_();
    
    /**
     * @brief   LED à allumer lorsque la couleur est verte ou rouge.
     */
    static LED* LED_;
    /**
     * @brief   Séquence de couleurs du papier au-dessus duquel passe le robot.
     */
    static ShapeColor colorSequence_[COLOR_SEQ_MAX];
    /**
     * @brief   Nombre de couleurs dans colorSequence_.
     */
    static uint8_t colorSequenceCount_;
    /**
     * @brief   Dernières valeurs lues. Il s'agit d'une sorte de tableau
     *      circulaire : l'indice 0 est juste après l'indice LAST_COLORS_MAX-1.
     */
    static ShapeColor lastColors_[LAST_COLORS_MAX];
    /**
     * @brief   Indice de début du tableau.
     */
    static uint8_t lastColorsBeg_;
};

#endif // COLOR_SEQUENCE_DETECTOR_H
