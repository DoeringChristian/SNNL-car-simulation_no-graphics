#include "car.h"

car::car(){
    this->size = vector2d(10,20);
    this->pos = vector2d(0,0);
    rotation = 0;
    rotspeed = 0;
    this->s = 0;
    length = 0;
    this->max_angle = 0.01;
}
car::car(world &w, vector2d pos, uint sensors, double max_angle, double rotation){
    this->pos = pos;
    this->rotation = rotation;
    this->w = &w;
    rotspeed = 0;
    length = sensors;
    s = new sensor[sensors];
    for(uint i = 0;i < sensors;i++)
        s[i] = sensor(pos,0);
    this->max_angle = max_angle;
}

car::~car(){
    delete [] s;
}

void car::operator =(const car &copy){
    if(this == &copy)
        return;
    delete [] s;
    this->length = copy.length;
    s = new sensor[length];
    for(uint i = 0;i < length;i++)
        s[i] = copy[i];
    this->max_angle = copy.max_angle;
    this->pos = copy.pos;
    this->rotation = copy.rotation;
    this->rotspeed = copy.rotspeed;
    this->size = copy.size;
    this->speed = copy.speed;
    this->w = copy.w;
}

void car::update(){
    this->rotation += rotspeed*speed;
    
    this->pos.x += sin(rotation)*speed;
    this->pos.y += cos(rotation)*speed;
    
    for(uint i = 0;i < getLength();i++){
        this->s[i].setPosition(pos);
        this->s[i].setRotation(rotation-s[i].m_rotation);
        this->s[i].update(*w);
    }
}

void car::setRotspeed(double rotspeed){
    if(rotspeed < max_angle && rotspeed > -max_angle)
        this->rotspeed = rotspeed;
    else if(rotspeed < 0)
        this->rotspeed = -max_angle;
    else
        this->rotspeed = max_angle;
}
void car::setSpeed(double speed){
    this->speed = speed;
}

vector2d car::getPosition() const{
    return this->pos;
}

void car::setPosition(vector2d pos){
    this->pos = pos;
}

void car::setRotation(double rotation){
    this->rotation = rotation;
}

bool car::isColliding(){
    for(uint i = 0;i < w->size();i++){
        vector2d A = (this->size*0.5).rotate(this->rotation)+this->pos;
        vector2d B = (vector2d(-this->size.x,-this->size.y)*0.5).rotate(this->rotation)+this->pos;
        vector2d C = (vector2d(this->size.x,-this->size.y)*0.5).rotate(this->rotation)+this->pos;
        vector2d D = (vector2d(-this->size.x,this->size.y)*0.5).rotate(this->rotation)+this->pos;
        if((*w)[i].Contains(A) || (*w)[i].Contains(B) || (*w)[i].Contains(C) || (*w)[i].Contains(D))
            return true;
    }
    return false;
}

uint car::getLength() const{
    return this->length;
}

sensor &car::operator [](const unsigned int i) const{
    return this->s[i];
}








