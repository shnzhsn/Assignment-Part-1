#ifndef CHARACTERS_HPP_
#define CHARACTERS_HPP_
#include "helper.h"
#include <string>
#include <vector>
using namespace std;

class Alien
{
private:
    int life_, atk_;
    string command_;
public:
    Alien(int life = 100, int atk = 0);  // initializer
    void attribute();  // alien attributes
    void command();  // alien command
    string getCommand(); // to return command in main 
    void help();  // display help list
    void updateAttribute(char obj, int z);  // update attribute found  
    int getAtk();
    int getLife();
};

class Zombie
{
private:
    int count_, dimX_, dimY_;
    vector< vector<int> > zombie_; 
public:
    Zombie(int count = 1, int dimX = 15, int dimY = 3);  // initialize
    void getZombie(int count);  // get zombie count from gameboard
    void getdimY(int count);  // get dimY from gameboard
    void getdimX(int count);  // get dimX from gameboard
    void randomAttribute();  // randomize attribute
    void attribute();  // zombie attributes
    void updateAttribute(char obj, int atk);  // update attribute 
    int getLife(char obj);
    int getRange(char obj);
    int getAtk(char obj);

};

#endif