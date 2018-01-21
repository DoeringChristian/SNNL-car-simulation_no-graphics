#ifndef POLIGON_H
#define POLIGON_H
#include "vector2d.h"

typedef unsigned int uint;

class poligon{
protected:
    vector2d *points;
    uint length;
public:
    poligon();
    poligon(uint length);
    poligon(const poligon &copy);
    ~poligon();
    
    vector2d &operator [](uint index) const;
    void operator =(const poligon &copy);
    uint size() const;
    void draw();
    bool Contains(const vector2d &inside) const;
};

#endif // POLIGON_H
