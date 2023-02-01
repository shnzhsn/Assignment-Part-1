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
#include "pf/alien.hpp"
#include "pf/zombie.hpp"
#include <iostream>
using namespace std;

// main function
int main()
{
    // pre game functions
    srand(time(NULL));
    Board board;
    Alien alien;
    Zombie zombie;
    pf::ClearScreen();

    board.displaySettings();
    zombie.getZombie(board.getZombie());  //pre game functions
    zombie.getdimX(board.getDimX());
    zombie.getdimY(board.getDimY()); 


    alien.attribute();
    zombie.attribute();
    alien.command();
    
    do {
        int i = 1;
        do {
            board.moveAlien(alien.getCommand(), i);
            alien.updateAttribute(board.getObj());
            alien.attribute();
            zombie.attribute();

            ++i;
        }
        while(board.gettempObj() != 'r' && board.gettempObj() != 's');
    }
    while(board.gettempObj() != 's');

}