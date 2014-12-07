/*
 * Ruiz, Juan - Project 1 - 48130
 *
 * Project allows user to play Minesweeper
 * 
 * Structures
 *      Functions with structure input: Most of the functions
 *      Functions returning structures: Function create()      Line 235
 *      Function with array of structures: Function fields()   Line 584
 *
 * Memory allocation:
 *      dynamic 2D array in function create()                  Line 242
 *      dynamic 1D array in function userName()                Line 225
 *
 * Binary Files
 *      Writing to: function writeBin()                        Line 553
 *      Reading from: function readBin()                       Line 562
 * Strings
 *      Function:
 *          writeBin(), readBin(), userName()               Line 553, 562, 220
 *
 * Pointers
 *      Structure passed as pointer in most functions
 *      2D array pointer notation in prntClear()               Line 288, 290
 *      1D array pointer notation in userName()                 Line 227, 229
 *      Returning pointer in create()                           Line 235
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Minesweeper.h"
#include "TemplateClass.h"

using namespace std;



/***************************************************
 *
 *                      Main
 *
 **************************************************/
int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(time(0)));
    AnyGame<GameBoard> m(new Minesweeper(10,10));
    
    //m->setUp();
    /// create GameBoard with max size
    /// the entire board may not be utilized
    GameBoard *mSweep = new  Minesweeper(10,10);

    try {
        m->setUp();
    //mSweep->setUp();
    }
    
    catch (Minesweeper::badSize) {
        cout << "Size was invalid\n";
    }
    
    //mSweep->loadGame();
    
    mSweep->print();
    
    //delete mSweep;
    
    return 0;
}

