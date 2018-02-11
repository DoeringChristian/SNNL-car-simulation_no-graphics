#include <iostream>
#include "simulation.h"
#include "network.h"

using namespace std;

int main(){
    srand(time(0));
    bool isVisible = true;
    vector2d car_prev;
    double score = 0;

    //set max generation
    int maxgen = -1;
    string in;
    cout << "max generations (-1 for infinit):" << endl;
    cin >> in;
    maxgen = atoi(in.c_str());

    uint fTC = 0;
    uint a[4] = {5,4,3,2};
    uint generation = 0;
    world w;
    car c(w,vector2d(50,50),5,0.02);
    c[0] = sensor(vector2d(0,0),1);
    c[1] = sensor(vector2d(0,0),-1);
    c[2] = sensor(vector2d(0,0),0.15);
    c[3] = sensor(vector2d(0,0),-0.15);
    c[4] = sensor(vector2d(0,0),0);
    
    
    w.LoadFile("test.sim");
    
    Network n(a,4,false);
    if(!n.LoadFile("test.snn"))
        n.randomize(1,2);
    Trainer tr(n,1,SOF_First_Second,10);
    n = tr.current();
    //n.randomize(1);
    while(true){
        
        
        for(uint i = 0;i < n.sizeAt(0);i++)
            n.setInput(i,c[i].getDistance()/MAX_DOUBLE-0.5);
        n.update();
        
        c.setRotspeed((n.getOutput()[0]-0.5));
        c.setSpeed(n.getOutput()[1]);
        score += (c.getPosition()-car_prev).length();
        car_prev = c.getPosition();
        
        //cout <<  n.getOutput()[0]-0.5 << "|" << n.getOutput()[1] << "|" << generation << "|" << tr.currentNet << "|" << fTC << "|" << c.getPosition().x << endl;        
        if(c.isColliding() || fTC > 10000 || (fTC > 1000 && c.getPosition().x < 60)){
            cout << "network: " << tr.currentNet << endl;
            if(tr.currentNet == tr.size()-1){
                cout << "generation: " << generation << " networks: ";
                generation++;
            }
            if(tr.currentNet == 0){
                ofstream log;
                log.open("log.txt",ofstream::out | ofstream::app);
                log << "score: " << score << " generation: " << generation << endl;
                log.close();
            }
            
            n = tr.update(-(score),0.1,0.1);//-((pow(c.getPosition().x,2)*0.01)/(pow(c.getPosition().x,2)*10)+0.01));//0.1/(c.getPosition().x-xq/fTC));//0.001);
            c.setPosition(vector2d(50,50));
            c.setRotation(1.5);
            car_prev = c.getPosition();
            score = 0;
            fTC = 0;
            tr[0].SavetoFile("test.snn");
             //max generation exeption
            if(generation >= maxgen && maxgen != -1)
                break;
        }
        fTC ++;

        w.update();
        c.upate();
    }
    tr[0].SavetoFile("test.snn");
    return 0;
}
