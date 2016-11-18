#include "timer.h"

Timer0 timer0(P01_NO_CLK);
Timer1 timer1(P01_NO_CLK);
Timer2 timer2(P2_NO_CLK);

// ===========================
// =          TIMER          =
// ===========================

// PUBLIC:

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
 * @brief Constructeur de Timer.
 */
Timer::Timer() :_nAmberLeds(0)
{
 UART::transmitCStr("Timer::Timer\n");
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
 * @brief   Change la valeur de TCNT0.
 * @param[in] tcnt0    Nouvelle valeur de TCNT0.
 */
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
 * @brief   Change la valeur de TCNT1.
 * @param[in] tcnt1    Nouvelle valeur de TCNT1.
 */
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
 * @brief   Change la valeur de TCNT2.
 * @param[in] tcnt2    Nouvelle valeur de TCNT2.
 */
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