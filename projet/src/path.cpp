#include "path.h"

uint16_t Path::pathAddr_[NB_PATHS];
Engine*  Path::engL_ = NULL;
Engine*  Path::engR_ = NULL;

/**
 * @brief   Vérifie s'il le robot est rendu à un branchement.
 * @param[in] input Valeur lue du détecteur de ligne.
 * @return  Si le robot est à un embranchement.
 */
bool checkBranch(uint8_t input);
/**
 * @brief   Vérifie si l'état reçu en paramètre est un état valide,
 *      c'est-à-dire, s'il s'agit d'un des états que l'on peut s'attendre à
 *      observer durant le parcours.
 * @param[in] input Valeur lue du détecteur de ligne.
 * @return  Si l'état présent est un état valide.
 */
bool checkValidState(uint8_t input);

const State
    S_BEGIN     = 0x1F, // Etat de début
    S_FOR1      = 0x04, // Etat avancement
    S_FOR2      = 0x0E,
    S_FOR3      = 0x0A,
    S_COR_R1    = 0x0C, // Etat correction vers la droite
    S_COR_R2    = 0x08,
    S_COR_L1    = 0x06, // Etat correction vers la gauche
    S_COR_L2    = 0x02,
    S_FCOR_R1   = 0x18, // Etat correction forcee droite
    S_FCOR_R2   = 0x10,
    S_FCOR_L1   = 0x03, // Etat correction forcee gauche
    S_FCOR_L2   = 0x01,
    S_B_R1      = 0x1C, // Etat Branchement à droite
    S_B_R2      = 0x1E,
    S_B_L1      = 0x07, // Etat Branchement à gauche
    S_B_L2      = 0x0F,
    S_STOP      = 0x1B; // Etat arret

// (VAL) * 256 / (MAX - MIN + 1)
//  18   * 256 / (80  - 10  + 1) = 65 = 0x41

// Distance que le capteur doit mesurer : ~18 cm
static const uint8_t MIDDLE_DIST = 94;

volatile State Path::etat = S_STOP;

/**
 * @brief   Fonction pour la routine d'interruption qui est utilisé pour faire
 *          une sorte de 'multi-threading'.
 */
void updateDirection(void) {
    if (checkValidState(LineSnsr::read()))
        Path::etat = State(LineSnsr::read());
    
    switch(Path::etat) {
    // ---AVANCEMENT---
    case S_BEGIN:   // fallthrough
    case S_B_L1:    // fallthrough
    case S_B_L2:    // fallthrough
    case S_B_R1:    // fallthrough
    case S_B_R2:    // fallthrough
    case S_FOR1:    // fallthrough
    case S_FOR2:    // fallthrough
    case S_FOR3:    Path::engL_->setPower(ENG_FORWARD,V_MAX);Path::engR_->setPower(ENG_FORWARD,V_MAX); break;
    // ---ARRÊT---
    case S_STOP:    Path::engL_->setMode(ENG_OFF);Path::engR_->setMode(ENG_OFF); break;
    // ---CORRECTION---
    case S_COR_R1:  // fallthrough
    case S_COR_R2:  Path::engL_->setPower(ENG_FORWARD,V_MAX);Path::engR_->setPower(ENG_FORWARD,V_MOY);break;
    case S_COR_L1:  // fallthrough
    case S_COR_L2:  Path::engL_->setPower(ENG_FORWARD,V_MOY);Path::engR_->setPower(ENG_FORWARD,V_MAX);break;
    // ---CORRECTION FORCÉE---
    case S_FCOR_R1: // fallthrough
    case S_FCOR_R2: Path::engL_->setPower(ENG_FORWARD,V_MOY);Path::engR_->setPower(ENG_BACKWARD,V_MOY);break;
    case S_FCOR_L1: // fallthrough
    case S_FCOR_L2: Path::engL_->setPower(ENG_BACKWARD,V_MOY);Path::engR_->setPower(ENG_FORWARD,V_MOY);break;
    // ---DÉFAUT---
    default: Path::engL_->setPower(ENG_FORWARD,V_MAX);Path::engR_->setPower(ENG_FORWARD,V_MAX); break;
    }
}

ISR(TIMER2_OVF_vect) {
    updateDirection();
}

bool checkBranch(uint8_t input) {
    switch(input) {
    case S_B_L1: // fallthrough
    case S_B_L2: // fallthrough
    case S_B_R1: // fallthrough
    case S_B_R2: return true;
    default: return false;
    }
}

bool checkValidState(uint8_t input) {
    switch(input) {
    case S_BEGIN:   // fallthrough
    case S_FOR1:    // fallthrough
    case S_FOR2:    // fallthrough
    case S_FOR3:    // fallthrough
    case S_COR_R1:  // fallthrough
    case S_COR_R2:  // fallthrough
    case S_COR_L1:  // fallthrough
    case S_COR_L2:  // fallthrough
    case S_FCOR_R1: // fallthrough
    case S_FCOR_R2: // fallthrough
    case S_FCOR_L1: // fallthrough
    case S_FCOR_L2: // fallthrough
    case S_STOP:    // fallthrough
    case S_B_L1:    // fallthrough
    case S_B_L2:    // fallthrough
    case S_B_R1:    // fallthrough
    case S_B_R2: return true;
    default: return false;
    }
}


void Path::init(Engine* engL, Engine* engR) {
    engL_ = engL;
    engR_ = engR;
    engL_->getTimer()->denyOVFI();
    RAM::init();
    readPath_(0x0000);
}

void Path::doPath(uint8_t path) {
    uint8_t  instr;
    uint16_t instrAddr = pathAddr_[path];
    RAM::read(instrAddr, &instr);
    while (instr != ENP_OP) {
        UART::transmitHex(pathAddr_[path]);
        UART::transmit(' ');
        UART::transmitHex(instr);
        UART::transmit('\n');
        switch (instr) {
        case INI_OP: ini(); break;
        case TNR_OP: tnr(); break;
        case TNL_OP: tnl(); break;
        case MDL_OP: mdl(); break;
        default:  enp(); break;
        }
        RAM::read(++instrAddr, &instr);
    }
    enp();
}

void Path::readPath_(uint16_t addr) {
    uint16_t pathCount = 0; // Nombre de chemins dans le fichier.
    RAM::read(addr+2, (uint8_t*)&pathCount, 2);
    for(uint8_t i = 0; i < pathCount; ++i) {
        RAM::read(addr + 4 + i*2, (uint8_t*)(&(pathAddr_[i])), 2);
    }
}

void Path::forward() {
    engL_->getTimer()->allowOVFI();
}

void Path::stop() {
    engL_->getTimer()->denyOVFI();
    engL_->setMode(ENG_OFF);
    engR_->setMode(ENG_OFF);
}

void Path::turn(RotDir dir, uint8_t speed) {
    engL_->getTimer()->denyOVFI();
    engL_->setPower( dir ? ENG_BACKWARD : ENG_FORWARD, speed);
    engR_->setPower(!dir ? ENG_BACKWARD : ENG_FORWARD, speed);
}

// +=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=+
// | instructions de l'interpréteur |
// +=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=+

void Path::ini(void) {
    // Les moteur sont arrêtés tant que le robot n'est pas sur la ligne de 
    // départ.
    stop();
    while (LineSnsr::read() != S_BEGIN);
    // On le fait avancer juste assez pour qu'il quite la ligne de départ...
    forward();
    _delay_ms(500.0);
    // puis on passe à l'instruction suivante
    stop();
}
void Path::tnr(void) {
    forward();
    _delay_ms(250.0);
    while (!checkBranch(LineSnsr::read()));
    stop();
    engL_->setPower(ENG_FORWARD, V_MAX);
    engR_->setPower(ENG_FORWARD, V_MAX);
    _delay_ms(1100.0);
    turn(ROT_RIGHT, V_MAX);
    _delay_ms(500.0);
    while (!(LineSnsr::read() & 0x08));
    forward();
    _delay_ms(500.0);
    stop();
}
void Path::tnl(void) {
    forward();
    _delay_ms(250.0);
    while (!checkBranch(LineSnsr::read()));
    stop();
    engL_->setPower(ENG_FORWARD, V_MAX);
    engR_->setPower(ENG_FORWARD, V_MAX);
    _delay_ms(1100.0);
    turn(ROT_LEFT, V_MAX);
    _delay_ms(500.0);
    while (!(LineSnsr::read() & 0x02));
    forward();
    _delay_ms(500.0);
    stop();
}
void Path::mdl(void) {
    forward();
    _delay_ms(1200.0);
    while (DistSnsr::readAverage() > MIDDLE_DIST);
    engL_->setMode(ENG_BACKWARD);
    engR_->setMode(ENG_BACKWARD);
    _delay_ms(300.0);
    stop();
    _delay_ms(500.0);
}
void Path::enp(void) {
    stop();
}
