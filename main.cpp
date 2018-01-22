#include <iostream>
#include "simulation.h"
#include "network.h"

using namespace std;

int main(){
    double xq = 50;
    bool isVisible = true;
    uint fTC = 0;
    uint a[4] = {5,4,3,2};
    world w;
    car c(w,vector2d(50,50),5);
    c[0] = sensor(vector2d(0,0),1);
    c[1] = sensor(vector2d(0,0),-1);
    c[2] = sensor(vector2d(0,0),0.15);
    c[3] = sensor(vector2d(0,0),-0.15);
    c[4] = sensor(vector2d(0,0),0);
    
    
    w.LoadFile("test.sim");
    
    Network n(a,4);
    n.LoadFile("test.snn");
    Trainer tr(n,0.1,10);
    Network n2 = n;
    n.randomize(1);
    while(true){
        
        
        for(uint i = 0;i < n2.sizeAt(0);i++)
            n2.setInput(i,c[i].getDistance()/MAX_DOUBLE-0.5);
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
        
        w.update();
        c.upate();
    }
    tr[0].SavetoFile("test.snn");
    return 0;
}
