//Created by Petar Ostojic
//August 15, 2015, 3:29 AM

#ifndef CVECTOR2D_H
#define	CVECTOR2D_H
#include <iostream>
#include <math.h>

using namespace std;

class cVector2d {
public:
    cVector2d(float X = 0, float Y = 0);
    ~cVector2d() {}

    float x, y;

    cVector2d operator*(float scalar) const;
    cVector2d operator+(const cVector2d &vect) const;
    cVector2d operator-(const cVector2d &vect) const;
    
    void Rotate(float angle);
    float CrossProduct(const cVector2d &vect2) const;
    float Magnitude();
    void Normalise();
    float DotProduct(const cVector2d &vect) const;
    
    void Print();
};

#endif	/* CVECTOR2D_H */

