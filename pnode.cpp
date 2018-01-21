#include "pnode.h"

pnode::pnode(){
	next = 0;
	befor = 0;
	p = 0;
}

pnode::~pnode(){
    delete p;
}
