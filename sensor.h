#ifndef SENSOR_H
#define SENSOR_H
#include "world.h"
#define MAX_DOUBLE 10005

class world;

class sensor{
    double distance;
    vector2d A;
    vector2d E;
    double rotation;
public:
    double m_rotation;
    sensor();
    sensor(vector2d pos,double m_rotation);
    void setPosition(const vector2d &pos);
    void setRotation(double rotation);
    void update(world &w);
    double getDistance();
    void operator = (const sensor &copy);
};

#endif // SENSOR_H
