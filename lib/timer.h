/*
 * Classe permettant l'utilisation des minuteries du microcontrôleur.
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

#ifndef TIMER_H
#define TIMER_H

#include "incl.h"

class Timer;    // Résolution des dépendances circulaires (ouais... bof, c'est du patchwork)
class Timer0;   // Résolution des dépendances circulaires
class Timer1;   // Résolution des dépendances circulaires
class Timer2;   // Résolution des dépendances circulaires

extern Timer0 timer0;
extern Timer1 timer1;
extern Timer2 timer2;

#include "lib.h"
#include "led.h"
#include "engine.h"
#include "uart.h"

// ---ComNX---

// ---WGMode---               // Modes du Timer0 : [Voir Documentation p. 103]
#define    WGM02_NORMAL    0x00 // Normal             (avec TOP = 0xFF)
#define    WGM02_PWM_PC1   0x01 // PWM, Phase correct (avec TOP = 0xFF)
#define    WGM02_CTC       0x02 // CTC                (avec TOP = OCR0A)
#define    WGM02_PWM_F1    0x03 // Fast PWM           (avec TOP = 0xFF)
#define    WGM02_PWM_PC2   0x05 // PWM, Phase correct (avec TOP = OCR0A)
#define    WGM02_PWM_F2    0x07 // Fast PWM           (avec TOP = OCR0A)

                           // Modes du Timer1 : [Voir Documentation p. 130]
#define    WGM1_NORMAL    0x00 // Normal                         (avec TOP = 0xFFFF)
#define    WGM1_PWM_PC_8  0x01 // PWM, Phase Correct 8-bit       (avec TOP = 0x00FF)
#define    WGM1_PWM_PC_9  0x02 // PWM, Phase Correct 9-bit       (avec TOP = 0x01FF)
#define    WGM1_PWM_PC_10 0x03 // PWM, Phase Correct 10-bit      (avec TOP = 0x03FF)
#define    WGM1_CTC1      0x04 // CTC                            (avec TOP = OCR1A)
#define    WGM1_PWM_F_8   0x05 // Fast PWM, 8-bit                (avec TOP = 0x00FF)
#define    WGM1_PWM_F_9   0x06 // Fast PWM, 9-bit                (avec TOP = 0x01FF)
#define    WGM1_PWM_F_10  0x07 // Fast PWM, 10-bit               (avec TOP = 0x03FF)
#define    WGM1_PWM_PFC1  0x08 // PWM, Phase & Frequency Correct (avec TOP = ICR1)
#define    WGM1_PWM_PFC2  0x09 // PWM, Phase & Frequency Correct (avec TOP = OCR1A)
#define    WGM1_PWM_PC1   0x0A // PWM, Phase Correct             (avec TOP = ICR1)
#define    WGM1_PWM_PC2   0x0B // PWM, Phase Correct             (avec TOP = OCR1A)
#define    WGM1_CTC2      0x0C // CTC                            (avec TOP = ICR1)
#define    WGM1_PWM_F1    0x0E // Fast PWM                       (avec TOP = ICR1)
#define    WGM1_PWM_F2    0x0F // Fast PWM                       (avec TOP = OCR1A)

// ===========================
// =          TIMER          =
// ===========================

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
    inline virtual bool is8BitClock() { while (true) {} return false; };
    
    /**
     * @brief   Retourne les positions des LED présentement ambres (et donc gérées par les interruptions du compteur).
     * @return  Les positions des LED. Chaque bit correspond à une paire de broche.
     *      Exemple : le bit 0 (LSB) correspond aux broches A0 et A1.
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
};

// ===========================
// =         TIMER 1         =
// ===========================

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
};

// ===========================
// =         TIMER 2         =
// ===========================

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
};

#endif // TIMER_H
