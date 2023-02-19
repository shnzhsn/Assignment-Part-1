#include "gameboard.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <ctype.h>
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
    cout << "Odd Number Rows & Columns Only" << endl;
    cout << "Less than 10 Zombies Only" << endl
         << endl;

    // checks for odd numbers
    while (true)
    {
        cout << "Enter Rows         => ";
        cin >> y;
        if (y % 2 == 0)
        {
            cout << endl
                 << "Please Enter Odd Number Only" << endl;
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
        cin >> x;
        if (x % 2 == 0)
        {
            cout << endl
                 << "Please Enter Odd Number Only" << endl
                 << endl;
            continue;
        }
        else
        {
            break;
        }
    }

    // checks zombie <10
    while (true)
    {
        cout << "Enter Zombie Count => ";
        cin >> z;
        if (z > 9)
        {
            cout << endl
                 << "Please Enter <10 Only" << endl
                 << endl;
            continue;
        }
        else
        {
            break;
        }
    }

    create(x, y, z);
    cout << endl
         << "Settings Updated" << endl;
    ;
    pf::Pause();
    pf::ClearScreen();
}

// display game settings | initial game screen
void Board::displaySettings()
{
    char change;
    cout << "Default Game Settings" << endl;
    cout << "---------------------" << endl;
    cout << "Board Rows    : " << dimY_ << endl;
    cout << "Board Columns : " << dimX_ << endl;
    cout << "Zombie Count  : " << zombie_ << endl
         << endl;

    while (change != 'y' && change != 'n')
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
            break;
        }

        else
        {
            cout << "Invalid Input. Please try again" << endl
                 << endl;
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
        while (true)
        {
            char z = '1' + i;
            int y = rand() % dimY_;
            int x = rand() % dimX_;
            if ((y == dimY_ / 2) && (x == dimX_ / 2) || isdigit(getObject(x, y))) // avoid Alien position and other zombies
            {
                continue;
            }

            else
            {
                map_[y][x] = z;
                break;
            }
        }
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
    cout << endl
         << endl;
}

// for other files
int Board::getNum(char item) const
{
    switch (item)
    {
    case 'x':
        return dimX_;
        break;

    case 'y':
        return dimY_;
        break;

    case 'z':
        return zombie_;
        break;
    default:
        return 0;
    }
}

char Board::getChar(char item) const
{
    switch (item)
    {
    case 'o':
        return object_;
        break;

    case 't':
        return tempObj_;
        break;

    default:
        return 0;
    }
}

void Board::findObject(char object, int &x, int &y)
{
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            if (map_[i][j] == object)
            {
                x = j;
                y = i;
            }
        }
    }
}

void Board::resetTrail()
{
    char trail = '.';
    int x = -1, y = -1;

    while (true)
    {
        findObject(trail, x, y);
        if (x == -1 || y == -1)
        {
            break;
        }

        else
        {
            char objects[] = {' ', ' ', ' ', 'r', 'p', 'h', '>', '<', '^', 'v'};
            int objNo = rand() % 10;
            setObject(x, y, objects[objNo]);
            x = -1, y = -1;
        }
    }
}

// change arrows
void Board::switchArrow()
{
    int x, y;
    char arrow;

    cout << "Enter X Y Coordinate of Arrow" << endl;
    cin >> x >> y;
    x = x - 1;
    y = y - 1;
    if ((x >= dimX_ || x < 0 || y >= dimY_ || y < 0) || (getObject(x, y) != '>' && getObject(x, y) != '<' && getObject(x, y) != 'v' && getObject(x, y) != '^'))
    {
        cout << "Invalid Coordinate" << endl
             << endl;
        switchArrow();
    }

    else
    {
        while (true)
        {
            cout << endl
                 << "Enter New Arrow" << endl;
            cin >> arrow;
            if (arrow != '>' && arrow != '<' && arrow != '^' && arrow != 'v')
            {
                cout << "Invalid Character" << endl;
                continue;
            }

            else
                break;
        }

        setObject(x, y, arrow);
    }
}

void Board::podAtk(int x, int y)
{
    
    int temp = INT_MAX;
    char z = '1';
    for (int i = 0; i < zombie_; ++i)
    {
        z = z + i;
        int x2 = -1, y2 = -1;
        findObject(z, x2, y2);

        int index = abs(x - x2) + abs(y - y2);

        if (index <= temp)
        {
            temp = index;
            object_ = z;
        }

        else
            continue;
    }

    cout << "Zombie " << object_ << " receives +10 DMG" << endl;
}

// texts for objects found
void Board::outputObj()
{
    switch (object_)
    {
    case ' ':
        cout << "Alien finds nothing" << endl
             << endl;
        break;

    case 'r':
    {
        cout << "Path is obstructed by a rock" << endl;
        ;
        char objects[] = {' ', ' ', ' ', 'p', 'h', '>', '<', '^', 'v'};
        object_ = objects[rand() % 9];
        switch (object_)
        {
        case ' ':
            cout << "Alien finds nothing under rock" << endl
                 << endl;
            break;
        case 'p':
            cout << "Alien discovered a pod under rock" << endl
                 << endl;
            break;
        case 'h':
            cout << "Alien finds health pack under rock" << endl
                 << endl;
            break;
        case '>':
        case '<':
        case '^':
        case 'v':
            cout << "Alien finds an arrow under rock" << endl
                 << endl;
            break;
        }
        break;
    }

    case 'p':
        cout << "Alien discovered a pod" << endl;
        break;

    case 'h':
        cout << "Alien finds health pack" << endl;
        cout << "+20 Life" << endl
             << endl;
        break;

    case '>':
    case '<':
    case '^':
    case 'v':
        cout << "Alien finds an arrow" << endl
             << "+20 Attack" << endl
             << endl;
        break;
    }
}

void Board::moveAlien(string command)
{
    firstChar_ = command[0];
    int tempAlienY = alienY_;
    int tempAlienX = alienX_;
    tempObj_ = ' ';     // initializer
    switch (firstChar_) // to set new position
    {
    case 'u':
        alienY_ = tempAlienY - 1;
        break;

    case 'd':
        alienY_ = tempAlienY + 1;
        break;

    case 'l':
        alienX_ = tempAlienX - 1;
        break;

    case 'r':
        alienX_ = tempAlienX + 1;
        break;
    }

    switch (firstChar_) // to check if out of bound
    {
    case 'u':
    case 'd':
        if (alienY_ >= dimY_ || alienY_ < 0)
        {
            cout << "Alien hits border" << endl;
            cout << "Alien's turn ends" << endl
                 << endl;
            tempObj_ = 's';
        }
        break;

    case 'l':
    case 'r':
        if (alienX_ >= dimX_ || alienX_ < 0)
        {
            cout << "Alien hits border" << endl;
            cout << "Alien's turn ends" << endl
                 << endl;
            tempObj_ = 's';
        }
        break;
    }

    // if not out of bounds
    if (tempObj_ != 's')
    {
        object_ = getObject(alienX_, alienY_);
        // if finds rock
        if (object_ == 'r')
        {
            outputObj();
            tempObj_ = 'r';
            setObject(alienX_, alienY_, object_);
            alienX_ = tempAlienX; // set to previous position
            alienY_ = tempAlienY;
            cout << "Alien's turn ends" << endl;
        }

        // if finds zombie
        else if (isdigit(object_))
        {
            cout << "Alien has encounterd Zombie " << object_ << endl;
            tempObj_ = object_;
            object_ = 'x';
            alienX_ = tempAlienX;
            alienY_ = tempAlienY;
        }

        // if anything else
        else
        {
            outputObj();
            setObject(alienX_, alienY_, 'A');
            setObject(tempAlienX, tempAlienY, '.');

            if (object_ == 'p')
            {
                podAtk(alienX_, alienY_);
            }
        }
    }

    else // set to previous position
    {
        object_ = 's';
        alienX_ = tempAlienX;
        alienY_ = tempAlienY;
    }

    pf::Pause();
    pf::ClearScreen();
    display();
}

void Board::moveZombie(char count, int range, int atk)
{
    int x, y;
    char move = ' ';
    while (true)
    {
        x = -1, y = -1;
        char direction[] = {'l', 'r', 'u', 'd'};
        move = direction[rand() % 4];

        findObject(count, x, y);
        int tempX = x;
        int tempY = y;
        setObject(x, y, ' ');
        switch (move)
        {
        case 'l':
            x = x - 1;
            break;
        case 'r':
            x = x + 1;
            break;
        case 'u':
            y = y - 1;
            break;
        case 'd':
            y = y + 1;
            break;
        }

        if ((x >= dimX_ || x < 0 || y >= dimY_ || y < 0) || getObject(x, y) == 'A' || isdigit(getObject(x, y)))
        {
            setObject(tempX, tempY, count);
            continue;
        }

        else
        {
            setObject(x, y, count);
            break;
        }
    }



    display();

    switch (move)
    {
    case 'l':
        cout << "Zombie " << count << " moved left" << endl;
        break;
    case 'r':
        cout << "Zombie " << count << " moved right" << endl;
        break;
    case 'u':
        cout << "Zombie " << count << " moved up" << endl;
        break;
    case 'd':
        cout << "Zombie " << count << " moved down" << endl;
        break;
    }

    // checks if alien in range
    int x2 = -1, y2 = -1;
    findObject('A', x2, y2);

    int index = abs(x-x2) + abs(y-y2);

    if (index <= range)
    {
        tempObj_ = 'z';
        cout << "Alien recieves +" << atk << " DMG" << endl;        
    }

    else 
    {
        cout << "Alien not in range" << endl;
    }

    pf::Pause();
    pf::ClearScreen();

}


