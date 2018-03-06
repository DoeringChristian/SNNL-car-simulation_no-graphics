#ifndef CAR_H
#define CAR_H
#include "vector2d.h"
#include "world.h"

class sensor;

class car{
    vector2d pos;
    double rotation;
    double rotspeed;
    double speed;
    world *w;
    vector2d size;
    sensor *s;
    uint length;
public:
    car();
    car(world &w, vector2d pos, uint sensors, double rotation = 1.5);
    ~car();
    void operator =(const car &copy);
    void update();
    void setRotspeed(double rotspeed);
    void setSpeed(double speed);
    vector2d getPosition() const;
    void setPosition(vector2d pos);
    void setRotation(double rotation);
    bool isColliding();
    uint getLength() const;
    sensor &operator [](const unsigned int i) const;
    
};

#endif // CAR_H
