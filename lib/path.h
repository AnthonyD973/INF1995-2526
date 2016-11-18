//
//  path.h
//  
//
//  Created by Vincent Dandenault on 2016-11-16.
//
//

#ifndef PATH_H
#define PATH_H

#define   NB_PATHS 2

#include "lib.h"
#include "timer.h"
#include "ram.h"

class Path {
    
    public :
    
    static void forward();
    
    static void turn(bool dir);
    
    static void init();

    static void doPath(uint8_t path);
    
    
    
    
    private :
    
    static void readPath(pathAddr_ addr);
    uint16_t[NB_PATHS] pathAddr_; // 3 Adresses for the paths    
};


#endif /* path_h */
