/* 
 * File:   cNpc.h
 * Author: master312
 *
 * Created on August 14, 2015, 7:06 PM
 */

#ifndef CNPC_H
#define	CNPC_H
#include "cPawn.h"

class cNpc : public cPawn{
public:
    cNpc();
    virtual ~cNpc();
    void OnDestroy();

private:

};

#endif	/* CNPC_H */

