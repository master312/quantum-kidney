/* 
 * File:   main.cpp
 * Author: master312
 *
 * Created on August 13, 2015, 7:58 PM
 */

#include <iostream>
#include "storm/engine.h"

int main(int argc, char** argv) {
    S_InitEngine(STORM_API_SDL2);
    
    std::cout << "Test test, test!" << std::endl;
    
    return 0;
}

