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
        if((points[i]-points[i2]).length()+0.001 >= (inside-points[i]).length()+(inside-points[i2]).length())
            return true;
    }
    //test: inside
    bool odd = false;
    int j = size()-1;
    for(uint i = 0;i < this->size();i++){
        if((points[i].y < inside.y && points[j].y > inside.y) 
                || (points[i].y > inside.y && points[j].y < inside.y))
            if(points[i].x+(inside.y-points[i].y)/(points[j].y-points[i].y)*(points[j].x-points[i].x) < inside.x)
                odd = !odd;
        j = i;
    }
    return odd;
}















