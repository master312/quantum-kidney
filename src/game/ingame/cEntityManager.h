/* 
 * File:   cEntityManager.h
 * Author: master312
 *
 * Created on August 23, 2015, 12:31 AM
 */

#ifndef CENTITYMANAGER_H
#define	CENTITYMANAGER_H
#include "../sCommon.h"
#include "entities/cPawn.h"
#include "map/cMapManager.h"
#include <vector>

class cEntityManager {
public:
    cEntityManager();
    ~cEntityManager();
    
    void Tick();
    void Draw();
    
    void PushEntity(cEntity *e);
private:
    std::vector<cEntity*> entities;

    void HandlePawn(cPawn *pawn);
};

#endif	/* CENTITYMANAGER_H */

