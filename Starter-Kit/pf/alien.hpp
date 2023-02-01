#ifndef ALIEN_HPP_
#define ALIEN_HPP_
#include "helper.h"
#include <string>
using namespace std;

class Alien
{
private:
    int life_, atk_;
    string command_;
public:
    Alien(int life = 80, int atk = 0);  // initializer
    void attribute();  // alien attributes
    void command();  // alien command
    string getCommand(); // to return command in main 
    void help();  // display help list
    void updateAttribute(char obj);  // update attribute found  
};

#endif