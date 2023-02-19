#ifndef GAMEBOARD_HPP_
#define GAMEBOARD_HPP_
#include "helper.h"
#include <string>
#include <vector>
using namespace std;

class Board
{
private:
    vector< vector<char> > map_; 
    int dimX_, dimY_, zombie_, alienX_, alienY_;
    char firstChar_, object_, tempObj_; 

public:
    Board(int dimX = 15, int dimY = 3, int zombie = 1);  // game board default settings | initialize
    void create(int dimX, int dimY, int zombie);  // creates board
    void display() const;  // display board
    void settings();  // change game settings
    void displaySettings();  // display settings
    void setObject(int x, int y, char ch);  // set object at index
    char getObject(int x, int y) const;  // get object at index
    void findObject(char object, int& x, int& y);

    // for other files
    int getNum(char item) const;
    char getChar(char item) const;

    //for alien
    void switchArrow();
    void moveAlien(string command); 
    void outputObj(); 
    void resetTrail();
    void podAtk(int x, int y);

    //for zombie
    void moveZombie(char count, int range, int atk);
    


};

#endif