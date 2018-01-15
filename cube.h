#ifndef CUBE_H
#define CUBE_H
#include "poligon.h"

class cube : public poligon{
    vector2d size;
    vector2d pos;
public:
    cube();
    cube(vector2d pos,vector2d size);
    
};

#endif // CUBE_H
