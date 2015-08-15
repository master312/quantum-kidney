/* 
 * File:   cPlayerDriver.h
 * Author: master312
 *
 * Created on August 15, 2015, 3:14 AM
 * This class controls player input. Movement, spell cast, item drop, etc...
 */

#ifndef CPLAYERDRIVER_H
#define	CPLAYERDRIVER_H
#include "entities/cCharacter.h"
#include "../../storm/engine.h"
#include "sKeyBinds.h"

class cPlayerDriver {
public:
    cPlayerDriver();
    ~cPlayerDriver();
    /* Initialize player handler */
    void Init();
    /* Event handler callback function */
    void HandleEvents();
    
    void SetCharacter(cCharacter *_character);
    cCharacter *GetCharacter() { return character; }
private:
    cCharacter *character;
    sKeyBinds binds;
};

#endif	/* CPLAYERDRIVER_H */

