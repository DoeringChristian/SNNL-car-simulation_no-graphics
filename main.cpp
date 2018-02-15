#include <iostream>
#include "simulation.h"
#include "network.h"

using namespace std;

int main(int argc, char *argv[]){
    double max_score = 0;
    double randomness = 0.3,shift = 0.1;
    string saveto = "test.snn";
    string loadfrom = "test.snn";
    string config = "config.txt";
    uint population = 10;
    int maxgen = -1;

    if(argc <= 1){
        cout << "max generations (-1 for infinit):" << endl;
        cin >> maxgen;
        cout << "settings file:" << endl;
        cin >> config;
        
    }
    else{
        if(argc > 1)
            maxgen = atoi(argv[1]);
        if(argc > 2)
            config = argv[2];
    }
    ifstream con;
    con.open(config.c_str());
    if(con.is_open()){
        con >> saveto;
        con >> loadfrom;
        con >> population;
        con >> randomness;
        con >> shift;
        cout << randomness << "|" << shift << endl;
    }
    con.close();
        

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
    
    
    w.LoadFile("world.sim");
    
    Network n(a,4,false);
    if(!n.LoadFile(loadfrom))
        n.randomize(1,2);
    Trainer tr(n,population);
    
    car agents[tr.size()];
    for(uint i = 0;i < tr.size();i++)
        agents[i] = c;
    vector2d car_prev[tr.size()];
    bool isAlive[tr.size()];
    for(uint i = 0;i < tr.size();i++)
        isAlive[i] = true;
    
    while(true){
        
        for(uint i = 0;i < tr.size();i++){
            if(isAlive[i])
                agents[i].update();
            for(uint j = 0;j < tr[i].sizeAt(0);j++)
                tr[i].setInput(j,agents[i][j].getDistance()/MAX_DOUBLE-0.5);
            tr[i].update();
            agents[i].setRotspeed(tr[i].getOutput()[0]-0.5);
            agents[i].setSpeed(tr[i].getOutput()[1]);
            tr[i].setFitness(tr[i].getFitness()-(agents[i].getPosition()-car_prev[i]).length());
            car_prev[i] = agents[i].getPosition();
            if(-tr[i].getFitness() > max_score)
                max_score = -tr[i].getFitness();
        }
        bool crash = true;
        for(uint i = 0;i < tr.size();i++){
            if(!agents[i].isColliding())
                crash = false;
            isAlive[i] = !agents[i].isColliding();
        }
        if(fTC > 1000)
            for(uint i = 0;i < tr.size();i++)
                if(tr[i].getFitness() > -10)
                    isAlive[i] = false;
       
        
        if(crash || fTC > 10000){
            //log has to be befor update
            cout << "generation: " << generation << " best: " << tr[tr.best()].getFitness() << " fitness: ";
            for(uint i = 0;i < tr.size();i++)
                cout << tr[i].getFitness() << "|";
            cout << endl;
            //logging:
            ofstream log;
            log.open("log.txt",ofstream::out | ofstream::app);
            log << "score: " << tr[tr.best()].getFitness() << " generation: " << generation << endl;
            log.close();
            tr[tr.best()].SavetoFile(saveto);
            
            tr.update(randomness,shift);
            for(uint i = 0;i < tr.size();i++){
                agents[i] = c;
                isAlive[i] = true;
                car_prev[i] = agents[i].getPosition();
            }
            generation++;
            
            fTC = 0;
            tr.resetFitness();
            if(maxgen > -1 && generation > maxgen)
                break;
        }
        else
            fTC ++;

        w.update();
    }
    tr[0].SavetoFile(saveto);
    return 0;
}
