#ifndef TIMER_H
#define TIMER_H

#include "lib.h"
#include "pinPosition.h"
#include "led.h"
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
    TOGGLE = 0x1,
    CLEAR = 0x2,
    SET = 0x3;

// ===========================
// =          TIMER          =
// ===========================

class Timer {
    
    friend class LED;
    
    friend void intTimerChgAmberLedsColor(Timer* timer);
    
public:
    Timer();
    
    virtual void changePrescale(Prescale01 prescale) {};
  
    virtual void allowOVFI() {};
    virtual void allowOCIA() {};
    virtual void allowOCIB() {};
    
    virtual void denyOVFI() {};
    virtual void denyOCIA() {};
    virtual void denyOCIB() {};
    
    inline virtual bool is8BitClock() {return false;};
    
    
    volatile uint16_t getAmberLeds();
    
 
    volatile uint16_t _amberLeds;   // Positions des LED ambres sur les broches.
    uint8_t _nLedsControlled;       // Nombre de LED contrôlées par ce timer lorsqu'elles sont ambres.
private:
};

// ===========================
// =         TIMER 0         =
// ===========================

class Timer0 : public Timer {
public:
    
    Timer0(Prescale01 prescale);
    
    virtual void changePrescale(Prescale01 prescale);
    
    void modeCTC    (ComNX com0a, ComNX com0b, uint8_t ocr0a, uint8_t ocr0b);
    void modeFastPWM(ComNX com0a, ComNX com0b, uint8_t ocr0a, uint8_t ocr0b);
    
    
    virtual void allowOVFI();
    virtual void allowOCIA();
    virtual void allowOCIB();
    
    virtual void denyOVFI();
    virtual void denyOCIA();
    virtual void denyOCIB();
    
    inline virtual bool is8BitClock() { return true; }
};

// ===========================
// =         TIMER 1         =
// ===========================

class Timer1 : public Timer {
public:
    
    Timer1(Prescale01 prescale);
    
    virtual void changePrescale(Prescale01 prescale);
    
    void modeCTC    (ComNX com0a, ComNX com1b, uint16_t ocr1a, uint16_t ocr1b);
    void modeFastPWM(ComNX com0a, ComNX com1b, uint16_t ocr1a, uint16_t ocr1b);
    
    
    virtual void allowOVFI();
    virtual void allowOCIA();
    virtual void allowOCIB();
    
    virtual void denyOVFI();
    virtual void denyOCIA();
    virtual void denyOCIB();
    
    inline virtual bool is8BitClock() { return false; }
};

#endif // TIMER_H
