#include "car.h"

car::car(){
    this->rotation = 0;
    this->rotspeed = 0;
    this->sensorangel = 0.15;
    this->size = vector2d(10,20);
    this->pos = vector2d(0,0);
}
car::car(world &w,vector2d pos, double rotation){
    this->rotation = 0;
    this->rotspeed = 0;
    this->sensorangel = 0.15;
    this->pos = pos;
    this->rotation = rotation;
    this->w = &w;
}

void car::upate(){
    this->rotation += rotspeed*speed;
    
    this->pos.x += sin(rotation)*speed;
    this->pos.y += cos(rotation)*speed;
    
    left.setPosition(pos);
    right.setPosition(pos);
    this->left.setRotation(rotation-sensorangel);
    this->right.setRotation(rotation+sensorangel);
    left.update(*w);
    right.update(*w);
    
}

void car::setRotspeed(double rotspeed){
    this->rotspeed = rotspeed;
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








