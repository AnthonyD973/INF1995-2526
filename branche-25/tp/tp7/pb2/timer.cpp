#include "timer.h"

// ===========================
// =          TIMER          =
// ===========================

// PUBLIC:

Timer::Timer() :_nLedsControlled(0)
{ }

/**
 * @brief Retourne les positions des LED présentement ambres (et donc gérées par les interruptions du compteur).
 * @return  Les positions des LED. Chaque bit correspond à une paire de broche.
 *      Exemple : le bit 0 (LSB) correspond aux broches A0 et A1.
 */
volatile uint16_t Timer::getAmberLeds() {
    return _amberLeds;
}


// ===========================
// =         TIMER 0         =
// ===========================

// PUBLIC:

/**
 * @brief   Construit un Timer0 avec une certaine division d'horloge.
 * @param prescale  Valeur de la divison de l'horloge.
 */
Timer0::Timer0(Prescale01 prescale)
{
    changePrescale(prescale);
    allowOVFI();
    modeFastPWM(DISCONNECTED, DISCONNECTED, 0x00, 0x00);
}


/**
 * @brief   Change la valeur du diviseur d'horloge.
 * @param prescale  Valeur de la divison de l'horloge.
 */
void Timer0::changePrescale(Prescale01 prescale) {
    cli();
    
    _MASK(TCCR0B, prescale << CS00, 0x7 << CS00);
    
    sei();
}

/**
 * @brief   Met le timer en mode Clear Timer Counter (CTC).
 *      ATTENTION : les broches PB3 et PB4 seront gérées par le compteur.
 *      Pour éviter cela, mettre com0a et/ou com0b en mode DISCONNECTED.
 * @param[in] com0a Mode du signal PWM, sortie OCRA.
 * @param[in] com0b Mode du signal PWM, sortie OCRB.
 * @param[in] ocr0a Valeur à mettre dans le registre corresondant.
 * @param[in] ocr0b Valeur à mettre dans le registre corresondant.
 */
void Timer0::modeCTC(ComNX com0a, ComNX com0b, uint8_t ocr0a, uint8_t ocr0b) {
    cli();
   
    // Se mettre en mode CTC (WGM02:0 = 2).
    uint8_t wgm010 = 0x02 << WGM00;
    
    // Lors de la comparaison, les signaux s'inversent.
    uint8_t com0ab10 = com0a << COM0A0 | com0b << COM0B0;
    
    TCCR0A = wgm010 | com0ab10; // On écrit dans tout le registre TCCR0A.
    
    
    
    // Se mettre en mode CTC (WGM02:0 = 2).
     uint8_t wgm02 = 0 << WGM02;
    
    // Ne pas forcer la comparaison.
    uint8_t foc0ab = 0 << FOC0A | 0 << FOC0B;
    
    // Écrire aux position apropriées.
    uint8_t tccr0b_mask = _BV(WGM02) | _BV(FOC0A) | _BV(FOC0B);
    
    _MASK(TCCR0B, wgm02 | foc0ab, tccr0b_mask);
    
    // Changer les valeurs de occr0a et occr0b.
    OCR0A = ocr0a;
    OCR0B = ocr0b;
    
    sei();
}

/**
 * @brief   Met le timer en mode Fast-Pulse Width Modulation (Fast-PWM).
 *      ATTENTION : les broches PB3 et PB4 seront gérées par le compteur.
 *      Pour éviter cela, mettre com0a et/ou com0b en mode DISCONNECTED.
 * @param[in] com0a Mode du signal PWM, sortie OCRA.
 * @param[in] com0b Mode du signal PWM, sortie OCRB.
 * @param[in] ocr0a Valeur à mettre dans le registre corresondant.
 * @param[in] ocr0b Valeur à mettre dans le registre corresondant.
 */
void Timer0::modeFastPWM(ComNX com0a, ComNX com0b, uint8_t ocr0a, uint8_t ocr0b) {
    cli();
   
    // Se mettre en mode Fast-PWM.
    uint8_t wgm010 = 0x3 << WGM00;
    
    // Lors de la comparaison, PWM passe de 0 à 1.
    uint8_t com0ab10 = com0a << COM0A0 | com0b << COM0B0;
    
    TCCR0A = wgm010 | com0ab10; // On écrit dans tout le registre TCCR0A.
    
    
    
    // TOP = OCR0A
     uint8_t wgm02 = _BV(WGM02);
    
    // Assurer que FOC0A et FOC0B soient à 0 (voir doc p. 104).
    uint8_t foc0ab = 0 << FOC0A | 0 << FOC0B;
    
    // Écrire aux position apropriées.
    uint8_t tccr0b_mask = _BV(WGM02) | _BV(FOC0A) | _BV(FOC0B);
    
    _MASK(TCCR0B, wgm02 | foc0ab, tccr0b_mask);
    
    // Changer les valeurs de occr0a et occr0b.
    OCR0A = ocr0a;
    OCR0B = ocr0b;
    
    sei();
}

/**
 * @brief Permet l'interruption TOV0 (voir doc. p. 103).
 * NOTE: L'interruption TOV0 est permise par défaut dans le constructeur.
 */
void Timer0::allowOVFI() {
    _MASK(TIMSK0, _BV(TOIE0), _BV(TOIE0));
}

/**
 * @brief Permet l'interruption lors de l'égalité du OCR0A et TCNT0.
 */
void Timer0::allowOCIA() {
    _MASK(TIMSK0, _BV(OCIE0A), _BV(OCIE0A));
}

/**
 * @brief Permet l'interruption lors de l'égalité du OCR0B et TCNT0.
 */
void Timer0::allowOCIB() {
    _MASK(TIMSK0, _BV(OCIE0B), _BV(OCIE0B));
}


/**
 * @brief Empêche l'interruption TOV0 (voir doc. p. 103).
 * NOTE: L'interruption TOV0 est permise par défaut dans le constructeur.
 */
void Timer0::denyOVFI() {
    _MASK(TIMSK0, 0 << TOIE0, _BV(TOIE0));
}

/**
 * @brief Empêche l'interruption lors de l'égalité du OCR0A et TCNT0.
 */
void Timer0::denyOCIA() {
    _MASK(TIMSK0, 0 << OCIE0A, _BV(OCIE0A));
}

/**
 * @brief Empêche l'interruption lors de l'égalité du OCR0B et TCNT0.
 */
void Timer0::denyOCIB() {
    _MASK(TIMSK0, 0 << OCIE0B, _BV(OCIE0B));
}


// ===========================
// =         TIMER 1         =
// ===========================

// PUBLIC:

/**
 * @brief   Construit un Timer1 avec une certaine division d'horloge.
 * @param prescale  Valeur de la divison de l'horloge.
 */
Timer1::Timer1(Prescale01 prescale)
{
    changePrescale(prescale);
    allowOVFI();
    modeFastPWM(DISCONNECTED, DISCONNECTED, 0x0000, 0x0000);
}


/**
 * @brief   Change la valeur du diviseur d'horloge.
 * @param prescale  Valeur de la divison de l'horloge.
 */
void Timer1::changePrescale(Prescale01 prescale) {
    cli();
    
    _MASK(TCCR1B, prescale << CS00, 0x7 << CS10);
    
    sei();
}

/**
 * @brief   Met le timer en mode Clear Timer Counter (CTC).
 *      ATTENTION : les broches PD4 et PD5 seront gérées par le compteur.
 *      Pour éviter cela, mettre com1a et/ou com1b en mode DISCONNECTED.
 * @param[in] com1a Mode du signal PWM, sortie OCRA.
 * @param[in] com1b Mode du signal PWM, sortie OCRB.
 * @param[in] ocr1a Valeur à mettre dans le registre corresondant.
 * @param[in] ocr1b Valeur à mettre dans le registre corresondant.
 */
void Timer1::modeCTC(ComNX com1a, ComNX com1b, uint16_t ocr1a, uint16_t ocr1b) {
    cli();
    
    // Se mettre en mode CTC avec TOP = OCR1A (WGM13:0 = 4).
    uint8_t wgm110 = 0x00 << WGM10;
    
    // Lors de la comparaison, les signaux s'inversent.
    uint8_t com1ab10 = com1a << COM1A0 | com1b << COM1B0;
    
    TCCR1A = wgm110 | com1ab10; // On écrit dans tout le registre TCCR1A.
    
    
    // Se mettre en mode CTC avec TOP = OCR1A (WGM13:0 = 4).
    uint8_t wgm132 = 0x01 << WGM12;
    
    _MASK(TCCR1B, wgm132, _BV(WGM12) | _BV(WGM13));
     
    
    // Ne pas forcer la comparaison.
    uint8_t foc1ab = 0 << FOC1A | 0 << FOC1B;
   
    TCCR1C = foc1ab; // On écrit dans tout le registre TCCR1C.
    
    // Changer les valeurs de occr0a et occr0b.
    OCR1A = ocr1a;
    OCR1B = ocr1b;
    
    sei();
}

/**
 * @brief   Met le timer en mode Fast-Pulse Width Modulation (Fast-PWM).
 *      ATTENTION : les broches PD4 et PD5 seront gérées par le compteur.
 *      Pour éviter cela, mettre com1a et/ou com1b en mode DISCONNECTED.
 * @param[in] com1a Mode du signal PWM, sortie OCRA.
 * @param[in] com1b Mode du signal PWM, sortie OCRB.
 * @param[in] ocr1a Valeur à mettre dans le registre corresondant.
 * @param[in] ocr1b Valeur à mettre dans le registre corresondant.
 */
void Timer1::modeFastPWM(ComNX com1a, ComNX com1b, uint16_t ocr1a, uint16_t ocr1b) {
    cli();
    
    // Se mettre en mode Fast-PWM avec TOP = OCR1A (WGM13:0 = 15).
    uint8_t wgm110 = 0x03 << WGM10;
    
    // Lors de la comparaison, PWM passe de 0 à 1.
    uint8_t com1ab10 = com1a << COM1A0 | com1b << COM1B0;
    
    TCCR1A = wgm110 | com1ab10; // On écrit dans tout le registre TCCR1A.
    
    
    // Se mettre en mode Fast-PWM avec TOP = OCR1A (WGM13:0 = 15).
    uint8_t wgm132 = 0x03 << WGM12;
      
    _MASK(TCCR1B, wgm132, _BV(WGM12) | _BV(WGM13));
     
    
    // Assurer que FOC0A et FOC0B soient à 0 (voir doc. p. 131).
    uint8_t foc1ab = 0 << FOC1A | 0 << FOC1B;
     
    TCCR1C = foc1ab; // On écrit dans tout le registre TCCR1C.
    
    // Changer les valeurs de occr0a et occr0b.
    OCR1A = ocr1a;
    OCR1B = ocr1b;
    
    sei();
}


/**
 * @brief Permet l'interruption TOV1 (voir doc. p. 130).
 * NOTE: L'interruption TOV1 est permise par défaut dans le constructeur.
 */
void Timer1::allowOVFI() {
    _MASK(TIMSK1, _BV(TOIE1), _BV(TOIE1));
}

/**
 * @brief Permet l'interruption lors de l'égalité du OCR1A et TCNT1.
 */
void Timer1::allowOCIA() {
    _MASK(TIMSK1, _BV(OCIE1A), _BV(OCIE1A));
}

/**
 * @brief Permet l'interruption lors de l'égalité du OCR1B et TCNT1.
 */
void Timer1::allowOCIB() {
    _MASK(TIMSK1, _BV(OCIE1B), _BV(OCIE1B));
}


/**
 * @brief Empêche l'interruption TOV1 (voir doc. p. 130).
 * NOTE: L'interruption TOV1 est permise par défaut dans le constructeur.
 */
void Timer1::denyOVFI() {
    _MASK(TIMSK1, 0 << TOIE1, _BV(TOIE1));
}

/**
 * @brief Empêche l'interruption lors de l'égalité du OCR1A et TCNT1.
 */
void Timer1::denyOCIA() {
    _MASK(TIMSK1, 0 << OCIE1A, _BV(OCIE1A));
}

/**
 * @brief Empêche l'interruption lors de l'égalité du OCR1B et TCNT1.
 */
void Timer1::denyOCIB() {
    _MASK(TIMSK1, 0 << OCIE1B, _BV(OCIE1B));
}
