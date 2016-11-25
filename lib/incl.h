#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define _MASK(reg, value, mask) (reg = ((reg) & ~(mask)) | ((value) & (mask))) // Change la valeur de certains bits d'un registre.
#define _MASKV(reg, value, mask) (((reg) & ~(mask)) | ((value) & (mask))) // Retourne la valeur d'un mask appliqué à certain bits
