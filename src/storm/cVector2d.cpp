#include "cVector2d.h"

cVector2d::cVector2d(double X, double Y) { 
    x = X;
    y = Y;
}

cVector2d cVector2d::operator*(double scalar) const {
    return cVector2d(x * scalar, y * scalar);
}
cVector2d cVector2d::operator+(const cVector2d &vect) const {
    return cVector2d(x + vect.x, y + vect.y);
}
cVector2d cVector2d::operator-(const cVector2d &vect) const {
    return cVector2d(x - vect.x, y - vect.y);
}

void cVector2d::Rotate(double angle) {
    double xt = (x * cos(angle)) - (y * sin(angle));
    double yt = (y * cos(angle)) + (x * sin(angle));
    x = xt;
    y = yt;
}
double cVector2d::CrossProduct(const cVector2d &vect2) const {
    return (this->x * vect2.y) - (this->y * vect2.x);
}
double cVector2d::Magnitude() {
    return sqrt(x * x +y * y);
}
void cVector2d::Normalise() {
    double mag = sqrt(x * x + y * y);
    this->x = x / mag;
    this->y = y / mag;
}
double cVector2d::DotProduct(const cVector2d &vect) const {
    return (x * vect.x) + (y * vect.y);
}
void cVector2d::Print() {
    cout << "Vector: X=" << x << " Y=" << y << endl;
}