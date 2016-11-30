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
 * 
 * <div id="PLUGIN">
 * <h2>Comment brancher les composantes</h2>
 * <ul>
 *     <li>PORT A</li>
 *     <ul>
 *         <li>0-5: @link LineSnsr Suiveur de ligne@endlink. Les bits des
 *             capteurs sont du côté des bits moins significatifs.</li>
 *         <li>7: Bit de sortie du @link DistSnsr capteur de distance@endlink.</li>
 *     </ul>
 *     <li>PORT B</li>
 *     <ul>
 *         <li>0: Bit %LED du @link ColorSnsr capteur de couleur@endlink.</li>
 *         <li>1: Bit OUT du @link ColorSnsr capteur de couleur@endlink.</li>
 *         <li>2-3: Bits S0 et S1 (respectivement) du @link ColorSnsr capteur de couleur@endlink.</li>
 *         <li>4-5: Bits du @link Buzzer piézo-électrique@endlink.</li>
 *         <li>6-7: Bits S2 et S3 (respectivement) du @link ColorSnsr capteur de couleur@endlink.</li>
 *     </ul>
 *     <li>PORT C</li>
 *     <ul>
 *         <li>4-5: @link LED Del libre@endlink. La borne positive doit être
 *             vers l'extérieur de la carte (du même côté que le VCC).</li>
 *         <li></li>
 *     </ul>
 *     <li>PORT D</li>
 *     <ul>
 *         <li>0-5: @link LineSnsr Suiveur de ligne@endlink. Les bits des
 *             capteurs sont du côté des bits moins significatifs.</li>
 *         <li>7: Bit de sortie du @link DistSnsr capteur de distance@endlink.</li>
 *     </ul>
 * </ul>
 * 
 * </div>
 * 
 * <div id="HOWTO">
 * <h2>Faire fonctionner notre projet</h2>
 * 
 * Pour faire fonctionner le programme, il vous faut tout d'abord transférer le
 * bytecode des chemins dans la mémoire externe du robot afin que l'interpréteur
 * puisse les lire. Le programme a aussi besoin d'avoir la chanson à jouer
 * lorsque le robot a fini le parcours.
 * 
 * 
 * Pour transférer les chemins, ouvrez un terminal dans le répertoire
 * projet/gas/ puis entrez les commandes:
 * 
 *     $ make
 *     $ ./gas input.txt paths.bin; cp paths.bin ../src/transfert
 * 
 * Par la suite, assurez-vous que le robot est branché et
 * prêt à recevoir des données et rendez-vous dans le répertoire
 * projet/src/transfert/ pour entrer les commandes qui suivent:
 * 
 *     $ make install
 * 
 * La Del libre devrait s'allumer en rouge. Ensuite, faites la
 * commande suivante pour transférer les chemins sur la @link RAM mémoire externe@endlink
 * (le programme serieViaUSB doit être installé):
 * 
 *     $ serieViaUSB -e -h -s 8 -f paths.bin
 * 
 * La Del devrait clignoter faiblement avant de s'éteindre. Maintenant, les chemins
 * sont normalement transférés dans la mémoire et visibles pour l'interpréteur.
 * 
 * 
 * Pour transférer la chanson de fin, tout ce que vous devez faire est d'ouvrir un
 * terminal dans le répertoire projet/song/ et d'entrer la commande:
 * 
 *     $ make
 * 
 * Le processus est automatisé. La chanson qui se trouve dans le code du
 * sous-répertoire song_data/ est tout d'abord compilée en un fichier binaire pour
 * ensuite être transféré à l'aide du programme dans le répertoire projet/song/ .
 * Lors du transfert, la Del devrait clignoté entre vert et rouge puis, à la fin du
 * transfert, devrait s'éteindre.
 * 
 * 
 * Finalement, lorsque toutes les données ont été transférées dans la mémoire
 * externe, il ne reste plus qu'a envoyer le programme principale dans la mémoire
 * flash. Pour ce faire, vous devez ouvrir un terminal dans le répertoire
 * projet/src/ puis entrer la commande:
 * 
 *     $ make install
 * 
 * Le programme se compile et s'install automatiquement. Il ne reste plus qu'a
 * placer le robot sur la ligne de départ, enclancher les moteur et démarrer le
 * robot!
 * 
 * </div>
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
