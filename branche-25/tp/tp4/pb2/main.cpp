#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "engine.h"
#include "lib.h"

#define EVER (;;)


/**
 * @brief Fonction principale du programme.
 */
int main() {
    DDRD = 0x00;		// Entrées
    DDRA = DDRB = DDRC = 0xff;	// Sorties
    
    
    
    // Boucle d'exécution infinie.
     enginePower(60,  0);
     enginePower(60,  25);
     enginePower(60,  50);
     enginePower(60,  75);
     enginePower(60, 100);
     
     enginePower(400,  0);
     enginePower(400, 25);
     enginePower(400, 50);
     enginePower(400, 75);
     enginePower(400,100);
     
     enginePower(60,   0);
    
    
    return 0;
}
