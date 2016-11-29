/**
 * @file    engine.h
 * 
 * @brief   Définition de la classe Engine qui permet de contrôler les moteurs.
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

#ifndef ENGINE_H
#define ENGINE_H

#include "incl.h"

class Engine;   // Résolution des dépendances circulaires (c'est du patchwork...)

#include "lib.h"
#include "timer.h"

/**
 * @brief   Classe permettant de contrôler les moteurs.
 */
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
    
    /**
     * @brief   Accède au Timer du moteur qui contrôle la puissance du moteur.
     * @return  Un pointeur vers le Timer qui contrôle la puissance du moteur.
     */
    Timer* getTimer();
    
private:
    /**
     * @brief   Timer qui contrôle la puissance du moteur.
     */
    Timer* _timer;
    /**
     * @brief   Définit si le moteur est branché sur le canal A du Timer.
     */
    bool _isOnChannelA;
    
    /**
     * @brief   Valeur à mettre sur le port lorsque le moteur doit avancer.
     */
    uint8_t _FORWARD;
    /**
     * @brief   Valeur à mettre sur le port lorsque le moteur doit reculer.
     */
    uint8_t _BACKWARD;
    /**
     * @brief   Masque du moteur sur le port sur lequel il est branché.
     */
    uint8_t _THIS_MASK;
    /**
     * @brief   Port sur lequel le moteur est branché.
     */
    volatile uint8_t* _PORT;
};
#endif // ENGINE_H
