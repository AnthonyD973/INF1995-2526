#ifndef TIMER_H
#define TIMER_H

#include "lib.h"
#include "led.h"
#include "engine.h"
#include "defaultISR.h"

extern Timer0 timer0;
extern Timer1 timer1;
extern Timer2 timer2;


typedef uint8_t Prescale01;
//const Prescale01
#define    P01_NO_CLK  0x0
#define    P01_CLK1    0x1
#define    P01_CLK8    0x2
#define    P01_CLK64   0x3
#define    P01_CLK256  0x4
#define    P01_CLK1024 0x5
#define    P01_EXT_CLK_FALLING_EDGE 0x6
#define    P01_EXT_CLK_RISING_EDGE 0x7

typedef uint8_t Prescale2;
//const Prescale2
#define    P2_NO_CLK  0x0
#define    P2_CLK1    0x1
#define    P2_CLK8    0x2
#define    P2_CLK32   0x3 // Nouvelle valeur comparé à P01
#define    P2_CLK64   0x4
#define    P2_CLK128  0x5 // Nouvelle valeur comparé à P01
#define    P2_CLK256  0x6
#define    P2_CLK1024 0x7

typedef uint8_t ComNX;
//const ComNX
#define    DISCONNECTED 0x0
#define    TOGGLE       0x1   // ATTENTION: Dans certains modes (ex: Fast-PWM et PC-PWM du Timer0 avec WGM02 = 0), TOGGLE est équivalent à DISCONNECTED.
                              // Également, pour COMNB, TOGGLE peut ne pas être supporté par le microcontrôleur.
#define    CLEAR        0x2
#define    SET          0x3

typedef uint8_t WGMode; // Waveform Generation Mode
//const WGMode               // Modes du Timer0 : [Voir Documentation p. 103]
#define    WGM0_NORMAL    0x00 // Normal             (avec TOP = 0xFF)
#define    WGM0_PWM_PC1   0x01 // PWM, Phase correct (avec TOP = 0xFF)
#define    WGM0_CTC       0x02 // CTC                (avec TOP = OCR0A)
#define    WGM0_PWM_F1    0x03 // Fast PWM           (avec TOP = 0xFF)
#define    WGM0_PWM_PC2   0x05 // PWM, Phase correct (avec TOP = OCR0A)
#define    WGM0_PWM_F2    0x07 // Fast PWM           (avec TOP = OCR0A)

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

                           // Modes du Timer1 : [Voir Documentation p. 153]
#define    WGM2_NORMAL    0x00 // Normal             (avec TOP = 0xFF)
#define    WGM2_PWM_PC1   0x01 // PWM, Phase Correct (avec TOP = 0xFF)
#define    WGM2_CTC       0x02 // CTC                (avec TOP = OCR2A)
#define    WGM2_PWM_F1    0x03 // Fast PWM           (avec TOP = 0xFF)
#define    WGM2_PWM_PC2   0x05 // PWM, Phase Correct (avec TOP = OCR2A)
#define    WGM2_PWM_F2    0x07 // Fast PWM           (avec TOP = OCR2A)

// ===========================
// =          TIMER          =
// ===========================

class Timer {
    
    friend class LED;
    friend class Engine;
    
    friend void switchAmberLedsColor(Timer* timer);
    
public:
#warning ">>> SVP, rendre la classe Timer abstraite <<<"
    Timer();
    
    virtual void setPrescale(Prescale01 prescale) {};
    
    virtual void setMode(WGMode mode) { UART::transmitCStr("UART::transmitCStr"); };
    
    virtual void setComNA(ComNX comNa) { UART::transmitCStr("Timer::setComNA"); };
    virtual void setComNB(ComNX comNb) { UART::transmitCStr("Timer::setComNB"); };
    
    virtual void setOcrNA(uint16_t ocrNa) { UART::transmitCStr("Timer::setOcrNA"); };
    virtual void setOcrNB(uint16_t ocrNb) { UART::transmitCStr("Timer::setOcrNB"); };
  
    virtual void allowOVFI() { UART::transmitCStr("Timer::allowOVFI"); };
    virtual void allowOCIA() { UART::transmitCStr("Timer::allowOCIA"); };
    virtual void allowOCIB() { UART::transmitCStr("Timer::allowOCIB"); };
    
    virtual void denyOVFI() { UART::transmitCStr("Timer::denyOVFI"); };
    virtual void denyOCIA() { UART::transmitCStr("Timer::denyOCIA"); };
    virtual void denyOCIB() { UART::transmitCStr("Timer::denyOCIB"); };
    
    __attribute__ ((always_inline))
    inline virtual bool is8BitClock() { UART::transmitCStr("Timer::is8BitClock"); return false;};
    
    volatile uint16_t getAmberLeds();

private:
    ComNX _comNa, _comNb;           // Mode de réaction des signaux OCNX lors de l'égalité entre OCRNX et TCNTN.
 
    volatile uint16_t _amberLeds;   // Positions des LED ambres sur les broches.
    uint8_t _nAmberLeds;            // Nombre de LED présentement ambres.
};

// ===========================
// =         TIMER 0         =
// ===========================

class Timer0 : public Timer {
public:
    
    Timer0(Prescale01 prescale);
    
    virtual void setPrescale(Prescale01 prescale);
    
    virtual void setMode(WGMode mode0);
    
    virtual void setComNA(ComNX com0a);
    virtual void setComNB(ComNX com0b);
    
    virtual void setOcrNA(uint16_t ocrNa);
    virtual void setOcrNB(uint16_t ocrNb);
    
    
    virtual void allowOVFI();
    virtual void allowOCIA();
    virtual void allowOCIB();
    
    virtual void denyOVFI();
    virtual void denyOCIA();
    virtual void denyOCIB();
    
    __attribute__ ((always_inline))
    inline virtual bool is8BitClock() { return true; }
};

// ===========================
// =         TIMER 1         =
// ===========================

class Timer1 : public Timer {
public:
    
    Timer1(Prescale01 prescale);
    
    virtual void setPrescale(Prescale01 prescale);
    
    virtual void setMode(WGMode mode1);
    
    virtual void setComNA(ComNX com1a);
    virtual void setComNB(ComNX com1b);
    
    virtual void setOcrNA(uint16_t ocr1a);
    virtual void setOcrNB(uint16_t ocr1b);
    
    
    virtual void allowOVFI();
    virtual void allowOCIA();
    virtual void allowOCIB();
    
    virtual void denyOVFI();
    virtual void denyOCIA();
    virtual void denyOCIB();
    
    __attribute__ ((always_inline))
    inline virtual bool is8BitClock() { return false; }
};

// ===========================
// =         TIMER 2         =
// ===========================

class Timer2 : public Timer {
public:
    
    Timer2(Prescale2 prescale);
    
    virtual void setPrescale(Prescale2 prescale);
    
    virtual void setMode(WGMode mode2);
    
    virtual void setComNA(ComNX com2a);
    virtual void setComNB(ComNX com2b);
    
    virtual void setOcrNA(uint16_t ocr2a);
    virtual void setOcrNB(uint16_t ocr2b);
    
    
    virtual void allowOVFI();
    virtual void allowOCIA();
    virtual void allowOCIB();
    
    virtual void denyOVFI();
    virtual void denyOCIA();
    virtual void denyOCIB();
    
    __attribute__ ((always_inline))
    inline virtual bool is8BitClock() { return true; }
};

#endif // TIMER_H
