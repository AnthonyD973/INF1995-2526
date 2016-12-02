#include "timer.h"

Timer0 timer0(P01_NO_CLK);
Timer1 timer1(P01_NO_CLK);
Timer2 timer2(P2_NO_CLK);

// ===========================
// =          TIMER          =
// ===========================

// PUBLIC:

volatile uint16_t Timer::getAmberLeds() {
    return _amberLeds;
}

// PROTECTED:

Timer::Timer() :_nAmberLeds(0)
{ }

// ===========================
// =         TIMER 0         =
// ===========================

// PUBLIC:

Timer0::Timer0(Prescale01 prescale)
{
    setPrescale(prescale);
}


void Timer0::setPrescale(Prescale01 prescale) {
    cli();
    
    _MASK(TCCR0B, prescale << CS00, _BV(CS02) | _BV(CS01) | _BV(CS00));
    
    sei();
}

void Timer0::setMode(WGMode mode0) {
    cli();
    
    // On sépare le bit 2 des bit 1 et 0
    uint8_t wgm02  = ((mode0 & 0x04) >> 2) << WGM02;
    uint8_t wgm010 =  (mode0 & 0x03)       << WGM00;
    
    // Ne pas forcer la comparaison.
    uint8_t foc0ab = 0 << FOC0A | 0 << FOC0B;
    
    // Écrire aux position apropriées.
    uint8_t tccr0b_mask = _BV(WGM02) | _BV(FOC0A) | _BV(FOC0B);
    
    // On met les valeurs voulues dans les registres
    _MASK(TCCR0A, wgm010, _BV(WGM01) | _BV(WGM00));
    _MASK(TCCR0B, wgm02 | foc0ab, tccr0b_mask);
    
    sei();
}


void Timer0::setComNA(ComNX com0a) {
    _MASK(TCCR0A, com0a << COM0A0, 0x3 << COM0A0);
}

void Timer0::setComNB(ComNX com0b) {
    _MASK(TCCR0A, com0b << COM0B0, 0x3 << COM0B0);
}


void Timer0::setOcrNA(uint16_t ocr0a) {
    OCR0A = (uint8_t)ocr0a;
}

void Timer0::setOcrNB(uint16_t ocr0b) {
    OCR0B = (uint8_t)ocr0b;
}


void Timer0::setTcntN(uint16_t tcnt0) {
    TCNT0 = tcnt0;
}


uint16_t Timer0::getOcrNA() {
    return OCR0A;
}

uint16_t Timer0::getOcrNb() {
    return OCR0B;
}


uint16_t Timer0::getTcntN() {
    return TCNT0;
}



void Timer0::allowOVFI() {
    _MASK(TIMSK0, _BV(TOIE0), _BV(TOIE0));
}

void Timer0::allowOCIA() {
    _MASK(TIMSK0, _BV(OCIE0A), _BV(OCIE0A));
}

void Timer0::allowOCIB() {
    _MASK(TIMSK0, _BV(OCIE0B), _BV(OCIE0B));
}


void Timer0::denyOVFI() {
    _MASK(TIMSK0, 0 << TOIE0, _BV(TOIE0));
}

void Timer0::denyOCIA() {
    _MASK(TIMSK0, 0 << OCIE0A, _BV(OCIE0A));
}

void Timer0::denyOCIB() {
    _MASK(TIMSK0, 0 << OCIE0B, _BV(OCIE0B));
}

// ===========================
// =         TIMER 1         =
// ===========================

// PUBLIC:

Timer1::Timer1(Prescale01 prescale)
{
    setPrescale(prescale);
}


void Timer1::setPrescale(Prescale01 prescale) {
    cli();
    
    _MASK(TCCR1B, prescale << CS00, 0x7 << CS10);
    
    sei();
}

void Timer1::setMode(WGMode mode1) {
    cli();
    
    // On sépare les bits 2 et 3 des bit 1 et 0
    uint8_t wgm132 = ((mode1 & 0x0C) >> 2) << WGM12;
    uint8_t wgm110 =  (mode1 & 0x03)       << WGM10;
    
    // Ne pas forcer la comparaison.
    uint8_t foc1ab = 0 << FOC1A | 0 << FOC1B;
    
    // On met les valeurs voulues dans les registres
    _MASK(TCCR1A, wgm110, _BV(WGM11) | _BV(WGM10));
    _MASK(TCCR1B, wgm132, _BV(WGM13) | _BV(WGM12));
    
    TCCR1C = foc1ab;
    
    sei();
}


void Timer1::setComNA(ComNX com1a) {
    _MASK(TCCR1A, com1a << COM1A0, 0x3 << COM1A0);
}

void Timer1::setComNB(ComNX com1b) {
    _MASK(TCCR1A, com1b << COM1B0, 0x3 << COM1B0);
}


void Timer1::setOcrNA(uint16_t ocr1a) {
    OCR1A = ocr1a;
}

void Timer1::setOcrNB(uint16_t ocr1b) {
    OCR1B = ocr1b;
}

void Timer1::setTcntN(uint16_t tcnt1) {
    TCNT1 = tcnt1;
}


uint16_t Timer1::getOcrNA() {
    return OCR1A;
}

uint16_t Timer1::getOcrNb() {
    return OCR1B;
}


uint16_t Timer1::getTcntN() {
    return TCNT1;
}



void Timer1::allowOVFI() {
    _MASK(TIMSK1, _BV(TOIE1), _BV(TOIE1));
}

void Timer1::allowOCIA() {
    _MASK(TIMSK1, _BV(OCIE1A), _BV(OCIE1A));
}

void Timer1::allowOCIB() {
    _MASK(TIMSK1, _BV(OCIE1B), _BV(OCIE1B));
}


void Timer1::denyOVFI() {
    _MASK(TIMSK1, 0 << TOIE1, _BV(TOIE1));
}

void Timer1::denyOCIA() {
    _MASK(TIMSK1, 0 << OCIE1A, _BV(OCIE1A));
}

void Timer1::denyOCIB() {
    _MASK(TIMSK1, 0 << OCIE1B, _BV(OCIE1B));
}

// ===========================
// =         TIMER 2         =
// ===========================

// PUBLIC:

Timer2::Timer2(Prescale2 prescale)
{
    setPrescale(prescale);
}



void Timer2::setPrescale(Prescale2 prescale) {
    cli();
    
    _MASK(TCCR2B, (prescale & 0x07) << CS20, _BV(CS22) | _BV(CS21) | _BV(CS20));
    
    sei();
}

void Timer2::setMode(WGMode mode2) {
    cli();
    
    // On sépare le bit 2 des bit 1 et 0
    uint8_t wgm22  = ((mode2 & 0x04) >> 2) << WGM22;
    uint8_t wgm210 =  (mode2 & 0x03)       << WGM20;
    
    // Ne pas forcer la comparaison.
    uint8_t foc2ab = 0 << FOC2A | 0 << FOC2B;
    
    // Écrire aux position apropriées.
    uint8_t tccr2b_mask = _BV(WGM22) | _BV(FOC2A) | _BV(FOC2B);
    
    // On met les valeurs voulues dans les registres
    _MASK(TCCR2A, wgm210, _BV(WGM21) | _BV(WGM20));
    _MASK(TCCR2B, wgm22 | foc2ab, tccr2b_mask);
    
    sei();
}


void Timer2::setComNA(ComNX com2a) {
    _MASK(TCCR2A, com2a << COM2A0, 0x3 << COM2A0);
}

void Timer2::setComNB(ComNX com2b) {
    _MASK(TCCR2A, com2b << COM2B0, 0x3 << COM2B0);
}


void Timer2::setOcrNA(uint16_t ocr2a) {
    OCR2A = (uint8_t)ocr2a;
}

void Timer2::setOcrNB(uint16_t ocr2b) {
    OCR2B = (uint8_t)ocr2b;
}

void Timer2::setTcntN(uint16_t tcnt2) {
    TCNT2 = tcnt2;
}


uint16_t Timer2::getOcrNA() {
    return OCR2A;
}

uint16_t Timer2::getOcrNb() {
    return OCR2B;
}


uint16_t Timer2::getTcntN() {
    return TCNT2;
}



void Timer2::allowOVFI() {
    _MASK(TIMSK2, _BV(TOIE2), _BV(TOIE2));
}

void Timer2::allowOCIA() {
    _MASK(TIMSK2, _BV(OCIE2A), _BV(OCIE2A));
}

void Timer2::allowOCIB() {
    _MASK(TIMSK2, _BV(OCIE2B), _BV(OCIE2B));
}


void Timer2::denyOVFI() {
    _MASK(TIMSK2, 0 << TOIE2, _BV(TOIE2));
}

void Timer2::denyOCIA() {
    _MASK(TIMSK2, 0 << OCIE2A, _BV(OCIE2A));
}

void Timer2::denyOCIB() {
    _MASK(TIMSK2, 0 << OCIE2B, _BV(OCIE2B));
}
