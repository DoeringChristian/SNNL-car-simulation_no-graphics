#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <math.h>

using namespace std;

struct vector2d{
    double x,y;
    vector2d();
    vector2d(double x,double y);
    vector2d(const vector2d &copy);
    
    vector2d operator +(const vector2d &toadd) const;
    void operator +=(const vector2d &toadd);
    vector2d operator -(const vector2d &tosub) const;
    void operator -=(const vector2d &tosub);
    void operator =(const vector2d &copy);
    vector2d operator *(double mult) const;
    void operator *=(double mult);
    vector2d operator /(double div) const;
    void operator /=(double div);
    double operator *(const vector2d &mult) const;
    double length() const;
    vector2d rotate(double angle) const;
    
};

#endif // VECTOR2D_H
