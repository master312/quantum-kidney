/* 
 * File:   cCharacter.cpp
 * Author: master312
 * 
 * Created on August 14, 2015, 7:06 PM
 */

#include "cCharacter.h"

cCharacter::cCharacter() {
    type = character;
}
cCharacter::~cCharacter() {
}
void cCharacter::OnDestroy() {
    UnloadSprites();
}


