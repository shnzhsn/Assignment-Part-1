#ifndef zombie_HPP_
#define zombie_HPP_
#include "helper.h"
using namespace std;

class Zombie
{
private:
    int life_, atk_, range_, count_, dimX_, dimY_; 
public:
    Zombie(int life = 100, int atk = 0, int range = 0);  // initialize
    void getZombie(int count);  // get zombie count from gameboard
    void getdimY(int count);  // get dimY from gameboard
    void getdimX(int count);  // get dimX from gameboard
    void randomAttribute();  // randomize attribute
    void attribute();  // zombie attributes

};

#endif