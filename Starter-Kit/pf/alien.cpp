#include "alien.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

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

void Alien::updateAttribute(char obj)
{
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
    }
}