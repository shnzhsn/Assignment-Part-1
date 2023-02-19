// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT5L 
// Names: SHAHNAZ BINTI HUSAIN SUKRI
// IDs: 1211101888
// Emails: 1211101888@STUDENT.MMU.EDU.MY
// Phones: +60177320297
// ********************************************************* 

#include "pf/helper.h"
#include "pf/gameboard.hpp"
#include "pf/characters.hpp"
#include <iostream>
using namespace std;

// main function
int main()
{
    srand(time(NULL));
    // pre game functions
    Board board;
    Alien alien;
    Zombie zombie;
    pf::ClearScreen();

    // default or choice settings
    board.displaySettings();

    // for zombie attributes
    zombie.getZombie(board.getNum('z'));  
    zombie.getdimX(board.getNum('x'));
    zombie.getdimY(board.getNum('y'));
    zombie.randomAttribute();

    // actual game
    int lifeZ;
    do {
        board.display();
        alien.attribute();
        zombie.attribute();
        alien.command();
        string command = alien.getCommand();

        // if command is arrow
        if (command == "arrow")
        {
            board.switchArrow();
            pf::ClearScreen();
            continue;
        }

        while(true)
        {
            board.moveAlien(command);
            char object = board.getChar('o');

            alien.updateAttribute(object, 0);
            alien.attribute();
            zombie.attribute();

            switch(object)
           {
                case '>':
                    command = "right";
                    break;
                case '<':
                    command = "left";
                    break;
                case '^':
                    command = "up";
                    break;
                case 'v':
                    command = "down";
                    break;
           }      

            // if rock or to stop turn
            if (board.getChar('t') == 'r' || board.getChar('t') == 's')
            {
                alien.updateAttribute(board.getChar('t'), 0);
                break;
            }
            
            // if found zombie
            else if (isdigit(board.getChar('t')))
            {
                int atk = alien.getAtk();
                cout << "Zombie " << board.getChar('t') << " recieves +" << atk << " DMG" << endl;

                zombie.updateAttribute(board.getChar('t'), atk);
                alien.updateAttribute('n', 0);

                pf::Pause();
                pf::ClearScreen();
                board.display();
                alien.attribute();
                zombie.attribute();
                pf::Pause();

                int life = zombie.getLife(board.getChar('t'));
                if (life == 0)
                {
                    int x = 0, y =0;
                    board.findObject(board.getChar('t'), x, y);
                    board.setObject(x, y, ' ');
                }
                break;
            }

            // if found pod
            else if (isdigit(board.getChar('o')))
            {
                zombie.updateAttribute(board.getChar('o'), 10);
                pf::ClearScreen();
                board.display();
                alien.attribute();
                zombie.attribute();
            }

            else
                continue;
        }

        // zombies turn
        board.resetTrail();
        pf::ClearScreen();
        for(int i = 0; i < board.getNum('z'); ++i)
        {
            char z = '1' + i;
            if (zombie.getLife(z) != 0)
            {
                board.moveZombie(z, zombie.getRange(z), zombie.getAtk(z));
                if (board.getChar('t') == 'z')
                {
                    alien.updateAttribute('z', zombie.getAtk(z));
                }

            }

            else
                continue;
            
        }

        //  to check zombies left
        lifeZ = 1;
        for(int i = 0; i < board.getNum('z'); ++i)
        {
            char j = '1' + i;
            int z = zombie.getLife(j);
            if (z == 0)
            {
                lifeZ = lifeZ * 1;
            }

            else
            {
                lifeZ = lifeZ * 0;
            }

        }

    } while(alien.getLife() != 0 && lifeZ != 1);

    // end game functions
    board.display();
    alien.attribute();
    zombie.attribute();

    if (alien.getLife() != 0)
        cout << "All Zombies Defeated. You Win!" << endl;

    else
        cout << "Aw.. What a shame. You Lost!" << endl;

    char choice;
    while(choice != 'y' && choice != 'n')
    {
        cout << "Play Again? (y/n) => ";
        cin >> choice;
        choice = tolower(choice);

        if (choice == 'y')
        {
            pf::ClearScreen();
            main();
            break;
        }

        else if (choice == 'n')
        {
            pf::ClearScreen();
            cout << "Thanks for Playing!";
            exit(0);
        }

        else
        {
            cout << "Invalid Input. Please try again" << endl << endl;
        }
    }
}