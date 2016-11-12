#include "timer.h"

Timer0 timer0;
Timer1 timer1;
Timer2 timer2;

// ===========================
// =          TIMER          =
// ===========================

// PUBLIC:

/**
 * @brief Constructeur de Timer.
 */
Timer::Timer() :_nAmberLeds(0)
{
 UART::transmitCStr("Timer::Timer\n");
}


/**
 * @brief Retourne les positions des LED présentement ambres (et donc gérées par les interruptions du compteur).
 * @return  Les positions des LED. Chaque bit correspond à une paire de broche.
 *      Exemple : le bit 0 (LSB) correspond aux broches A0 et A1.
 */
volatile uint16_t Timer::getAmberLeds() {
    return _amberLeds;
}

// PROTECTED:

/**
 * @brief   Retourne la valeur courante du Com pour le canal A.
 * @return _comNa.
 */
ComNX Timer::_getComNA() {
    return _comNa;
}

/**
 * @brief   Retourne la valeur courante du Com pour le canal B.
 * @return _comNb.
 */
ComNX Timer::_getComNB(){
    return _comNb;
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
    setPrescale(prescale);
}


/**
 * @brief   Change la valeur du diviseur d'horloge.
 * @param prescale  Valeur de la divison de l'horloge.
 */
void Timer0::setPrescale(Prescale01 prescale) {
    cli();
    
    _MASK(TCCR0B, prescale << CS00, _BV(CS02) | _BV(CS01) | _BV(CS00));
    
    sei();
}

/**
 * @brief   Met le timer au mode Passé en paramètre.
 * @param[in]   mode0   Mode auquel on veut mettre le timer.
 *                      Le mode doit être une des constantes préfixé par WGM0_.
 */
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

/**
 * @brief   Met le timer en mode Clear Timer Counter (CTC).
 * @param[in] ocr0a Valeur à mettre dans le registre corresondant.
 * @param[in] ocr0b Valeur à mettre dans le registre corresondant.
 */
void Timer0::modeCTC(uint16_t ocr0a, uint16_t ocr0b) {
    cli();
   
    // Se mettre en mode CTC (WGM02:0 = 2).
    uint8_t wgm010 = 0x02 << WGM00;
    
    _MASK(TCCR0A, wgm010, _BV(WGM01) | _BV(WGM00));
    
    
    // Se mettre en mode CTC (WGM02:0 = 2).
     uint8_t wgm02 = 0 << WGM02;
    
    // Ne pas forcer la comparaison.
    uint8_t foc0ab = 0 << FOC0A | 0 << FOC0B;
    
    // Écrire aux position apropriées.
    uint8_t tccr0b_mask = _BV(WGM02) | _BV(FOC0A) | _BV(FOC0B);
    
    _MASK(TCCR0B, wgm02 | foc0ab, tccr0b_mask);
    
    // Changer les valeurs de ocr0a et ocr0b.
    setOcrNA(ocr0a);
    setOcrNB(ocr0b);
    
    sei();
}

/**
 * @brief   Met le timer en mode Fast-Pulse Width Modulation (Fast-PWM).
 * @param[in] ocr0a Valeur à mettre dans le registre corresondant.
 * @param[in] ocr0b Valeur à mettre dans le registre corresondant.
 */
void Timer0::modeFastPWM(uint16_t ocr0a, uint16_t ocr0b) {
    cli();
   
    // Se mettre en mode Fast-PWM (WGM01:0 = 3).
    uint8_t wgm010 = 0x3 << WGM00;
    
    _MASK(TCCR0A, wgm010, _BV(WGM01) | _BV(WGM00));
    
    
    // TOP = 0xFF
     uint8_t wgm02 = 0 << WGM02;
    
    // Assurer que FOC0A et FOC0B soient à 0 (voir doc p. 104).
    uint8_t foc0ab = 0 << FOC0A | 0 << FOC0B;
    
    // Écrire aux position apropriées.
    uint8_t tccr0b_mask = _BV(WGM02) | _BV(FOC0A) | _BV(FOC0B);
    
    _MASK(TCCR0B, wgm02 | foc0ab, tccr0b_mask);
    
    // Changer les valeurs de ocr0a et ocr0b.
    setOcrNA(ocr0a);
    setOcrNB(ocr0b);
    
    sei();
}


/**
 * @brief   Change la réaction du signal de OC0A lors d'une une égalité entre OCR0A et TCNT0.
 * @param[in] com0a Valeur du COM à utiliser pour le canal A.
 */
void Timer0::setComNA(ComNX com0a) {
    _MASK(TCCR0A, com0a << COM0A0, 0x3 << COM0A0);
}

/**
 * @brief   Change la réaction du signal de OC0B lors d'une une égalité entre OCR0B et TCNT0.
 * @param[in] com0b Valeur du COM à utiliser pour le canal B.
 */
void Timer0::setComNB(ComNX com0b) {
    _MASK(TCCR0A, com0b << COM0B0, 0x3 << COM0B0);
}


/**
 * @brief   Change la valeur de OCR0A.
 * @param[in] ocr0a    Nouvelle valeur de OCR0A.
 */
void Timer0::setOcrNA(uint16_t ocr0a) {
    OCR0A = (uint8_t)ocr0a;
}

/**
 * @brief   Change la valeur de OCR0B.
 * @param[in] ocr0b    Nouvelle valeur de OCR0B.
 */
void Timer0::setOcrNB(uint16_t ocr0b) {
    OCR0B = (uint8_t)ocr0b;
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
    setPrescale(prescale);
}


/**
 * @brief   Change la valeur du diviseur d'horloge.
 * @param prescale  Valeur de la divison de l'horloge.
 */
void Timer1::setPrescale(Prescale01 prescale) {
    cli();
    
    _MASK(TCCR1B, prescale << CS00, 0x7 << CS10);
    
    sei();
}

/**
 * @brief   Met le timer au mode passé en paramètre.
 * @param[in]   mode1   Mode auquel on veut mettre le timer.
 *                      Le mode doit être une des constantes préfixé par WGM1_.
 */
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

/**
 * @brief   Met le timer en mode Clear Timer Counter (CTC).
 *      ATTENTION : les broches PD4 et PD5 seront gérées par le compteur.
 *      Pour éviter cela, mettre com1a et/ou com1b en mode DISCONNECTED.
 * @param[in] ocr1a Valeur à mettre dans le registre corresondant.
 * @param[in] ocr1b Valeur à mettre dans le registre corresondant.
 */
void Timer1::modeCTC(uint16_t ocr1a, uint16_t ocr1b) {
    cli();
    
    // Se mettre en mode CTC avec TOP = OCR1A (WGM13:0 = 4).
    uint8_t wgm110 = 0x00 << WGM10;
    
    _MASK(TCCR1A, wgm110, _BV(WGM11) |_BV(WGM10));
    
    // Se mettre en mode CTC avec TOP = OCR1A (WGM13:0 = 4).
    uint8_t wgm132 = 0x01 << WGM12;
    
    _MASK(TCCR1B, wgm132, _BV(WGM12) | _BV(WGM13));
     
    
    // Ne pas forcer la comparaison.
    uint8_t foc1ab = 0 << FOC1A | 0 << FOC1B;
   
    TCCR1C = foc1ab; // On écrit dans tout le registre TCCR1C.
    
    // Changer les valeurs de ocr0a et ocr0b.
    setOcrNA(ocr1a);
    setOcrNB(ocr1b);
    
    sei();
}

/**
 * @brief   Met le timer en mode Fast-Pulse Width Modulation (Fast-PWM).
 *      ATTENTION : les broches PD4 et PD5 seront gérées par le compteur.
 *      Pour éviter cela, mettre com1a et/ou com1b en mode DISCONNECTED.
 * @param[in] ocr1a Valeur à mettre dans le registre corresondant.
 * @param[in] ocr1b Valeur à mettre dans le registre corresondant.
 */
void Timer1::modeFastPWM(uint16_t ocr1a, uint16_t ocr1b) {
    cli();
    
    // Se mettre en mode Fast-PWM avec TOP = OCR1A (WGM13:0 = 15).
    uint8_t wgm110 = 0x03 << WGM10;
    
    _MASK(TCCR1A, wgm110, _BV(WGM11) |_BV(WGM10));
    
    
    // Se mettre en mode Fast-PWM avec TOP = OCR1A (WGM13:0 = 15).
    uint8_t wgm132 = 0x03 << WGM12;
      
    _MASK(TCCR1B, wgm132, _BV(WGM12) | _BV(WGM13));
     
    
    // Assurer que FOC0A et FOC0B soient à 0 (voir doc. p. 131).
    uint8_t foc1ab = 0 << FOC1A | 0 << FOC1B;
     
    TCCR1C = foc1ab; // On écrit dans tout le registre TCCR1C.
    
    // Changer les valeurs de ocr0a et ocr0b.
    setOcrNA(ocr1a);
    setOcrNB(ocr1b);
    
    sei();
}


/**
 * @brief   Change la réaction du signal de OC1A lors d'une une égalité entre OCR1A et TCNT1.
 * @param[in] com1a Valeur du COM à utiliser pour le canal A.
 */
void Timer1::setComNA(ComNX com1a) {
    _MASK(TCCR1A, com1a << COM1A0, 0x3 << COM1A0);
}

/**
 * @brief   Change la réaction du signal de OC1B lors d'une une égalité entre OCR1B et TCNT1.
 * @param[in] com1b Valeur du COM à utiliser pour le canal B.
 */
void Timer1::setComNB(ComNX com1b) {
    _MASK(TCCR1A, com1b << COM1B0, 0x3 << COM1B0);
}


/**
 * @brief   Change la valeur de OCR1A.
 * @param[in] ocr1a    Nouvelle valeur de OCR1A.
 */
void Timer1::setOcrNA(uint16_t ocr1a) {
    OCR1A = ocr1a;
}

/**
 * @brief   Change la valeur de OCR0B.
 * @param[in] ocr0b    Nouvelle valeur de OCR0B.
 */
void Timer1::setOcrNB(uint16_t ocr1b) {
    OCR1B = ocr1b;
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

// ===========================
// =         TIMER 2         =
// ===========================

// PUBLIC:

/**
 * @brief   Construit un Timer2 avec une certaine division d'horloge.
 * @param prescale  Valeur de la divison de l'horloge.
 */
Timer2::Timer2(Prescale2 prescale)
{
    setPrescale(prescale);
}


/**
 * @brief   Change la valeur du diviseur d'horloge.
 * @param prescale  Valeur de la divison de l'horloge.
 */
void Timer2::setPrescale(Prescale2 prescale) {
    cli();
    
    _MASK(TCCR2B, (prescale & 0x07) << CS20, _BV(CS22) | _BV(CS21) | _BV(CS20));
    
    sei();
}

/**
 * @brief   Met le timer au mode Passé en paramètre.
 * @param[in]   mode2   Mode auquel on veut mettre le timer.
 *                      Le mode doit être une des constantes préfixé par WGM2_.
 */
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

/**
 * @brief   Met le timer en mode Clear Timer Counter (CTC).
 * @param[in] ocr2a Valeur à mettre dans le registre corresondant.
 * @param[in] ocr2b Valeur à mettre dans le registre corresondant.
 */
void Timer2::modeCTC(uint16_t ocr2a, uint16_t ocr2b) {
    cli();
   
    // Se mettre en mode CTC (WGM22:0 = 2).
    uint8_t wgm210 = 0x02 << WGM20;
    
    _MASK(TCCR2A, wgm210, _BV(WGM21) | _BV(WGM20));
    
    
    // Se mettre en mode CTC (WGM22:0 = 2).
     uint8_t wgm22 = 0 << WGM22;
    
    // Ne pas forcer la comparaison.
    uint8_t foc2ab = 0 << FOC2A | 0 << FOC2B;
    
    // Écrire aux position apropriées.
    uint8_t tccr2b_mask = _BV(WGM22) | _BV(FOC2A) | _BV(FOC2B);
    
    _MASK(TCCR2B, wgm22 | foc2ab, tccr2b_mask);
    
    // Changer les valeurs de ocr2a et ocr2b.
    setOcrNA(ocr2a);
    setOcrNB(ocr2b);
    
    sei();
}

/**
 * @brief   Met le timer en mode Fast-Pulse Width Modulation (Fast-PWM).
 * @param[in] ocr2a Valeur à mettre dans le registre corresondant.
 * @param[in] ocr2b Valeur à mettre dans le registre corresondant.
 */
void Timer2::modeFastPWM(uint16_t ocr2a, uint16_t ocr2b) {
    cli();
   
    // Se mettre en mode Fast-PWM (WGM21:0 = 3).
    uint8_t wgm210 = 0x03 << WGM20;
    
    _MASK(TCCR2A, wgm210, _BV(WGM21) | _BV(WGM20));
    
    
    // TOP = 0xFF
     uint8_t wgm22 = 0 << WGM22;
    
    // Assurer que FOC2A et FOC2B soient à 0 (voir doc p. 104).
    uint8_t foc2ab = 0 << FOC2A | 0 << FOC2B;
    
    // Écrire aux position apropriées.
    uint8_t tccr2b_mask = _BV(WGM22) | _BV(FOC2A) | _BV(FOC2B);
    
    _MASK(TCCR2B, wgm22 | foc2ab, tccr2b_mask);
    
    // Changer les valeurs de ocr2a et ocr2b.
    setOcrNA(ocr2a);
    setOcrNB(ocr2b);
    
    sei();
}


/**
 * @brief   Change la réaction du signal de OC2A lors d'une une égalité entre OCR2A et TCNT2.
 * @param[in] com2a Valeur du COM à utiliser pour le canal A.
 */
void Timer2::setComNA(ComNX com2a) {
    _MASK(TCCR2A, com2a << COM2A0, 0x3 << COM2A0);
}

/**
 * @brief   Change la réaction du signal de OC2B lors d'une une égalité entre OCR2B et TCNT2.
 * @param[in] com2b Valeur du COM à utiliser pour le canal B.
 */
void Timer2::setComNB(ComNX com2b) {
    _MASK(TCCR2A, com2b << COM2B0, 0x3 << COM2B0);
}


/**
 * @brief   Change la valeur de OCR2A.
 * @param[in] ocr2a    Nouvelle valeur de OCR2A.
 */
void Timer2::setOcrNA(uint16_t ocr2a) {
    OCR2A = (uint8_t)ocr2a;
}

/**
 * @brief   Change la valeur de OCR2B.
 * @param[in] ocr2b    Nouvelle valeur de OCR2B.
 */
void Timer2::setOcrNB(uint16_t ocr2b) {
    OCR2B = (uint8_t)ocr2b;
}



/**
 * @brief Permet l'interruption TOV2 (voir doc. p. 103).
 */
void Timer2::allowOVFI() {
    _MASK(TIMSK2, _BV(TOIE2), _BV(TOIE2));
}

/**
 * @brief Permet l'interruption lors de l'égalité du OCR2A et TCNT2.
 */
void Timer2::allowOCIA() {
    _MASK(TIMSK2, _BV(OCIE2A), _BV(OCIE2A));
}

/**
 * @brief Permet l'interruption lors de l'égalité du OCR2B et TCNT2.
 */
void Timer2::allowOCIB() {
    _MASK(TIMSK2, _BV(OCIE2B), _BV(OCIE2B));
}


/**
 * @brief Empêche l'interruption TOV2 (voir doc. p. 103).
 */
void Timer2::denyOVFI() {
    _MASK(TIMSK2, 0 << TOIE2, _BV(TOIE2));
}

/**
 * @brief Empêche l'interruption lors de l'égalité du OCR2A et TCNT2.
 */
void Timer2::denyOCIA() {
    _MASK(TIMSK2, 0 << OCIE2A, _BV(OCIE2A));
}

/**
 * @brief Empêche l'interruption lors de l'égalité du OCR2B et TCNT2.
 */
void Timer2::denyOCIB() {
    _MASK(TIMSK2, 0 << OCIE2B, _BV(OCIE2B));
}
