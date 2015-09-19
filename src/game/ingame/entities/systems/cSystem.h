/* 
 * File:   cSystem.h
 * Author: master312
 *
 * Created on September 16, 2015, 8:25 PM
 */

#ifndef CSYSTEM_H
#define	CSYSTEM_H
#include <vector>

class cComponent;

class cSystem {
public:
    virtual ~cSystem() { }
    virtual void Draw() { }
    virtual void Tick() { }
    virtual void Register(cComponent *com) {
        components.push_back(com);
    }
    virtual void UnRegister(cComponent *com) {
        int i = 0;
        for(auto &c : components){
            if(c == com){
                components.erase(components.begin() + i);
                return;
            }
            i++;
        }
    }
protected:
    std::vector<cComponent*> components;

};

#endif	/* CSYSTEM_H */

