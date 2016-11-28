#ifndef GAS_H
#define GAS_H

#include <fstream>
#include <string>
#include <list>

// ---OPTIONS---
const std::string
    HELP  = "help", /**< @brief Affiche l'aide d'utilisation du programme. */
    EMAIL = "--send-email"; /**< @brief Transmet automatiquement un courriel à
                                        une adresse courriel avec le fichier
                                        compilé en pièce jointe. */

// ---NOM D'INSTRUCTIONS---
const std::string
    INI = "ini",  /**< @brief <b>INI</b>t: Attendre que les 5 capteurs de ligne
                              soient actifs, puis se déplacer en avant pendant
                              une demi-seconde. */
    TNL = "tnl",  /**< @brief <b>T</b>ur<b>N</b> <b>L</b>eft: Au prochain
                              embranchement, tourner à gauche. */
    TNR = "tnr",  /**< @brief <b>T</b>ur<b>N</b> <b>R</b>ight: Au prochain
                              embranchement, tourner à droite. */
    MDL = "mdl",  /**< @brief <b>M</b>i<b>D</b>d<b>L</b>e: Se mettre au milieu
                              de la pièce. */
    ENP = "enp";  /**< @brief <b>EN</b>d <b>P</b>ath: Le chemin est terminé ;
                              les prochaines instructions sont pour le chemin
                              suivant. */

// ---OPCODE DES INSTRUCTIONS---
const unsigned char
    INI_OP = 0x10, /**< @brief Opcode de INI. */
    TNL_OP = 0x20, /**< @brief Opcode de TNL. */
    TNR_OP = 0x21, /**< @brief Opcode de TNR. */
    MDL_OP = 0x30, /**< @brief Opcode de MDL. */
    ENP_OP = 0xF0; /**< @brief Opcode de ENP. */

/**
 * @brief   Classe du compilateur.
 * 
 * Utiliser la classe GAS se fait en appelant la méthode GAS::run.
 * 
 *
 * Le fichier s'organise comme suit:
 * <table>
 *     <tr>
 *         <th>Adresses</th>
 *         <td class="gave">0</td>
 *         <td class="gave" width="30px">2</td><td class="gave" width="30px">...</td><td class="gave" width="90px">2*nPaths + 2</td>
 *         <td class="gave" witdh="120px">beg = 2*nPaths + 4</td><td class="gave" witdh="30px">...</td><td class="gave" witdh="30px">beg + nInstrs</td>
 *     </tr>
 *     <tr>
 *         <th>Donnée (taille en o)</th>
 *         <td class="gave">Taille du fichier (2)</td>
 *         <td class="gave" colspan="3">Adresse relative du début de chaque chemin (2)</td>
 *         <td class="gave" colspan="3">@link Opcode Instructions @endlink compilées (1)</td>
 *     </tr>
 * </table>
 */
class GAS {
public:
    /**
     * @brief   Exécute la commande demandée. Voir GAS::_shouldCompile pour
     *      plus de précisions.
     * 
     * Si un fichier est compilé, le fichier de sortie est orgianisé selon la
     * structure suivante:
     * 
     * <table>
     * <tr><td class="gave">@link GAS::_addHeader En-tête @endlink</td><td class="gave">@link Opcode Instructions @endlink</td></tr>
     * </table>
     */
    static void run(int argc, char* argv[]);
    
private:
    /**
     * @brief   Instructions compilées (sans le header) qui seront mises dans
     *      le fichier.
     */
    static std::list<unsigned char> _instrs;
    /**
     * @brief   Adresses de début des chemins (avant l'ajout du header).
     */
    static std::list<unsigned short> _pathAddr;
    
    /**
     * @brief   Fichier %GAS d'entrée.
     */
    static std::ifstream _iFile;
    /**
     * @brief   Fichier binaire de sortie.
     */
    static std::ofstream _oFile;
    
    /**
     * @brief   Vérifie si on doit compiler et, le cas échéant, affiche l'aide ou
     *      transmet un courriel.
     * 
     * Voici la liste des trois cas où on ne compile pas, et les actions
     * correspondantes:
     * 
     * <ol type="1">
     *     <li>Si le nombre de paramètres est incorrect, alors afficher
     *         l'aide.</li>
     *     <li>Si l'utilisateur demande d'afficher l'aide, alors afficher
     *         l'aide.</li>
     *     <li>Si l'utilisateur demande de transmettre un courriel, alors
     *         appeler _sendEmail, qui se chargera de compiler et d'envoye un
     *         courriel.</li>
     * </ol>
     * @param[in] argc  Nombre d'arguments passés en argument de l'exécutable.
     * @param[in] argv  Arguments passés à l'exécutable.
     * @return Si GAS doit compiler le fichier.
     */
    static bool _shouldCompile(int argc, char* argv[]);
    /**
     * @brief   Gestionnaire de la compilation. Appelle les méthodes qui se
     *      chargeront de générer le fichier de sortie.
     * 
     * @param[in] ifName    Nom du fichier %GAS à partir duquel compiler.
     * @param[in,out] ofName    Nom du fichier de sortie désiré. Le fichier ne
     *      sera pas écrit/modifié si la compilation produit une erreur.
     */
    static void _compile(const std::string& ifName, const std::string& ofName);
    
    /**
     * @brief   Ouvre le fichier d'entrée #_iFile.
     * @param[in] ifName    Nom du fichier d'entrée.
     */
    static void _openInputFile(const std::string& ifName);
    /**
     * @brief   Ferme les fichiers #_iFile et #_oFile.
     */
    static void _closeFiles();
    
    /**
     * @brief   Initialise la classe GAS pour se préparer à une compilation.
     */
    static void _startOver();
    /**
     * @brief   Compile un fichier %GAS.
     * 
     * Émet un warning lorsque le fichier d'entrée ne se termine pas par
     * l'instruction ENP.
     */
    static void _compileInputFile();
    /**
     * @brief   Ajoute l'Opcode du paramètre dans la liste _instrs.
     * 
     * Émet une erreur lorsque l'instruction n'est pas valide.
     * 
     * @param[in] token Instruction %GAS à compiler.
     */
    static void _emitCodeFromToken(std::string token);
    /**
     * @brief   Ajoute l'en-tête di fichier compilé.
     * 
     * L'en-tête s'organise comme suit:
     * <table>
     *     <tr>
     *         <th>Adresses</th>
     *         <td class="gave">0</td><td class="gave" width="30px">2</td><td class="gave" width="30px">...</td><td class="gave" width="90px">2*nPaths + 2</td>
     *     </tr>
     *     <tr>
     *         <th>Donnée (taille en o)</th>
     *         <td class="gave">Taille du fichier (2)</td>
     *         <td class="gave" colspan="3">Adresse relative du début de chaque chemin (2)</td>
     *     </tr>
     * </table>
     */
    static void _addHeader();
    /**
     * @brief   Ouvre #_oFile et y place l'enemble des données (i.e. le header
     *      et les instructions).
     * @param[in,out] ofName    Nom du fichier de sortie désiré.
     */
    static void _flushIntoOutputFile(const std::string& ofName);
    /**
     * @brief   Affiche l'aide d'utilisation de %GAS.
     */
    static void _printHelp();
    /**
     * @brief   Compile le fichier d'entrée et transmet le fichier de sortie en
     *      pièce jointe par courriel.
     * @param[in] email Courriel vers lequel envoyer le fichier de sortie.
     */
    static void _sendEmail(const std::string& email);
};

std::string toLower(const std::string& str);

template <class T>
unsigned int computeLength(std::list<T> l);

#endif // GAS_H