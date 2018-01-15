#include "cube.h"

cube::cube(){
    this->points = 0;
    this->length = 0;
}

cube::cube(vector2d pos, vector2d size){
    this->length = 4;
    this->points = new vector2d[length];
    this->points[0] = pos;
    this->points[1] = vector2d(pos.x + size.x,pos.y);
    this->points[2] = pos+size;
    this->points[3] = vector2d(pos.x,pos.y + size.y);
}
