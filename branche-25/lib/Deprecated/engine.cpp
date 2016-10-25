#include "engine.h"

/**
 * @brief Définit l'état d'un moteur (allumé ou éteint, vers l'avant ou
 *        l'arrière).
 * @param[in] state  État voulu du moteur (Utiliser préférablement les
 *                   constantes prédéfinites).
 * @param[in] side   Le moteur que l'on doit changer d'état (Utiliser
 *                   préférablement les constantes prédéfinites).
 */
void engineControl(const uint8_t& state, const uint8_t& side) {
    //      (Reset the bits for the target motor) | (and set them to the new state)
    PORT_OUT = (PORT_OUT & ~uint8_t(0x3 << side)) | (state << side);
}

/**
 * @brief Change l'état des deux moteurs en générant un signal PWM pendant 2 secondes.
 * @param[in] frequency Fréquence du signal PWM (Hz). Doit valoir 60 ou 400.
 * @param[in] ratio	Ratio de niveau haut. Doit valoir 0, 25, 50, 75 ou 100.
 */
void enginePower(const uint16_t& frequency, const uint8_t& ratio)
{
  if (ratio == 0) {
    engineControl(ENG_OFF, ENG_L);
    engineControl(ENG_OFF, ENG_R);
    _delay_ms(2000.0);
    return;
  }
  else if (ratio == 100) {
    engineControl(ENG_ON | ENG_FW, ENG_L);
    engineControl(ENG_ON | ENG_FW, ENG_R);
    _delay_ms(2000.0);
    return;
  }
  
  if (frequency == 60) {
    // f = 60 Hz => 1/f = 16.6667 ms
    switch (ratio) {
      
      case 25:
	for (uint8_t i = 0; i < 120; ++i) {
	  engineControl(ENG_OFF, ENG_L);
	  engineControl(ENG_OFF, ENG_R);
	  _delay_ms(12.5);
	  engineControl(ENG_ON | ENG_FW, ENG_L);
	  engineControl(ENG_ON | ENG_FW, ENG_R);
	  _delay_ms(4.16667);
	}
	break;
	
      case 50:
	for (uint8_t i = 0; i < 120; ++i) {
	  engineControl(ENG_OFF, ENG_L);
	  engineControl(ENG_OFF, ENG_R);
	  _delay_ms(8.33333);
	  engineControl(ENG_ON | ENG_FW, ENG_L);
	  engineControl(ENG_ON | ENG_FW, ENG_R);
	  _delay_ms(8.33333);
	}
	break;
	
      case 75:
	for (uint8_t i = 0; i < 120; ++i) {
	  engineControl(ENG_OFF, ENG_L);
	  engineControl(ENG_OFF, ENG_R);
	  _delay_ms(4.16667);
	  engineControl(ENG_ON | ENG_FW, ENG_L);
	  engineControl(ENG_ON | ENG_FW, ENG_R);
	  _delay_ms(12.5);
	}
	break;
	
      default:
	break;
	
    }
  }
  else if (frequency == 400) {
    // f = 400 Hz => 1/f = 2.5 ms
    switch (ratio) {
      
      case 25:
	for (uint16_t i = 0; i < 800; ++i) {
	  engineControl(ENG_OFF, ENG_L);
	  engineControl(ENG_OFF, ENG_R);
	  _delay_ms(1.875);
	  engineControl(ENG_ON | ENG_FW, ENG_L);
	  engineControl(ENG_ON | ENG_FW, ENG_R);
	  _delay_ms(0.625);
	}
	break;
	
      case 50:
	for (uint16_t i = 0; i < 800; ++i) {
	  engineControl(ENG_OFF, ENG_L);
	  engineControl(ENG_OFF, ENG_R);
	  _delay_ms(1.25);
	  engineControl(ENG_ON | ENG_FW, ENG_L);
	  engineControl(ENG_ON | ENG_FW, ENG_R);
	  _delay_ms(1.25);
	}
	break;
	
      case 75:
	for (uint16_t i = 0; i < 800; ++i) {
	  engineControl(ENG_OFF, ENG_L);
	  engineControl(ENG_OFF, ENG_R);
	  _delay_ms(0.625);
	  engineControl(ENG_ON | ENG_FW, ENG_L);
	  engineControl(ENG_ON | ENG_FW, ENG_R);
	  _delay_ms(1.875);
	}
	break;
	
      default:
	break;
	
    }
  }
  
}
