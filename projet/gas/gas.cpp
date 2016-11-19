#include "gas.h"

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <algorithm>

std::list<unsigned char> GAS::_instrs = std::list<unsigned char>();

std::ifstream GAS::_iFile = std::ifstream();
std::ofstream GAS::_oFile = std::ofstream();

void GAS::compile(const std::string& ifName, const std::string& ofName) {
    _instrs.clear();
    
    _openFiles(ifName, ofName);
    
    _compileInputFile();
    
    _flushIntoOutputFile();
    _closeFiles();
}

bool GAS::shouldCompile(int argc, char* argv[])
{
    bool shldCmple = true;
    if (argc != 3 || (argc == 2 && toLower(std::string(argv[1])) == HELP)) {
        _printHelp();
        shldCmple = false;
    } else if (argc == 3 && toLower(std::string(argv[1])) == EMAIL) {
        _printSendEmail(argv[2]);
        shldCmple = false;
    }
    return shldCmple;
}


void GAS::_openFiles(const std::string& ifName, const std::string& ofName) {
    _iFile.open(ifName);
    
    if (_iFile.fail()) {
        throw std::runtime_error("ERREUR: Le fichier \"" + ifName + "\" n'a pas été trouvé.");
        return;
    }
    
    _oFile.open(ofName);
    if (_oFile.fail()) {
        throw std::runtime_error("ERREUR: Le fichier \"" + ofName + "\" n'a pas pu être ouvert.");
    }
}

void GAS::_closeFiles() {
    _iFile.close();
    _oFile.close();
}

void GAS::_compileInputFile() {
    std::string token;
    while (_iFile.peek() != EOF) {
        _iFile >> token;
        _emitCodeFromToken(toLower(token));
    }
}


void GAS::_emitCodeFromToken(std::string token) {
    unsigned char curOp;
    
    // Toutes les instructions ont 3 caractères
    if (token.length() != 3) {
        throw std::logic_error("ERREUR: Opération inconnue: \"" + token + "\"");
    }
    // Vérifier si l'instruction courante est une des instructions valides.
    else if   (token == INI) {
        curOp = INI_OP;
    } else if (token == TNL) {
        curOp = TNL_OP;
    } else if (token == TNR) {
        curOp = TNR_OP;
    } else if (token == MDL) {
        curOp = MDL_OP;
    } else if (token == ENP) {
        curOp = ENP_OP;
    }
    else {
        throw std::logic_error("ERREUR: Opération inconnue: \"" + token + "\"");
    }
    
    _instrs.push_back(curOp);
}

void GAS::_flushIntoOutputFile() {
    std::copy(_instrs.begin(), _instrs.end(), std::ostream_iterator<unsigned char>(_oFile));
}

void GAS::_printHelp() {
    std::cout << "\n"
        "------------------------------------------------------------------------\n"
            "\t+----------------+\n"
            "\t|      AIDE      |\n"
            "\t+----------------+\n"
        "\n"
        "---UTILISATION GÉNÉRALE---:\n"
        "$ gas <fichier d'entrée> <fichier de sortie> --Génère un fichier compilé à\n"
        "      partir d'un fichier source écrit en GAS.\n"
        "\n"
        "---AUTRES OPTIONS:\n"
        "$ gas help --Affiche l'aide d'utilisation de GAS.\n"
        "$ gas --send-email <email> --Envoyer un email avec le fichier en sortie comme\n"
        "      pièce jointe.\n"
        "\n"
        "---FORMAT DE FICHIER D'ENTRÉE---\n"
        "Le fichier doit contenir une combinaison des cinq instructions suivantes\n"
        "(casse ignorée) séparées par des caractères blancs (espace, retour chariot,\n"
        "tabulation):\n"
        "INI --Attendre que les 5 capteurs de ligne soient actifs, puis se déplacer en\n"
        "      avant pendant une demi-seconde.\n"
        "TNL --Au prochain embranchement, tourner à gauche.\n"
        "TNR --Au prochain embranchement, tourner à droite.\n"
        "MDL --Se mettre au milieu de la pièce.\n"
        "ENP --Le chemin est terminé ; les prochaines instructions sont pour le chemin\n"
        "      suivant.\n"
        "------------------------------------------------------------------------\n\n";
}

void GAS::_printSendEmail(const std::string& email) {
    std::cout <<
    "We are sorry, CHUCK NORRIS stole that feature.\n\n"
    "                                      MMMMMMMMMMM\n"
    "                                   MMMMMMMMMMMMMMMMM\n"
    "                               NMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                             MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                            MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN\n"
    "                            MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                           MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                           MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMD\n"
    "                          DMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                          MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                          MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                         MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                         MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                        MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN\n"
    "                        MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN\n"
    "                       MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN\n"
    "                       MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN\n"
    "  NM                  MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "  MMMMM              MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "   MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "    MMMMMMMMMMMMMMMMMMMMMMMMMM8MMMMMMMMMIMMMMM8,. ...........OMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "       MMMMMMMMMMMMMMMMMMMMMMM ..N. .....~MMMM...............:MMMMNMMMMMMMMMMMMMMMMMMMMMMM\n"
    "         NMMMMMMMMMMMMMMMMMMMMM.....:..DMMMMMNZ Z.... .......M$MMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "             MMMMMMMMMMNMMMMMMM....... 7=MMMMMMO....Z .......MM7MMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                MMMMMMMMMMMMMMMMM  Z...MMMZ .. .,M..,........MMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                    MMMMMM.......DOM ....N7..................MMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                       MMM....... M. ... .  ... ..............M...$MMMMMMMMMMMMMMMMMMMM\n"
    "                         ........... ........~. ..............M..=....+MMMMMMMMMMMMMM\n"
    "                         ......+.NMI~........ . ..............M.,.I...MMMMMMMMMMMMMMN\n"
    "                         ......$... ...... O..................,.....$MMMMMMMMMMMMN\n"
    "                         .....M.......... M M.. .............. 8  .OMMMMMMMMMMMN\n"
    "                          ..=7I,,.,,IMI...M.................. ..MMMMMMMMMMM\n"
    "                          ....DMMMMMMMMMMMMMMMO..............D...MMMMMMMMM\n"
    "                           .MMMMMMMMMMMMMMDDMM:,N..............DMMMMMMMMMMM\n"
    "                           NMMMMMNMM8 . .... ...,~............  MMMMMMMMM\n"
    "                           MMMMM,:......::~..M8M8MM...............MMMMMM\n"
    "                           MMMM ... . .........,MM..............MMMMMO$\n"
    "                           MMMMM... =.=. .. . . MM ....... . ...MMMMMMM\n"
    "                            NMMMMMMMMMM?  ..O.?NM7 ....... ......MMMMMM\n"
    "                             NMMMMMMMMMMMMMMMMM........  $ . ...MMMNMMM\n"
    "                              MMMMMMMMMMMMMMM.........,, ......MMMMMMMM\n"
    "                               OMMMMMMMM8 , .. .. .,N.... ...:MMMMMMMMMMN\n"
    "                                MMMMMMMM?N. ...~MD.:MNI8MMMMMMMMMMMMMMMMMN\n"
    "                           MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN\n"
    "                        NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN\n"
    "                       MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN\n"
    "                    MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                 MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "                NMMMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n"
    "               MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM\n\n";
}

std::string toLower(const std::string& str) {
    std::string ret;
    
    for (size_t i = 0; i < str.length(); ++i) {
        ret.push_back(tolower(str[i]));
    }
    
    return ret;
}