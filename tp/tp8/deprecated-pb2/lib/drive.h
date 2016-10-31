#ifndef DRIVE_H
#define DRIVE_H

#include "lib.h"
#include "timer.h"
#include "engine.h"

class Drive {
public:
	Drive(Engine& engL, Engine& engR);
    
    power(uint8_t ratio255);
	
private:
	Engine* const _engL, * const _engR;
};

#endif // DRIVE_H