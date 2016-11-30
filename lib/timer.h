/**
 * @file    timer.h
 * 
 * @brief   Définition des classes Timer, Timer0, Timer1 et Timer2 qui
 *      permettent l'utilisation des minuteries du microcontrôleur.
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

#ifndef TIMER_H
#define TIMER_H

#include "incl.h"

class Timer;  // Résolution des dépendances circulaires (ouais... bof, c'est du patchwork)
class Timer0; // Résolution des dépendances circulaires
class Timer1; // Résolution des dépendances circulaires
class Timer2; // Résolution des dépendances circulaires

extern Timer0 timer0;
extern Timer1 timer1;
extern Timer2 timer2;

#include "lib.h"
#include "led.h"
#include "engine.h"
#include "uart.h"

// ===========================
// =          TIMER          =
// ===========================

/**
 * @brief   Classe qui permet l'utilisation des minuteries/compteurs
 *      du microcontrôleur. Timer est une classe abstraite utilisée pour
 *      effectuer du polymorphisme, de manière à ce que d'autres classes
 *      puissent fonctionner indémendamment du compteur utilisé.
 */
class Timer {
    
    friend class LED;
    friend class Engine;
    
    friend void switchAmberLedsColor(Timer* timer);
    
public:
    /**
     * @brief   Change la valeur du diviseur d'horloge.
     * @param prescale  Valeur de la divison de l'horloge.
     */
    virtual void setPrescale(Prescale01 prescale) {};
    
    /**
     * @brief   Met le timer au mode Passé en paramètre.
     * @param[in]   mode    Mode auquel on veut mettre le timer.
     *      Le mode doit être une des constantes préfixé par WGM02_ pour les
     *      Timers 0 ou 2 ou par WGM1_ pour le Timer 1.
     */
    virtual void setMode(WGMode mode) { while (true) {} };
    
    /**
     * @brief   Change la réaction du signal de OCNA lors d'une une égalité entre OCRNA et TCNTN.
     * @param[in] comNa Valeur du COM à utiliser pour le canal A.
     */
    virtual void setComNA(ComNX comNa) { while (true) {} };
    /**
     * @brief   Change la réaction du signal de OCNB lors d'une une égalité entre OCRNB et TCNTN.
     * @param[in] comNb Valeur du COM à utiliser pour le canal B.
     */
    virtual void setComNB(ComNX comNb) { while (true) {} };
    
    /**
     * @brief   Change la valeur de OCRNA.
     * @param[in] ocrNa    Nouvelle valeur de OCRNA.
     */
    virtual void setOcrNA(uint16_t ocrNa) { while (true) {} };
    /**
     * @brief   Change la valeur de OCRNB.
     * @param[in] ocrNb    Nouvelle valeur de OCRNB.
     */
    virtual void setOcrNB(uint16_t ocrNb) { while (true) {} };
    
    /**
     * @brief   Change la valeur de TCNTN.
     * @param[in] tcntN    Nouvelle valeur de TCNTN.
     */
    virtual void setTcntN(uint16_t tcntN) { while (true) {} };
    
    /**
     * @brief   Accède à la valeur de OcrNA.
     * @return  La valeur actuelle de OcrNA.
     */
    virtual uint16_t getOcrNA() { while (true) {} };
    /**
     * @brief   Accède à la valeur de OcrNB.
     * @return  La valeur actuelle de OcrNB.
     */
    virtual uint16_t getOcrNb() { while (true) {} };
    
    /**
     * @brief   Accède à la valeur de TcntN.
     * @return  La valeur actuelle de TcntN.
     */
    virtual uint16_t getTcntN() { while (true) {} };
    
  
    /**
     * @brief   Permet l'interruption TOVN (voir doc. p. 103).
     * @note L'interruption TOVN est permise par défaut dans le constructeur.
     */
    virtual void allowOVFI() { while (true) {} };
    /**
     * @brief   Permet l'interruption lors de l'égalité du OCRNA et TCNTN.
     */
    virtual void allowOCIA() { while (true) {} };
    /**
     * @brief   Permet l'interruption lors de l'égalité du OCRNB et TCNTN.
     */
    virtual void allowOCIB() { while (true) {} };
    
    /**
     * @brief   Empêche l'interruption TOVN (voir doc. p. 103).
     * @note L'interruption TOVN est permise par défaut dans le constructeur.
     */
    virtual void denyOVFI() { while (true) {} };
    /**
     * @brief   Empêche l'interruption lors de l'égalité du OCRNA et TCNTN.
     */
    virtual void denyOCIA() { while (true) {} };
    /**
     * @brief   Empêche l'interruption lors de l'égalité du OCRNB et TCNTN.
     */
    virtual void denyOCIB() { while (true) {} };
    
    /**
     * @brief   Détermine si l'instance du Timer est à 8 bits ou à 16 bits.
     * @return  Si l'instance du Timer est à 8 bits.
     */
#ifndef DOXYGEN // Doxygen ne gère pas les __attribute__, alors nous devons les chacher lorsqu'on génère la documentation.
    __attribute__ ((always_inline))
#endif // DOXYGEN
    inline virtual bool is8BitClock() { while (true) {} return false;};
    
    /**
     * @brief   Détermine si l'instance du Timer permet la fonctionnalité
     *      asynchrone.
     * @return  Si l'instance du Timer permet la fonctionnalité asynchrone.
     */
#ifndef DOXYGEN // Doxygen ne gère pas les __attribute__, alors nous devons les chacher lorsqu'on génère la documentation.
    __attribute__ ((always_inline))
#endif // DOXYGEN
    inline virtual bool isAsync() { while (true) {} return false; }
    
    /**
     * @brief   Retourne les positions des LED présentement ambres (et donc
     *      gérées par les interruptions du compteur).
     * @return  Les positions des LED. Chaque bit correspond à une paire de
     *      broche. <b>Exemple :</b> le bit 0 (LSB) correspond aux broches A0
     *      et A1.
     */
    volatile uint16_t getAmberLeds();

protected:
    Timer();
    
private:
    /**
     * @brief   Mode de réaction des signaux OCNA à l'égalité entre OCRNA et
     *      TCNTN.
     */
    ComNX _comNa;
    /**
     * @brief   Mode de réaction des signaux OCNB à l'égalité entre OCRNB et
     *      TCNTN.
     */
    ComNX _comNb;
 
    
    /**
     * @brief   Positions des LED ambres sur les broches.
     */
    volatile uint16_t _amberLeds;
    /**
     * @brief   Nombre de LED actuellement ambres.
     */
    uint8_t _nAmberLeds;
};

// ===========================
// =         TIMER 0         =
// ===========================

/**
 * @brief   Classe qui permet l'utilisation de la minuterie/compteur 0
 *      du microcontrôleur. Timer0 est un compteur 8 bits.
 */
class Timer0 : public Timer {
public:
    /**
     * @brief   Construit un Timer0 avec une certaine division d'horloge.
     * @param prescale  Valeur de la divison de l'horloge.
     */
    Timer0(Prescale01 prescale);
    
    virtual void setPrescale(Prescale01 prescale);
    
    virtual void setMode(WGMode mode0);
    
    virtual void setComNA(ComNX com0a);
    virtual void setComNB(ComNX com0b);
    
    virtual void setOcrNA(uint16_t ocr0a);
    virtual void setOcrNB(uint16_t ocr0b);
    
    virtual void setTcntN(uint16_t tcnt0);
    
    virtual uint16_t getOcrNA();
    virtual uint16_t getOcrNb();
    
    virtual uint16_t getTcntN();
    
    
    virtual void allowOVFI();
    virtual void allowOCIA();
    virtual void allowOCIB();
    
    virtual void denyOVFI();
    virtual void denyOCIA();
    virtual void denyOCIB();
    
#ifndef DOXYGEN // Doxygen ne gère pas les __atribute__, alors nous devons les chacher lorsqu'on génère la documentation.
    __attribute__ ((always_inline))
#endif // DOXYGEN
    inline virtual bool is8BitClock() { return true; }
#ifndef DOXYGEN // Doxygen ne gère pas les __attribute__, alors nous devons les chacher lorsqu'on génère la documentation.
    __attribute__ ((always_inline))
#endif // DOXYGEN
    inline virtual bool isAsync() { return false; }
};

// ===========================
// =         TIMER 1         =
// ===========================

/**
 * @brief   Classe qui permet l'utilisation de la minuterie/compteur 1
 *      du microcontrôleur. Timer1 est un compteur 16 bits.
 */
class Timer1 : public Timer {
public:
    /**
     * @brief   Construit un Timer1 avec une certaine division d'horloge.
     * @param prescale  Valeur de la divison de l'horloge.
     */
    Timer1(Prescale01 prescale);
    
    virtual void setPrescale(Prescale01 prescale);
    
    virtual void setMode(WGMode mode1);
    
    virtual void setComNA(ComNX com1a);
    virtual void setComNB(ComNX com1b);
    
    virtual void setOcrNA(uint16_t ocr1a);
    virtual void setOcrNB(uint16_t ocr1b);
    
    virtual void setTcntN(uint16_t tcnt1);
    
    virtual uint16_t getOcrNA();
    virtual uint16_t getOcrNb();
    
    virtual uint16_t getTcntN();
    
    
    virtual void allowOVFI();
    virtual void allowOCIA();
    virtual void allowOCIB();
    
    virtual void denyOVFI();
    virtual void denyOCIA();
    virtual void denyOCIB();
    
#ifndef DOXYGEN // Doxygen ne gère pas les __atribute__, alors nous devons les chacher lorsqu'on génère la documentation.
    __attribute__ ((always_inline))
#endif // DOXYGEN
    inline virtual bool is8BitClock() { return false; }
#ifndef DOXYGEN // Doxygen ne gère pas les __attribute__, alors nous devons les chacher lorsqu'on génère la documentation.
    __attribute__ ((always_inline))
#endif // DOXYGEN
    inline virtual bool isAsync() { return false; }
};

// ===========================
// =         TIMER 2         =
// ===========================

/**
 * @brief   Classe qui permet l'utilisation de la minuterie/compteur 2
 *      du microcontrôleur. Timer2 est un compteur 8 bits avec une
 *      fonctionnalité asynchrone que nous n'utiliserons pas dans ce projet.
 */
class Timer2 : public Timer {
public:
    /**
     * @brief   Construit un Timer2 avec une certaine division d'horloge.
     * @param prescale  Valeur de la divison de l'horloge.
     */
    Timer2(Prescale2 prescale);
    
    virtual void setPrescale(Prescale2 prescale);
    
    virtual void setMode(WGMode mode2);
    
    virtual void setComNA(ComNX com2a);
    virtual void setComNB(ComNX com2b);
    
    virtual void setOcrNA(uint16_t ocr2a);
    virtual void setOcrNB(uint16_t ocr2b);
    
    virtual void setTcntN(uint16_t tcnt2);
    
    virtual uint16_t getOcrNA();
    virtual uint16_t getOcrNb();
    
    virtual uint16_t getTcntN();
    
    
    virtual void allowOVFI();
    virtual void allowOCIA();
    virtual void allowOCIB();
    
    virtual void denyOVFI();
    virtual void denyOCIA();
    virtual void denyOCIB();
    
#ifndef DOXYGEN // Doxygen ne gère pas les __atribute__, alors nous devons les chacher lorsqu'on génère la documentation.
    __attribute__ ((always_inline))
#endif // DOXYGEN
    inline virtual bool is8BitClock() { return true; }
#ifndef DOXYGEN // Doxygen ne gère pas les __attribute__, alors nous devons les chacher lorsqu'on génère la documentation.
    __attribute__ ((always_inline))
#endif // DOXYGEN
    inline virtual bool isAsync() { return true; }
};

#endif // TIMER_H
