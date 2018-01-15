#include "world.h"

world::world(){
    start = 0;
    end = 0;
}
world::~world(){
    if(start != 0){
        pnode *n = start;
        while(n != end){
            n = n->next;
            delete n->befor;
        }
        delete n;
    }
}

void world::add(poligon &insert){
    pnode *n = start;
    if(n == 0){
        start = new pnode;
        start->p = &insert;
        end = start;
    }
    else{
        while(n != end)
            n = n->next;
        pnode *n2 = new pnode;
        end = n2;
        n->next = n2;
        n2->befor = n;
        n2->p = &insert;
    }
}

void world::del(poligon &del){
    pnode *n = start;
    if(start != 0){
        while(n != 0){
            if(n->p == &del){
                if(n->next != 0)
                    n->next->befor = n->befor;
                else
                    end = n->befor;
                if(n->befor != 0)
                    n->befor->next = n->next;
                else
                    start = n->next;
                delete n;
                break;
            }
            n = n->next;
        }
    }
}

void world::update(){
    pnode *n = start;
    if(start != 0){
        while(n != 0){
            n->p->draw();
            n = n->next;
        }
    }
}

uint world::size() const{
    uint i = 0;
    pnode *n = start;
    while(n != 0){
        i++;
        n = n->next;
    }
    return i;
}

poligon &world::operator [](uint index) const{
    pnode *n = start;
    uint i = 0;
    while(index > i && n != 0){
        i++;
        n = n->next;
    }
    return *(n->p);
}










