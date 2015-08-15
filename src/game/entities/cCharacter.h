/* 
 * File:   cCharacter.h
 * Author: master312
 *
 * Created on August 14, 2015, 7:06 PM
 */

#ifndef CCHARACTER_H
#define	CCHARACTER_H
#include "cPawn.h"

class cCharacter : public cPawn {
public:
    cCharacter();
    virtual ~cCharacter();
    void OnDestroy();
private:

};

#endif	/* CCHARACTER_H */

