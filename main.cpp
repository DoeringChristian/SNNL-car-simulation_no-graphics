#include <iostream>
#include "simulation.h"
#include "network.h"

using namespace std;

int main(){
    double xq = 50;
    uint fTC = 0;
    uint a[2] = {2,2};
    world w;
    car c(w,vector2d(50,50));
    
    w.LoadFile("test.sim");
    
    Network n(a,2);
    n.LoadFile("test.snn");
    Trainer tr(n,0.1,5);
    Network n2 = n;
    n.randomize(1);
    while(true){
        
        
        n2.setInput(0,c.left.getDistance()/MAX_DOUBLE-0.5);
        n2.setInput(1,c.right.getDistance()/MAX_DOUBLE-0.5);
        n2.update();
        
        c.setRotspeed((n2.getOutput()[0]-0.5));
        c.setSpeed(n2.getOutput()[1]);
        
        cout <<  n2.getOutput()[0] << "|" << n2.getOutput()[1] << "|" << tr.currentNet << "|" << fTC << "|" << c.getPosition().x << endl;
        
        if(c.getPosition().x < 0 || c.getPosition().x > 10000 || c.isColliding() || fTC > 10000){
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
