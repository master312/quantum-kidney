#include "cVector2d.h"

cVector2d::cVector2d(float X, float Y) { 
    x = X;
    y = Y;
}

cVector2d cVector2d::operator*(float scalar) const {
    return cVector2d(x * scalar, y * scalar);
}
cVector2d cVector2d::operator+(const cVector2d &vect) const {
    return cVector2d(x + vect.x, y + vect.y);
}
cVector2d cVector2d::operator-(const cVector2d &vect) const {
    return cVector2d(x - vect.x, y - vect.y);
}

void cVector2d::Rotate(float angle) {
    float xt = (x * cos(angle)) - (y * sin(angle));
    float yt = (y * cos(angle)) + (x * sin(angle));
    x = xt;
    y = yt;
}
float cVector2d::CrossProduct(const cVector2d &vect2) const {
    return (this->x * vect2.y) - (this->y * vect2.x);
}
float cVector2d::Magnitude() {
    return sqrt(x * x +y * y);
}
void cVector2d::Normalise() {
    float mag = sqrt(x * x + y * y);
    this->x = x / mag;
    this->y = y / mag;
}
float cVector2d::DotProduct(const cVector2d &vect) const {
    return (x * vect.x) + (y * vect.y);
}
void cVector2d::Print() {
    cout << "Vector: X=" << x << " Y=" << y << endl;
}