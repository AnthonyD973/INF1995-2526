#include "path.h"

const PathState
    S_BEGIN   = 0x1F, // Etat de début
    S_FOR1    = 0x04, // Etat avancement
    S_FOR2    = 0x0E,
    S_FOR3    = 0x0A,
    S_COR_R1  = 0x0C, // Etat correction vers la droite
    S_COR_R2  = 0x08,
    S_COR_L1  = 0x06, // Etat correction vers la gauche
    S_COR_L2  = 0x02,
    S_FCOR_R1 = 0x18, // Etat correction forcee droite
    S_FCOR_R2 = 0x10,
    S_FCOR_L1 = 0x03, // Etat correction forcee gauche
    S_FCOR_L2 = 0x01,
    S_B_R1    = 0x1C, // Etat Branchement à droite
    S_B_R2    = 0x1E,
    S_B_L1    = 0x07, // Etat Branchement à gauche
    S_B_L2    = 0x0F,
    S_STOP    = 0x1B; // Etat arret


Engine* Path::engL_ = nullptr;
Engine* Path::engR_ = nullptr;
volatile PathState Path::currPathState_ = S_STOP;

const uint8_t Path::MIDDLE_DIST_ = 0x5E;
uint16_t Path::pathAddrs_[NB_PATHS];


ISR(TIMER2_OVF_vect) {
    Path::updateDirection_();
}


// ====================
// =       PATH       =
// ====================

// PUBLIC

void Path::init(Engine* engL, Engine* engR) {
    engL_ = engL;
    engR_ = engR;
    engL_->getTimer()->denyOVFI();
    RAM::init();
    populatePathAddrs_(0x0000);
}

void Path::doPath(uint8_t path) {
    uint8_t  instr;
    uint16_t instrAddr = pathAddrs_[path];
    
    RAM::read(instrAddr, &instr);
    while (instr != ENP_OP) {
        switch (instr) {
         case INI_OP: ini_(); break;
         case TNR_OP: tnr_(); break;
         case TNL_OP: tnl_(); break;
         case MDL_OP: mdl_(); break;
         default:     enp_(); break;
        }
        RAM::read(++instrAddr, &instr);
    }
    
    enp_();
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
    engL_->setPower(dir == ROT_LEFT ? ENG_BACKWARD : ENG_FORWARD,  speed);
    engR_->setPower(dir == ROT_LEFT ? ENG_FORWARD  : ENG_BACKWARD, speed);
}

void Path::updateDirection_() {
    if (isValidState_(LineSnsr::read())) {
        currPathState_ = PathState(LineSnsr::read());
    }
    
    EngineMode engLMode, engRMode;
    uint16_t   engLPwr,  engRPwr;
    
    switch(currPathState_) {
     // ---AVANCEMENT---
     case S_BEGIN:   // fallthrough
     case S_B_L1:    // fallthrough
     case S_B_L2:    // fallthrough
     case S_B_R1:    // fallthrough
     case S_B_R2:    // fallthrough
     case S_FOR1:    // fallthrough
     case S_FOR2:    // fallthrough
     case S_FOR3:    engLMode = ENG_FORWARD;  engLPwr = V_MAX;
                     engRMode = ENG_FORWARD;  engRPwr = V_MAX;
                     break;
     // ---ARRÊT---
     case S_STOP:    engLMode = ENG_OFF;      engLPwr = V_MIN;
                     engRMode = ENG_OFF;      engRPwr = V_MIN;
                     break;
     // ---CORRECTION---
     case S_COR_R1:  // fallthrough
     case S_COR_R2:  engLMode = ENG_FORWARD;  engLPwr = V_MAX;
                     engRMode = ENG_FORWARD;  engRPwr = V_MOY;
                     break;
     case S_COR_L1:  // fallthrough
     case S_COR_L2:  engLMode = ENG_FORWARD;  engLPwr = V_MOY;
                     engRMode = ENG_FORWARD;  engRPwr = V_MAX;
                     break;
     // ---CORRECTION FORCÉE---
     case S_FCOR_R1: // fallthrough
     case S_FCOR_R2: engLMode = ENG_FORWARD;  engLPwr = V_MOY;
                     engRMode = ENG_BACKWARD; engRPwr = V_MOY;
                     break;
     case S_FCOR_L1: // fallthrough
     case S_FCOR_L2: engLMode = ENG_BACKWARD; engLPwr = V_MOY;
                     engRMode = ENG_FORWARD;  engRPwr = V_MOY;
                     break;
     // ---DÉFAUT---
     default:        engLMode = ENG_FORWARD;  engLPwr = V_MAX;
                     engRMode = ENG_FORWARD;  engRPwr = V_MAX;
                     break;
    }
    engL_->setPower(engLMode, engLPwr);
    engR_->setPower(engRMode, engRPwr);
    
}

// PRIVATE

bool Path::isBranch_(uint8_t input) {
    switch(input) {
     case S_B_L1: // fallthrough
     case S_B_L2: // fallthrough
     case S_B_R1: // fallthrough
     case S_B_R2: return true;
     default:     return false;
    }
}

bool Path::isValidState_(uint8_t input) {
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
     default:     return false;
    }
}

void Path::populatePathAddrs_(uint16_t fileBegAddr) {
    uint16_t nPaths = 0;
    RAM::read(fileBegAddr + 2, (uint8_t*)&nPaths, 2);
    
    for(uint8_t i = 0; i < nPaths; ++i) {
        uint16_t addrToPathAddr = fileBegAddr + 4 + 2 * i;
        RAM::read(addrToPathAddr, (uint8_t*)(pathAddrs_ + i), 2);
    }
}

// ====================
// =  INSTRUCTIONS DE = 
// =  L'INTERPRÉTEUR  =
// ====================

void Path::ini_() {
    stop();
    while (LineSnsr::read() != S_BEGIN); // Attendre d'être sur la ligne de départ
    
    forward();
    _delay_ms(500.0); // Dépasser la ligne de départ avant la prochaine instruction
                      // pour éviter de trouver des branchements là où il n'y
    stop();           // en a pas.
    
}

void Path::tnl_() {
    forward();
    _delay_ms(250.0); // S'assurer d'être stable sur la ligne pour éviter de
                      // trouver des branchements là où il n'y en a pas.
    
    while (!isBranch_(LineSnsr::read())); // Attendre un branchement.
    
    stop();
    engL_->setPower(ENG_FORWARD, V_MAX);
    engR_->setPower(ENG_FORWARD, V_MAX);
    _delay_ms(1100.0); // S'avancer jusqu'à ce que les roues soient vis-à-vis
                       // du branchement.
    
    turn(ROT_LEFT, V_MAX);
    _delay_ms(500.0); // Quitter la ligne
    
    while (!(LineSnsr::read() & 0x02)); // Attendre de trouver la ligne vers
                                        // laquelle on tourne.
    forward();
    _delay_ms(500.0); // S'assurer d'être stable sur la ligne pour éviter de
                      // trouver des branchements là où il n'y en a pas.
    stop();
}

void Path::tnr_() {
    forward();
    _delay_ms(250.0); // S'assurer d'être stable sur la ligne pour éviter de
                      // trouver des branchements là où il n'y en a pas.
    
    while (!isBranch_(LineSnsr::read())); // Attendre un branchement.
    
    stop();
    engL_->setPower(ENG_FORWARD, V_MAX);
    engR_->setPower(ENG_FORWARD, V_MAX);
    _delay_ms(1100.0); // S'avancer jusqu'à ce que les roues soient vis-à-vis
                       // du branchement.
    
    turn(ROT_RIGHT, V_MAX);
    _delay_ms(500.0); // Quitter la ligne
    
    while (!(LineSnsr::read() & 0x08)); // Attendre de trouver la ligne vers
                                        // laquelle on tourne.
    
    forward();
    _delay_ms(500.0); // S'assurer d'être stable sur la ligne pour éviter de
                      // trouver des branchements là où il n'y en a pas.
    stop();
}

void Path::mdl_() {
    forward();
    _delay_ms(2000.0); // Dépasser la porte d'entrée dans la pièce.
    
    while (DistSnsr::readAverage() > MIDDLE_DIST_);
    engL_->setMode(ENG_BACKWARD);
    engR_->setMode(ENG_BACKWARD);
    _delay_ms(300.0); // S'arrêter le plus vite possible.
    
    stop();
    _delay_ms(500.0); // Attendre la fin du mouvement.
}

void Path::enp_() {
    stop();
}
