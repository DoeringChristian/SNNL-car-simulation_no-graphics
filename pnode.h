#ifndef PNODE_H
#define PNODE_H
#include "poligon.h"

struct pnode{
    pnode *next;
    pnode *befor;
    poligon *p;
    pnode();
    ~pnode();
};

#endif // PNODE_H
