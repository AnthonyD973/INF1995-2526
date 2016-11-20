/* 
 * Mini-compilateur de Gave Asm (GAS).
 *
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique
 * Cours inf1995
 *
 * Emir Khaled Belhaddad, Anthony Dentinger,
 * Gergi Younis et Vincent Dandenault
 * 2016
 *
 * Code qui n'est sous aucune license.
 *
 */

#include <clocale> // Pour setlocale
#include <iostream>
#include <string>

#include "gas.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, ""); // Pour les accents
	
	GAS::run(argc, argv);
	
	return 0;
}