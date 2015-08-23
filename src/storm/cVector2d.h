//Created by Petar Ostojic
//August 15, 2015, 3:29 AM

#ifndef CVECTOR2D_H
#define	CVECTOR2D_H
#include <iostream>
#include <math.h>

using namespace std;

class cVector2d {
public:
    cVector2d(double X = 0, double Y = 0);
    ~cVector2d() {}

    double x, y;

    cVector2d operator*(double scalar) const;
    cVector2d operator+(const cVector2d &vect) const;
    cVector2d operator-(const cVector2d &vect) const;
    
    void Rotate(double angle);
    double CrossProduct(const cVector2d &vect2) const;
    double Magnitude();
    void Normalise();
    double DotProduct(const cVector2d &vect) const;
    
    void Print();
};

#endif	/* CVECTOR2D_H */

