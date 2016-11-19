#include "gas.h"

#include <iostream>
#include <algorithm>

void printHelp() {
    std::cout << "HELPING YOU." << '\n';
}


std::string toLower(const std::string& str) {
    std::string ret;
    
    for (size_t i = 0; i < str.length(); ++i) {
        ret.push_back(tolower(str[i]));
    }
    
    return ret;
}