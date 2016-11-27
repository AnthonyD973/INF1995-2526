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
#include "ColorSnsr.h"
#include "path.h"
typedef uint8_t Color;

// ---Shape---
#ifndef CIRCLE_G
    #define CIRCLE_G  COLOR_READ_GREEN
    #define OCTOGON_R COLOR_READ_RED
    #define SQUARE_B  COLOR_READ_BLUE
#endif // CIRCLE_G

#define COLOR_SEQ_MAX 3
#define INPUT_SEQ_MAX 4


class ColorSequenceDetector {
public:
    /**
     * @brief   Fait le robot suivre la ligne jusqu'à ce qu'il rencontre la
     *      bonne séquence de couleurs.
     * @param[in] shapeSequence Séquence de couleur cherchée. L'indice 0
     *      correspond à la première couleur de la séquence, c'est-à-dire à la
     *      forme de la dernière pièce.
     */
    static void checkSequence(const Color shapeSequence[3]);

private:
    /**
     * @brief   Vérifie si la couleur a changé en comparant les valeurs des
     *      derniers résultats.
     * @param[in] color Couleur lue actuellement.
     * @return  Si la couleur a changé. La couleur a changé si elle est restée
     *      la même sur plusieurs lectures d'affilée, mais est différente d'une
     *      lecture plus ancienne.
     */
    static bool checkColorChange(Color color);
    
    /**
     * @brief   Séquence de couleurs du papier sur lequel passe le robot.
     */
    static Color colorSequence_[COLOR_SEQ_MAX];
    /**
     * @brief   Nombre de couleurs dans colorSequence_.
     */
    static uint8_t colorSequenceCount_;
    /**
     * @brief   Dernières valeurs lues. Il s'agit d'une sorte de tableau
     *      circulaire : l'indice 0 est juste après l'indice INPUT_SEQ_MAX-1.
     */
    static Color inputSequence_[INPUT_SEQ_MAX];
    /**
     * @brief   Indice de début du tableau.
     */
    static uint8_t inputSequenceBeg_;
};

#endif // COLOR_SEQUENCE_DETECTOR_H
