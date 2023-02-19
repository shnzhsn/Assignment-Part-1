#include "characters.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

// ALIEN
Alien::Alien(int life, int atk)
{
    life_ = life;
    atk_ = atk;
}

void Alien::attribute()
{
    if (life_ > 100)
        life_ = 100;
    cout << "Alien   : Life " << life_ << ", Attack " << atk_ << endl;
}

void Alien::help()
{
    cout << "Commands" << endl;
    cout << "1. up - Move Up" << endl << "2. down - Move Down" << endl;
    cout << "3. left - Move Left" << endl << "4. right - Move Right" << endl;
    cout << "5. arrow - Change arrow direction" << endl << "6. help - Display command list" << endl;
    cout << "7. quit - Quit Game" << endl << endl;
    command();  //back to command function
}

void Alien::command()
{
    cout << "<command> ";
    cin >> command_;
    for (int i = 0; i < command_.size(); i++)  // turn command_ to lowercase
    {
        command_[i] = tolower(command_[i]);
    }

    if (command_ == "help" || command_ == "up" || command_ == "down" || command_ == "left" || command_ == "right" || command_ == "arrow" || command_ == "quit")
    {
        char firstChar = command_[0];  //first character for switch
        switch(firstChar)
        {
            case 'h':
                help();
                break;
            case 'q':
                cout << "Goodbye!" << endl;
                exit(0);
                break;
        }
    }

    else
    {
        cout << "Invalid Command" << endl;
        command();
    }
}

string Alien::getCommand()
{
    return command_;
}

void Alien::updateAttribute(char obj, int z)
{
    Zombie zombie;
    switch(obj)
    {
        case 'h':
            life_ = life_ + 20;
            break;
        case '>':
        case '<':
        case '^':
        case 'v':
            atk_ = atk_ + 20;
            break;
            
        case 'n':
        case 'r':
        case 's':
            atk_ = 0;
            break;

        // zombie attack alien
        case 'z':
            life_ = life_ - z;
            break;

    }
}

int Alien::getAtk()
{
    return atk_;
}

int Alien::getLife()
{
    return life_;
}


// ZOMBIE
Zombie::Zombie(int count, int dimX, int dimY)
{
    count_ = count;
    dimX_ = dimX;
    dimY_ = dimY;
}

// get variables from other files
void Zombie::getZombie(int count)
{
    count_ = count;
}

void Zombie::getdimX(int dimX)
{
    dimX_ = dimX;
}

void Zombie::getdimY(int dimY)
{
    dimY_ = dimY;
}

// variables for other files
int Zombie::getLife(char obj)
{
    int z = obj - 48;
    return zombie_[z-1][0];
}

int Zombie::getRange(char obj)
{
    int z = obj - 48;
    return zombie_[z-1][2];
}

int Zombie::getAtk(char obj)
{
    int z = obj - 48;
    return zombie_[z-1][1];
}

// randomize zombie attributes
void Zombie::randomAttribute()
{
    zombie_.resize(count_); // for each zombie
    for (int i = 0; i < count_; ++i)
    {
        zombie_[i].resize(3); // life attack range
    }

    for (int i = 0; i < count_; ++i)
    {
        int life[] = {50, 100, 150, 200, 250};
        int atk[] = {5, 10, 15, 20};
        
        zombie_[i][0] = life[rand() % 5];
        zombie_[i][1]= atk[rand() % 4];

        if (dimX_ <= dimY_)
        {
            zombie_[i][2] = 1 + (rand() % (dimX_-1));  // make sure range between 1 and dim-1

        }

        else
        {
            zombie_[i][2] = 1 + (rand() % (dimY_-1));
        }
    }
}

// zombie attributes
void Zombie::attribute()
{
    for (int i = 0; i < count_; ++i)
    {
        cout << "Zombie " << i+1 << ": Life " << zombie_[i][0] << ", Attack " << zombie_[i][1] << ", Range " << zombie_[i][2] << endl;
    }

    cout << endl;
}

void Zombie::updateAttribute(char obj, int atk)
{
    int z = obj - 48;
    if (atk >= zombie_[z-1][0])
    {
        zombie_[z-1][0] = 0;
    }

    else 
    {
        zombie_[z-1][0] = zombie_[z-1][0] - atk;
    }
    
}


