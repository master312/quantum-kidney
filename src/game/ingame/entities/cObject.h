/* 
 * File:   cObject.h
 * Author: master312
 *
 * Created on August 15, 2015, 2:56 AM
 */

#ifndef COBJECT_H
#define	COBJECT_H
#include "cEntity.h"

class cObject : public cEntity {
public:
    cObject();
    virtual ~cObject();
    void OnDestroy();
private:
    
};

#endif	/* COBJECT_H */

