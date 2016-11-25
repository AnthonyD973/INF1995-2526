/* 
 * Classe permettant l'accès au capteur de distance GP2D12 de SHARP.
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

#ifndef DISTSNSR_H_ // Include Guard
#define DISTSNSR_H_

#include <incl.h>

typedef uint8_t PinAPos;

#include <lib.h>
#include <can.h>

/**
 * @class   DistSnsr
 * 
 * @brief   Classe � utiliser pour obtenir la valeur de distance lue par le
 *          capteur de distance GP2D12. La classe se charge de l'interpr�tation
 *          de la valeur analogique que fournit le capteur et donne une valeur
 *          normalis�e de la distance (voir <DistSnsr::read>).
 */
class DistSnsr {

public:
    /**
     * @brief   Initialisation du d�tecteur. � appeler au d�but du programme.
     *          Met en entr�e la broche <pinANum> du port A o� le signal
     *          analogique du capteur de distance est re�u.
     * 
     * @param[in]   pinANum     La position de la broche o� la sortie du capteur
     *                          est branch�e.
     * 
     *                          La valeur peut prendre une de celles-ci:
     *                              [PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7]
     *                          Elles sont d�finies dans la librairie d'AVR.
     */
    static void     init(PinAPos pinANum);

    /**
     * @brief   Lit la valeur du capteur.
     * 
     * @return  Une valeur allant de 0 � 256 repr�sentant la valeur de la
     *          tension �mise par le capteur.
     */
    static uint8_t  read();
    /**
     * @brief   Effectu 32 lectures sur le capteur en rafale pour ensuite en
     *          faire la moyenne afin de lisser tout pic qui puisse �tre caus�
     *          par du bruit dans le signal re�u et avoir des valeurs
     *          relativement constante et pr�cise.
     * 
     * @return  Une valeur moyenne allant de 0 � 256 repr�sentant la valeur de
     *          la tension �mise par le capteur.
     */
    static uint8_t  readAverage();

private:
    /**
     * @brief   Num�ro de la broche.
     */
    static PinAPos _PIN_A_NUM;

};

#endif  // Include Guard
