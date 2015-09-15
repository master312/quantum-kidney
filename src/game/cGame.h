/* 
 * File:   cGame.h
 * Author: master312
 *
 * Created on August 13, 2015, 8:28 PM
 */
#ifndef CGAME_H
#define	CGAME_H
#include <time.h>
#include <iostream>
#include "../storm/engine.h"
#include "states/cStMainMenu.h"
#include "scripts/cLuaEngine.h"

class cGame {
public:
    cGame();
    ~cGame();
    void Start();
private:

};

#endif	/* CGAME_H */

