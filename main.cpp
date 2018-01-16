#include <iostream>
#include "simulation.h"
#include "network.h"

using namespace std;

int main(){
    double xq = 50;
    uint fTC = 0;
    uint a[5] = {2,3,5,3,2};
    world w;
    car c(w,vector2d(50,50));
    
    poligon p1(2);
    p1[0] = vector2d(0,0);
    p1[1] = vector2d(10000,0);
    poligon p2(2);
    p2[0] = vector2d(0,0);
    p2[1] = vector2d(0,100);
    poligon p3(2);
    p3[0] = vector2d(0,100);
    p3[1] = vector2d(10000,100);
    w.add(p1);
    w.add(p2);
    w.add(p3);
    
    Network n(a,5);
    n.LoadFile("test.snn");
    Trainer tr(n,0.1,10);
    Network n2 = n;
    n.randomize(1);
    while(true){
        
        
        n2.setInput(0,c.left.getDistance()/MAX_DOUBLE-0.5);
        n2.setInput(1,c.right.getDistance()/MAX_DOUBLE-0.5);
        n2.update();
        c.setRotspeed(n2.getOutput()[0]-n2.getOutput()[1]);
        c.setSpeed((n2.getOutput()[0]+n2.getOutput()[1])/2);
        
        cout <<  n2.getOutput()[0] << "|" << n2.getOutput()[1] << "|" << tr.currentNet << "|" << fTC << "|" << c.getPosition().x << endl;
        
        if(c.getPosition().x < 0 || c.getPosition().x > 10000 || c.getPosition().y < 0 || c.getPosition().y > 100 || fTC > 10000){
            xq /= fTC;
            n2 = tr.update(-(c.getPosition().x-xq/fTC),1/(c.getPosition().x-xq/fTC));//0.001);
            c.setPosition(vector2d(50,50));
            c.setRotation(1.5);
            xq = 50;
            fTC = 0;
            tr[0].SavetoFile("test.snn");
        }
        fTC ++;
        xq += sqrt(pow(c.getPosition().y-50,2));
        
        srand(time(0));
        
        c.upate();
        w.update();
    }
    tr[0].SavetoFile("test.snn");
    return 0;
}
