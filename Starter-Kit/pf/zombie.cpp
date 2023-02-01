#include "zombie.hpp"
#include <iostream>
#include <string>
using namespace std;

//initialize
Zombie::Zombie(int life, int atk, int range)
{
    life_ = life;
    atk_ = atk;
    range_ = range;
}

// get zombie count from gameboard
void Zombie::getZombie(int count)
{
    count_ = count;
}

// get dimX
void Zombie::getdimX(int dimX)
{
    dimX_ = dimX;
}

// get dimY
void Zombie::getdimY(int dimY)
{
    dimY_ = dimY;
}

// randomize zombie attributes
void Zombie::randomAttribute()
{
    int life[] = {50, 100, 150, 200, 250};
    int atk[] = {5, 10, 15, 20};
    
    life_ = life[rand() % 5];
    atk_ = atk[rand() % 4]; 
    if (dimX_ <= dimY_)
    {
        range_ = 1 + (rand() % (dimX_-1));  // make sure range between 1 and dim-1

    }

    else
    {
        range_ = 1 + (rand() % (dimY_-1));
    }
}

// zombie attributes
void Zombie::attribute()
{
    for (int i = 1; i <= count_; ++i)
    {
        randomAttribute();
        cout << "Zombie " << i << ": Life " << life_ << ", Attack " << atk_ << ", Range " << range_ << endl;
    }

    cout << endl;
}

