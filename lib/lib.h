/**
 * @file    lib.h
 * 
 * @brief   Fichier de symboles divers utilisés dans la librarie..
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
 * @mainpage BIENVENUE DANS LA DOCUMENTATION DE NOTRE LIBRAIRIE
 * @anchor  LIB_MAINPAGE
 * 
 * Notre répertoire Git contient trois documentations:
 * <ol type="1">
 *     <li>La documentation de notre [librairie](@ref LIB_MAINPAGE), située sous lib/ ;</li>
 *     <li>La documentation de notre [compilateur GAS](@ref GAS_MAINPAGE), situé sous projet/gas/; </li>
 *     <li>La documentation des [fichiers créés pour notre projet](@ref SRC_MAINPAGE), situés sous projet/src.</li>
 * </ol>
 */

#ifndef LIB_H
#define LIB_H

#include "incl.h"
#include "timer.h"
#include "led.h"

// ===============================
// =   SYMBOLES GLOBAUX DIVERS   =
// ===============================

/** @cond FALSE */ // Ne pas documenter ces macros.
#define EVER (;;) // for EVER { ... }

#ifndef nullptr
#define nullptr 0
#endif
/** @endcond */


#endif // LIB_H
