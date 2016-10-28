#ifndef DEFAULT_ISR_H
#define DEFAULT_ISR_H

#include "lib.h"
#include "pinPosition.h"
#include "timer.h"
#include "led.h" // Nécessaire pour la déclaration de LedColor utilisé dans la fonction.
#include "uart.h" // Debug

class Timer; // Déclaration nécessaire pour résoudre la dépendance circulaire.

void intTimerChgAmberLedsColor(Timer* timer);

#endif // DEFAULT_ISR_H
