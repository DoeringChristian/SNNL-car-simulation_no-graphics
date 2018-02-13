#include "world.h"

world::world(){
    this->start = 0;
    this->end = 0;
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
    if(start == 0){
        start = new pnode;
        start->p = &insert;
        end = start;
    }
    else{
        end->next = new pnode;
        end->next->p = &insert;
        end->next->befor = end;
        end = end->next;
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

bool world::LoadFile(const string file){
    ifstream in;
    in.open(file.c_str());
    if(in.good()){
        char test = ' ';
        while(test != ';'){
            test = in.get();
        };
        string line;
        while(line != "end;"){
            line = "";
            char c = in.get();
            while(c != ';'){
                c = in.get();
                line.append(string(1,c));
            }
            if(line[0] == '\n')
                line = line.substr(1,line.length()-1);
            //add poligons
            if(line != "end;"){
                string coords = line.substr(line.find_first_of(':')+1,line.find_last_of(';')-line.find_first_of(':')-1);
                uint length = 0;
                for(uint i = 0;i < coords.length();i++)
                    if(coords[i] == '|')
                        length++;
                length++;
                poligon *p = new poligon(length);
                string splited[length];
                uint j = 0;
                for(uint i = 0;i < coords.length();i++){
                    if(coords[i] == '|')
                        j++;
                    else
                        splited[j] += coords[i];
                }
                for(uint i = 0;i < length;i++){
                    (*p)[i] = vector2d(atof(splited[i].substr(0,splited[i].find_first_of(',')).c_str()),
                                       atof(splited[i].substr(splited[i].find_first_of(',')+1,splited[i].length()-splited[i].find_first_of(',')).c_str()));
                }
                this->add(*p);
            }
        }
        
    }
    else
        return false;
    in.close();
}










