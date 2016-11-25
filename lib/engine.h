/*
 * Classe permettant l'utilisation des moteurs.
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

#ifndef ENGINE_H
#define ENGINE_H

#include "incl.h"

class Engine;   // Résolution des dépendances circulaires (c'est du patchwork...)

typedef uint8_t EngineMode;
typedef uint8_t TimerChannelUsed;

#include "lib.h"
#include "timer.h"


// ---EngineMode---
#define    ENG_OFF      0x04
#define    ENG_FORWARD  0x00
#define    ENG_BACKWARD 0x01

// ---TimerChannelUsed---                  | ENABLE | DIRECTION |
#define    T0CA 0   // PWM utilisé = OC0A. |   PB3  |    PB2    |
#define    T0CB 1   // PWM utilisé = OC0B. |   PB4  |    PB5    |
#define    T1CA 2   // PWM utilisé = OC1A. |   PD5  |    PD3    |
#define    T1CB 3   // PWM utilisé = OC1B. |   PD4  |    PD2    |
#define    T2CA 4   // PWM utilisé = OC2A. |   PD7  |    PD5    |
#define    T2CB 5   // PWM utilisé = OC2B. |   PD6  |    PD4    |


class Engine {
public:
    /**
     * @brief   Constructeur d'Engine. Permet de savoir où est branché le moteur.
     * @param[in] tcu   Permet de savoir : Quel Timer ? Canal A ou B ? Voir engine.h.
     */
    Engine(TimerChannelUsed tcu);
    /**
     * @brief   Fait avancer ou reculer le moteur en utilisant le Timer pour
     *      gérer la puissance.
     * @param[in] mode  Définit si le moteur doit avancer, reculer ou
     *      s'arrêter.
     * @param[in] ocrNX Valeur à mettre dans le registre de comparaison du
     *      compteur.
     */
    void setPower(EngineMode mode, uint16_t ocrNX);
    /**
     * @brief   Fait avancer ou reculer le moteur sans utiliser le Timer
     *      (puissance 100%).
     * @param[in] mode  Définit si le moteur doit avancer, reculer ou
     *      s'arrêter.
     */
    void setMode(EngineMode mode);
    
    Timer* getTimer();
    
private:
    Timer* _timer;
    bool _isOnChannelA;
    
    uint8_t _FORWARD, _BACKWARD;
    uint8_t _THIS_MASK;
    volatile uint8_t* _PORT;
};
#endif // ENGINE_H
