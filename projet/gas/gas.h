#ifndef GAS_H
#define GAS_H

#include <fstream>
#include <string>
#include <list>

// ---OPTIONS---
const std::string
    HELP  = "help",
    EMAIL = "--send-email";

// ---NOM D'INSTRUCTIONS---
const std::string
    INI = "ini",  // INIt: Attendre que les 5 capteurs de ligne soient actifs, puis se déplacer en avant pendant une demi-seconde.
    TNL = "tnl",  // TurN Left: Au prochain embranchement, tourner à gauche.
    TNR = "tnr",  // TurN Right: Au prochain embranchement, tourner à droite.
    MDL = "mdl",  // MiDdLe: Se mettre au milieu de la pièce.
    ENP = "enp";  // ENd Path: Le chemin est terminé ; les prochaines instructions sont pour le chemin suivant.

// ---OPCODE DES INSTRUCTIONS---
const unsigned char
    INI_OP = 0x10, // INIt: Attendre que les 5 capteurs de ligne soient actifs, puis se déplacer en avant pendant une demi-seconde.
    TNL_OP = 0x20, // TurN Left: Au prochain embranchement, tourner à gauche.
    TNR_OP = 0x21, // TurN Right: Au prochain embranchement, tourner à droite.
    MDL_OP = 0x30, // MiDdLe: Se mettre au milieu de la pièce.
    ENP_OP = 0xF0; // ENd Path: Le chemin est terminé ; les prochaines instructions sont pour le chemin suivant.

class GAS {
public:
    static void compile(const std::string& ifName, const std::string& ofName); 
    static bool shouldCompile(int argc, char* argv[]);

private:
    /**
     * @brief   Instructions compilées qui seront mises dans le fichier.
     */
    static std::list<unsigned char> _instrs;
    
    static std::ifstream _iFile;
    static std::ofstream _oFile;
    
    static void _openFiles(const std::string& ifName, const std::string& ofName);
    static void _closeFiles();
    
    static void _compileInputFile();
    static void _emitCodeFromToken(std::string token);
    static void _flushIntoOutputFile();
    static void _printHelp();
    static void _printSendEmail(const std::string& email);
};

std::string toLower(const std::string& str);

#endif // GAS_H