#include "vector2d.h"

vector2d::vector2d(){
    this->x = 0;
    this->y = 0;
}
vector2d::vector2d(double x, double y){
    this->x = x;
    this->y = y;
}
vector2d::vector2d(const vector2d &copy){
    this->x = copy.x;
    this->y = copy.y;
}

vector2d vector2d::operator +(const vector2d &toadd) const{
    return vector2d(this->x + toadd.x,this->y + toadd.y);
}

void vector2d::operator +=(const vector2d &toadd){
    this->x += toadd.x;
    this->y += toadd.y;
}

vector2d vector2d::operator -(const vector2d &tosub) const{
    return vector2d(this->x - tosub.x,this->y - tosub.y);
}

void vector2d::operator -=(const vector2d &tosub){
    this->x -= tosub.x;
    this->y -= tosub.y;
}

void vector2d::operator =(const vector2d &copy){
    this->x = copy.x;
    this->y = copy.y;
}

double vector2d::length() const{
    return sqrt(pow(x,2)+pow(y,2));
}

vector2d vector2d::operator *(double mult) const{
    return vector2d(this->x*mult,this->y*mult);
}
void vector2d::operator *=(double mult){
    this->x *= mult;
    this->y *= mult;
}

vector2d vector2d::operator /(double div) const{
    return vector2d(this->x / div,this->y / div);
}
void vector2d::operator /=(double div){
    this->x /= div;
    this->y /= div;
}

double vector2d::operator *(const vector2d &mult) const{
    return this->x*mult.x+this->y+mult.y;
}

vector2d vector2d::rotate(double angle) const{
    return vector2d(this->x*cos(angle)+this->y*sin(angle),this->x*(-sin(angle))+this->y*cos(angle));
}








