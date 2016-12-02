/**
 * @file    gas/main.cpp
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
 * 
 * <div id="PLUGIN">
 * <h2>Comment brancher les composantes</h2>
 * </div>
 * <ul>
 *     <li>PORT A</li>
 *     <ul>
 *         <li>0-5: @link LineSnsr Suiveur de ligne@endlink. Les bits des
 *             capteurs sont du côté des bits moins significatifs.</li>
 *         <li>7: Bit OUT du @link DistSnsr capteur de distance@endlink.</li>
 *     </ul>
 *     <li>PORT B</li>
 *     <ul>
 *         <li>0-1: Bits %LED et OUT (respectivement) du @link ColorSnsr capteur de couleur@endlink.</li>
 *         <li>2-3: Bits du @link Buzzer piézo-électrique@endlink.</li>
 *     </ul>
 *     <li>PORT C</li>
 *     <ul>
 *         <li>2-3: Bits S0 et S1 (respectivement) du @link ColorSnsr capteur de couleur@endlink.</li>
 *         <li>4-5: @link LED Del libre@endlink. La borne positive doit être
 *             vers l'extérieur de la carte (du même côté que le VCC).</li>
 *         <li>6-7: Bits S2 et S3 (respectivement) du @link ColorSnsr capteur de couleur@endlink.</li>
 *     </ul>
 *     <li>PORT D</li>
 *     <ul>
 *         <li>4,6: Bits <i>Direction</i> et <i>Enable</i> du @link Engine moteur @endlink droit.</li>
 *         <li>5,7: Bits <i>Direction</i> et <i>Enable</i> du @link Engine moteur @endlink gauche.</li>
 *     </ul>
 * </ul>
 * 
 * <div if="SNSRS">
 * <h2>Placement des capteurs</h2>
 * </div>
 * 
 * <ul><li><b>@link LineSnsr Suiveur de lignes@endlink (LSS05)</b></li></ul>
 * Le suiveur de lignes est placé sous le robot et en avant.
 * 
 * <ul><li><b>@link DistSnsr Capteur de distance@endlink (GP2D12)</b></li></ul>
 * Le capteur de distance est placé sur le robot et en avant.
 * 
 * <ul><li><b>@link ColorSnsr Capteur de couleurs@endlink (TCS230)</b></li></ul>
 * Le capteur de couleurs est placé sur le robot et sur la droite.
 * 
 * 
 * <div id="HOWTO">
 * <h2>Faire fonctionner notre projet</h2>
 * </div>
 * 
 * Pour faire fonctionner votre robot, simplement exécuter la commande...
 * 
 *     $ make everything
 * 
 * ...dans le dossier projet/src
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