#ifndef TIMER_H
#define TIMER_H

#include "lib.h"
#include "pinPosition.h"
#include "led.h"
#include "engine.h"
#include "defaultISR.h"


typedef uint8_t Prescale01;
const Prescale01
    P01_NO_CLK = 0x0,
    P01_CLK1 = 0x1,
    P01_CLK8 = 0x2,
    P01_CLK64 = 0x3,
    P01_CLK256 = 0x4,
    P01_CLK1024 = 0x5,
    P01_EXT_CLK_FALLING_EDGE = 0x6,
    P01_EXT_CLK_RISING_EDGE = 0x7;

typedef uint8_t ComNX;
const ComNX
    DISCONNECTED = 0x0,
    TOGGLE = 0x1,   // ATTENTION: Dans certains modes (ex: Fast-PWM et PC-PWM du Timer0 avec WGM02 = 0), TOGGLE est équivalent à DISCONNECTED.
                    // Également, pour COMNB, TOGGLE peut ne pas être supporté par le microcontrôleur.
    CLEAR = 0x2,
    SET = 0x3;

// ===========================
// =          TIMER          =
// ===========================

class Timer {
    
    friend class LED;
    friend class Engine;
    
    friend void intTimerChgAmberLedsColor(Timer* timer);
    
public:
    Timer();
    
    virtual void setPrescale(Prescale01 prescale) {};
    
    virtual void modeCTC    (uint16_t ocr0a, uint16_t ocr0b) { UART::transmitCStr("Timer::modeCTC"); };
    virtual void modeFastPWM(uint16_t ocr0a, uint16_t ocr0b) { UART::transmitCStr("Timer::modeFastPWM"); };
    
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
    
    inline virtual bool is8BitClock() { UART::transmitCStr("Timer::is8BitClock"); return false;};
    
    volatile uint16_t getAmberLeds();

protected:
    ComNX _getComNA(); // ATTENTION: Ne PAS utiliser cette méthode. Elle est gardée au cas où on décide le la réimplémenter plus tard.
    ComNX _getComNB(); // ATTENTION: Ne PAS utiliser cette méthode. Elle est gardée au cas où on décide le la réimplémenter plus tard.

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
    
    void setPrescale(Prescale01 prescale);
    
    void modeCTC    (uint16_t ocr0a, uint16_t ocr0b);
    void modeFastPWM(uint16_t ocr0a, uint16_t ocr0b);
    
    void setComNA(ComNX com0a);
    void setComNB(ComNX com0b);
    
    void setOcrNA(uint16_t ocrNa);
    void setOcrNB(uint16_t ocrNb);
    
    
    void allowOVFI();
    void allowOCIA();
    void allowOCIB();
    
    void denyOVFI();
    void denyOCIA();
    void denyOCIB();
    
    inline bool is8BitClock() { return true; }
};

// ===========================
// =         TIMER 1         =
// ===========================

class Timer1 : public Timer {
public:
    
    Timer1(Prescale01 prescale);
    
    void setPrescale(Prescale01 prescale);
    
    void modeCTC    (uint16_t ocr1a, uint16_t ocr1b);
    void modeFastPWM(uint16_t ocr1a, uint16_t ocr1b);
    
    void setComNA(ComNX com1a);
    void setComNB(ComNX com1b);
    
    void setOcrNA(uint16_t ocr1a);
    void setOcrNB(uint16_t ocr1b);
    
    
    void allowOVFI();
    void allowOCIA();
    void allowOCIB();
    
    void denyOVFI();
    void denyOCIA();
    void denyOCIB();
    
    inline bool is8BitClock() { return false; }
};

#endif // TIMER_H
