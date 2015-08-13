/* 
 * File:   main.cpp
 * Author: master312
 *
 * Created on August 13, 2015, 7:58 PM
 */
#include "game/cGame.h"

int main(int argc, char** argv) {
    cGame *g = new cGame;
    g->Start();
    delete g;
    
    return 0;
}

