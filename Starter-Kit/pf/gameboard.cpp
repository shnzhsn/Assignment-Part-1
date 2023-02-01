#include "gameboard.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime> // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
using namespace std;

// initialize
Board::Board(int dimX, int dimY, int zombie)
{
    create(dimX, dimY, zombie);
}

// change game settings
void Board::settings()
{
    int x, y, z;
    cout << "Change Game Settings " << endl;
    cout << "------------------------------" << endl;
    cout << "Odd Number Rows & Columns Only" << endl << endl;

    // checks for odd numbers
    while (true)
    {
        cout << "Enter Rows         => ";
        cin >> x;
        if (x % 2 == 0)
        {
            cout << endl << "Please Enter Odd Number Only" << endl;
            continue;
        }
        else
        {
            break;
        }
    }
    
    while (true)
    {
        cout << "Enter Columns      => ";
        cin >> y;
        if (y % 2 == 0)
        {
            cout << endl <<"Please Enter Odd Number Only" << endl;
            continue;
        }
        else
        {
            break;
        }
    }

    cout << "Enter Zombie Count => ";
    cin >> z;
    create(x, y, z);
    cout << endl << "Settings Updated" << endl;;
    pf::Pause();
    pf::ClearScreen();
    display();
}

// display game settings | initial game screen
void Board::displaySettings()
{   
    char change;
    cout << "Default Game Settings" << endl;
    cout << "---------------------" << endl;
    cout << "Board Rows    : " << dimY_ << endl;
    cout << "Board Columns : " << dimX_ << endl;
    cout << "Zombie Count  : " << zombie_ << endl << endl;

    while(change != 'y' && change != 'n')
    {
        cout << "Change game settings? (y/n) => ";
        cin >> change;
        change = tolower(change);

        if (change == 'y')
        {
            pf::ClearScreen();
            settings();
            break;
        }

        else if (change == 'n')
        {
            pf::ClearScreen();
            display();
            break;
        }

        else
        {
            cout << "Invalid Input. Please try again" << endl << endl;
        }

        
    }
    
}

void Board::setObject(int x, int y, char ch)
{
    map_[y][x] = ch;
}

char Board::getObject(int x, int y) const
{
    return map_[y][x];
}

// creates gameboard
void Board::create(int dimX, int dimY, int zombie)
{
    dimX_ = dimX;
    dimY_ = dimY;
    zombie_ = zombie;
    char objects[] = {' ', ' ', ' ', 'r', 'p', 'h', '>', '<', '^', 'v'};
    int noOfObjects = 10; // number of objects in the objects array

    // create vector
    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }

    // put random characters onto board
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }

    // put zombie onto board randomly
    for (int i = 0; i < zombie_; ++i)
    {
        char z = '1'+i;
        int y = rand() % dimY_;
        int x = rand() % dimX_;
        map_[y][x] = z;
    }

    // starting position for alien
    char alien = 'A';
    alienX_ = (dimX_ / 2);
    alienY_ = (dimY_ / 2);
    map_[alienY_][alienX_] = alien;
}

// to display board
void Board::display() const
{
    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << "  ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        // display row number
        cout << setw(2) << (i + 1);

        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }

    // display lower border of the last row
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    // display column number
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl << endl;
}

// for other files
int Board::getZombie() const
{
return zombie_;
}

int Board::getDimX() const
{
    return dimX_;
}

int Board::getDimY() const
{
    return dimY_;
}

char Board::getObj() const
{
    return object_;
}

char Board::gettempObj() const
{
    return tempObj_;
}

// texts for objects found
void Board::outputObj()
{
    switch(object_)
    {
        case ' ':
            cout << "Alien finds nothing" << endl << endl;
            break;

        case 'r':
        {
            cout << "Path is obstructed by a rock" << endl;;
            char objects[] = {' ', ' ', ' ', 'p', 'h', '>', '<', '^', 'v'};
            object_ = objects[rand() % 9];
            switch(object_)
            {
                case ' ':
                    cout << "Alien finds nothing under rock" << endl << endl;
                    break;
                case 'p':
                    cout << "Alien discovered a pod under rock" << endl << endl;
                    break;
                case 'h':
                    cout << "Alien finds health pack under rock" << endl << endl;
                    break;
                case '>':
                case '<':
                case '^':
                case 'v':
                    cout << "Alien finds an arrow under rock" << endl << endl;
                    break;
            }
            break;
        }

        case 'p':
            cout << "Alien discovered a pod" << endl << endl;
            break;

        case 'h':
            cout << "Alien finds health pack" << endl;
            cout << "+20 Life" << endl << endl;
            break;

        case '>':
        case '<':
        case '^':
        case 'v':
            cout << "Alien finds an arrow" << endl << "+20 Attack" << endl << endl;
            break;

    }
}

void Board::moveAlien(string command, int count)
{
    firstChar_ = command[0];
    int newAlienY = alienY_;
    int newAlienX = alienX_;
    tempObj_ = 't';  // initializer
    switch(firstChar_)  // to set new position
    {
        case 'u':
            newAlienY = alienY_ - count;
            break;

        case 'd':
            newAlienY = alienY_ + count;
            break;

        case 'l':
            newAlienX = alienX_ - count;
            break;
        
        case 'r':
            newAlienX = alienX_ + count;
            break;
    }

    switch(firstChar_)  // to check if out of bound
    {
        case 'u':
        case 'd':
            if (newAlienY >= dimY_ || newAlienY < 0)
            {
                cout << "Alien hits border" << endl << endl;
                tempObj_ = 's';
                exit(0);
            }
            break;


        case 'l':
        case 'r':
            if (newAlienX >= dimX_ || newAlienX < 0)
            {
                cout << "Alien hits border" << endl << endl;
                tempObj_ = 's';
                exit(0);
            }
            break;
    }

    object_ = getObject(newAlienX, newAlienY);
    if (object_ == 'r')
    {
        outputObj();
        tempObj_ = 'r';
        setObject(newAlienX, newAlienY, object_);
    }

    else
    {
        outputObj();
        setObject(newAlienX, newAlienY, 'A');
        switch(firstChar_)
        {
            case 'u':
                setObject(newAlienX, newAlienY+1, '.');
                break;
            case 'r':
                setObject(newAlienX-1, newAlienY, '.');
                break;
            case 'd':
                setObject(newAlienX, newAlienY-1, '.');
                break;
            case 'l':
                setObject(newAlienX+1, newAlienY, '.');
                break;
        }     
    }

    pf::Pause();
    pf::ClearScreen();
    display();
}