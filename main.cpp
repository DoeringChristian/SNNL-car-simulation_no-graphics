#include <iostream>
#include "simulation.h"
#include "network.h"

using namespace std;

int main(){
    srand(time(0));
    double xq = 50;
    bool isVisible = true;
    uint fTC = 0;
    uint a[4] = {5,4,3,2};
    uint generation = 0;
    world w;
    car c(w,vector2d(50,50),5,0.01);
    c[0] = sensor(vector2d(0,0),1);
    c[1] = sensor(vector2d(0,0),-1);
    c[2] = sensor(vector2d(0,0),0.15);
    c[3] = sensor(vector2d(0,0),-0.15);
    c[4] = sensor(vector2d(0,0),0);
    
    
    w.LoadFile("test.sim");
    
    Network n(a,4);
    n.LoadFile("test.snn");
    Trainer tr(n,1,10);
    Network n2 = n;
    //n.randomize(1);
    while(true){
        
        
        for(uint i = 0;i < n2.sizeAt(0);i++)
            n2.setInput(i,c[i].getDistance()/MAX_DOUBLE-0.5);
        n2.update();
        
        c.setRotspeed((n2.getOutput()[0]-0.5));
        c.setSpeed(n2.getOutput()[1]);
        
        cout <<  n2.getOutput()[0]-0.5 << "|" << n2.getOutput()[1] << "|" << generation << "|" << tr.currentNet << "|" << fTC << "|" << c.getPosition().x << endl;        
        if(c.isColliding() || fTC > 10000 || (fTC > 1000 && c.getPosition().x < 60)){
            xq /= fTC;
            if(tr.currentNet == 0){
                generation++;
                ofstream log;
                log.open("log.txt",ofstream::out | ofstream::app);
                log << "position: " << c.getPosition().x << " generation: " << generation << endl;
                log.close();
            }
            n2 = tr.update(-(c.getPosition().x-xq/fTC),0.1,0.1);//-((pow(c.getPosition().x,2)*0.01)/(pow(c.getPosition().x,2)*10)+0.01));//0.1/(c.getPosition().x-xq/fTC));//0.001);
            c.setPosition(vector2d(50,50));
            c.setRotation(1.5);
            xq = 50;
            fTC = 0;
            tr[0].SavetoFile("test.snn");
        }
        fTC ++;
        xq += sqrt(pow(c.getPosition().y-50,2));

        w.update();
        c.upate();
    }
    tr[0].SavetoFile("test.snn");
    return 0;
}
