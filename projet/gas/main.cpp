/**
 * @file    main.cpp
 * 
 * @brief   Fichier principal du compilateur %GAS.
 * 
 * @authors Belhaddad, Emir Khaled
 * @authors Dandenault, Vincent
 * @authors Dentinger, Anthony
 * @authors Younis, Gergi
 * 
 * @date Automne 2016
 * 
 * @copyright Code qui n'est sous aucune license.
 */

/**
 * @mainpage BIENVENUE DANS LA DOCUMENTATION DE GAVE ASSEMBLER (%GAS)
 * @anchor  GAS_MAINPAGE
 * 
 * Notre répertoire Git contient trois documentations:
 * <ol type="1">
 *     <li>La documentation de notre [librairie](@ref LIB_MAINPAGE), située sous lib/ ;</li>
 *     <li>La documentation de notre [compilateur GAS](@ref GAS_MAINPAGE), situé sous projet/gas/; </li>
 *     <li>La documentation des [fichiers créés pour notre projet](@ref SRC_MAINPAGE), situés sous projet/src.</li>
 * </ol>
 */

#include <clocale> // Pour setlocale
#include <iostream>
#include <string>

#include "gas.h"

/** @cond FALSE */ // Ne pas documenter cett fonction.
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, ""); // Pour les accents
	
	GAS::run(argc, argv);
	
	return 0;
}
/** @endcond */