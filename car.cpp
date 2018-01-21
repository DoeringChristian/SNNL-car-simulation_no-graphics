#include "car.h"

car::car(){
    this->size = vector2d(10,20);
    this->pos = vector2d(0,0);
    rotation = 0;
    rotspeed = 0;
    sensorangel = 0.15;
    speed = 0;
}
car::car(world &w,vector2d pos, double rotation){
    this->pos = pos;
    this->rotation = rotation;
    this->w = &w;
    rotspeed = 0;
    sensorangel = 0.15;
    speed = 0;
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








