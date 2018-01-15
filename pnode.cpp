#include "pnode.h"

pnode::pnode(){
    this->befor = 0;
    this->next = 0;
    this->p = 0;
}

pnode::~pnode(){
    delete p;
}
