#include "poligon.h"

poligon::poligon(){ 
    points = 0;
    length = 0;
}
poligon::poligon(uint length){
    this->length = length;
    this->points = new vector2d[length];
}
poligon::poligon(const poligon &copy){
    delete [] points;
    this->length = copy.length;
    this->points = new vector2d[length];
    for(uint i = 0;i < length;i++)
        this->points[i] = copy[i];
}

poligon::~poligon(){
    delete [] points;
}

void poligon::operator =(const poligon &copy){
    delete [] points;
    this->length = copy.length;
    this->points = new vector2d[length];
    for(uint i = 0;i < length;i++)
        this->points[i] = copy[i];
}

vector2d &poligon::operator [](uint index) const{
    return this->points[index];
}

uint poligon::size() const{
    return this->length;
}

void poligon::draw(){
    
}

bool poligon::Contains(const vector2d &inside) const{
    //test: on edge
    for(uint i = 0;i < this->size();i++){
        uint i2;
        if(i != 0)
            i2 = i-1;
        else 
            i2 = size()-1;
        if((points[i]-points[i2]).length() == (inside-points[i]).length()+(inside-points[i2]).length())
            return true;
    }
    //test: inside
    uint count = 0;
    for(uint i = 0;i < this->size();i++){
        uint i2;
        if(i != 0)
            i2 = i-1;
        else 
            i2 = size()-1;
        //formula for intersection of two lines
        vector2d A = points[i];
        vector2d B = points[i2];
        vector2d C = inside;
        vector2d D = vector2d(inside.x+1,inside.y);
        vector2d cross(0,0);
        double div =           (A.x-B.x)*(C.y-D.y)-(A.y-B.y)*(C.x-D.x);
        double xtop = ((A.x*B.y-A.y*B.x)*(C.x-D.x)-(A.x-B.x)*(C.x*D.y-D.x*C.y));
        double ytop = ((A.x*B.y-A.y*B.x)*(C.y-D.y)-(A.y-B.y)*(C.x*D.y-D.x*C.y));
        if(div != 0){
            cross.x = xtop/div;
            cross.y = ytop/div;
        }
        if((A-B).length()+1 >= (cross-A).length()+(cross-B).length())
            if((D-cross).length() < (C-cross).length())
                count++;
    }
    if(count % 2 == 1)
        return true;
    return false;
}















