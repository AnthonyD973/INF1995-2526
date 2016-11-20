//
//  path.cpp
//  
//
//  Created by Vincent Dandenault on 2016-11-18.
//
//

#include "path.h"

uint16_t Path::pathAddr_[NB_PATHS];
Engine*  Path::engL_ = NULL;
Engine*  Path::engR_ = NULL;

/**
 * @brief   Vérifie s'il le robot est rendu à un branchement.
 */
bool checkBranch(uint8_t input);
/**
 * @brief   Verifie si l'état reçu en paramètre est un état valide.
 */
bool checkValidState(uint8_t input);

const State
    S_BEGIN     = 0x1F, // Etat de debut
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

const uint8_t
    V_MAX = 0xAF,
    V_MOY = 0x6F,
    V_MIN = 0x00;

// (VAL) * 256 / (MAX - MIN + 1)
//  18   * 256 / (80  - 10  + 1) = 65 = 0x41

// distance que le capteur doit mesurer : ~18 cm
static const uint8_t MIDDLE_DIST = 0x41;

volatile State Path::etat = S_STOP;

/**
 * @brief   Routine d'interruption qui est utilisé pour faire du multi-threading.
 */
ISR(TIMER0_OVF_vect) {
    if (checkValidState(LineSnsr::read()))
        Path::etat = State(LineSnsr::read()); // State(...) : Nice code m8!!
    
    switch(Path::etat) {
    case S_BEGIN:   //fallthrough
    case S_FOR1:    //fallthrough
    case S_FOR2:    //fallthrough
    case S_FOR3:    Path::engL_->setPower(ENG_FORWARD,V_MAX);Path::engR_->setPower(ENG_FORWARD,V_MAX); break;
    case S_COR_R1:  //fallthrough
    case S_COR_R2:  Path::engL_->setPower(ENG_FORWARD,V_MAX);Path::engR_->setPower(ENG_FORWARD,V_MOY);break;
    case S_COR_L1:  //fallthrough
    case S_COR_L2:  Path::engL_->setPower(ENG_FORWARD,V_MOY);Path::engR_->setPower(ENG_FORWARD,V_MAX);break;
    case S_FCOR_R1: //fallthrough
    case S_FCOR_R2: Path::engL_->setPower(ENG_FORWARD,V_MAX);Path::engR_->setPower(ENG_OFF,V_MIN);break;
    case S_FCOR_L1: //fallthrough
    case S_FCOR_L2: Path::engL_->setPower(ENG_OFF,V_MIN);Path::engR_->setPower(ENG_FORWARD,V_MAX);break;
    case S_STOP:    //fallthrough
    default: Path::engL_->setMode(ENG_OFF);Path::engR_->setMode(ENG_OFF);
    }
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
    case S_BEGIN:   //fallthrough
    case S_FOR1:    //fallthrough
    case S_FOR2:    //fallthrough
    case S_FOR3:    //fallthrough
    case S_COR_R1:  //fallthrough
    case S_COR_R2:  //fallthrough
    case S_COR_L1:  //fallthrough
    case S_COR_L2:  //fallthrough
    case S_FCOR_R1: //fallthrough
    case S_FCOR_R2: //fallthrough
    case S_FCOR_L1: //fallthrough
    case S_FCOR_L2: //fallthrough
    case S_STOP: return true;
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
    uint16_t pathCount = 0; // Nombre de chemin dans le fichier.
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

void Path::turn(RotDir dir) {
    engL_->getTimer()->denyOVFI();
    engL_->setPower( dir ? ENG_BACKWARD : ENG_FORWARD, V_MAX);
    engR_->setPower(!dir ? ENG_BACKWARD : ENG_FORWARD, V_MAX);
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
    while (!checkBranch(LineSnsr::read()));
    _delay_ms(1000.0);
    turn(ROT_RIGHT);
    _delay_ms(1000.0);
    Path::etat = S_FCOR_R1;
    forward();
    while (!(LineSnsr::read() & 0x08));
    stop();
}
void Path::tnl(void) {
    forward();
    while (!checkBranch(LineSnsr::read()));
    _delay_ms(1000.0);
    turn(ROT_LEFT);
    _delay_ms(1000.0);
    Path::etat = S_FCOR_L1;
    forward();
    while (!(LineSnsr::read() & 0x02));
    stop();
}
void Path::mdl(void) {
    forward();
    while (LineSnsr::read() != S_STOP);
    //while (DistSnsr::read() > MIDDLE_DIST);
    stop();
}
void Path::enp(void) {
    stop();
}
