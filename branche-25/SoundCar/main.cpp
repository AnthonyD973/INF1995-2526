#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "Song.h"

#define EVER (;;)

volatile uint16_t ctr1         = ~(uint16_t(0));
volatile uint8_t  curSongIndex = 0;
volatile Tone     tone         = 0;
volatile Song     song;
volatile uint16_t factor       = 1,
                  divider      = 1,
                  nRep         = 1;

Memoire24CXXX ram = Memoire24CXXX();

void setPWM (const uint16_t& ratio);

ISR (INT0_vect) {
    _delay_ms(20);

    ++curSongIndex %= Song::nSongs;
    ctr1 = ~(uint16_t(0));
    setPWM(0/*,1*/);
    _delay_ms(250);

    EIFR |= _BV(INTF0);
}

void initialize() {
    cli();

    DDRA = DDRB = DDRC = 0xff;
    DDRD = 0xff & ~_BV(PD2); // Tout en OUT sauf D2 (INT0)
    
    PORTB = 0x2;

    ctr1 = ~(uint16_t(0));
    curSongIndex = 0;

    // mise a un des sorties OC1A et OC1B sur comparaison
    // reussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
    // page 130 de la description technique du ATmega324PA)
    TCCR1A = _BV(COM1A0); // 01000000

    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B = _BV(CS10) | _BV(WGM12); // 00001010
    TCCR1C = 0;

    EIMSK |= _BV(INT0);

    EICRA |= _BV(ISC01);

    sei();
}

void setPWM (const uint16_t& ratio/*, const uint8_t& prescale*/) {
    OCR1A = ratio;
    OCR1B = 0x00;

	TCCR1B = (TCCR1B & (0xff-0x7)) | ((ratio == 0x00) ? 0 : 1 << CS10);
}

/**
 * @brief Fonction principale du programme.
 */
int main() {
  initialize();
  UART::init(2400);
  uint8_t prevSongIndex = curSongIndex;
  
  bool songsLoaded = false;
  if(PIND & 0x04) {
    Song::saveToMemory(ram);
    songsLoaded = true;
  }
  else
    songsLoaded = Song::loadFromMemory(ram, 0x00);
  ctr1 = ~(uint16_t(0));
  _delay_ms(100);
  if(songsLoaded)
    Song::getSong(curSongIndex, song, ram);
  
  if(Song::nSongs >= 0) {
    for EVER {
      if(prevSongIndex != curSongIndex) {
        Song::getSong(curSongIndex, song, ram);
        prevSongIndex = curSongIndex;
      }
      if(song.nTones != 0)
        tone = song.tones[ctr1 %= song.nTones];
      
      //*
      if(((tone >> 4) & 0x03) >= 2) {
        factor  = 1 << (((tone >> 4) & 0x3) - 2);
        divider = 1;
      }
      else {
        factor  = 1;
        divider = 1 << (2 - ((tone >> 4) & 0x03));
      }//*/
      nRep = (tone >> 6) & 0x03;
      
      if((tone & 0x0f) == 0) {
        tone    = 0;
        factor  = 1;
        divider = 1;
      }
      
      setPWM(Song::freqs[tone & 0x0f] != 0 ? F_CPU/(factor * Song::freqs[tone & 0x0f] / divider) : 0);
      for (uint16_t i = 0; i < song.bps*(nRep+1); ++i) {
        _delay_ms(125.0/4.0); // 1/32 s
      }
      
      ++ctr1;
    }
  }

  return 0;
}
