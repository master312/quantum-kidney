/* 
 * File:   cCommon.cpp
 * Author: master312
 * 
 * Created on August 13, 2015, 9:21 PM
 */

#include "cCommon.h"

cCommon *pubCommon = NULL;

cCommon::cCommon() {
}

cCommon::~cCommon() {
}

cCommon *GetCommon() {
    if(pubCommon == NULL)
        pubCommon = new cCommon();
    return pubCommon;
}
void DeleteCommon() {
    delete pubCommon;
}
