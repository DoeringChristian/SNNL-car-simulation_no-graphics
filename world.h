#ifndef WORLD_H
#define WORLD_H
#include "pnode.h"
#include "cube.h"
#include "sensor.h"
#include "string"
#include "fstream"
#include "iostream"
#include "stdlib.h"

using namespace std;

class world{
    pnode *start;
    pnode *end;
public:
    world();
    ~world();
    
    void add(poligon &insert);
    void del(poligon &del);
    uint size() const;
    poligon &operator [](uint index) const;
    
    void update();
    bool LoadFile(string file);
};

#endif // WORLD_H
