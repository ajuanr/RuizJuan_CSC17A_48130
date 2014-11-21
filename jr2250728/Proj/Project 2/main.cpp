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
#include <fstream>
#include <string>
#include <iomanip>
#include "Minesweeper.h"

/***************************************************
 *
 *                  Structure
 *
 **************************************************/


using namespace std;



/***************************************************
 *
 *                      Main
 *
 **************************************************/
int main(int argc, const char * argv[]) {
    /// Get the user name
    char *player = userName();
    /// ask user if they want to play
    cout << "Hello " << player
         << ", Would you like to play a game of minesweeper?\n"
            "Hit 'y' if yes\n";
    char ans;
    cin >> ans;
    
    if (ans == 'y') {
        /// create minefield variables
        short nrows;
        MineField::Difficulty d;
        /// Get game information from user
        prompt(nrows, d);
        /// Check that data is valid before creating the array
        /// that holds the results of previous games
        if (isValidIn(nrows, nrows, d)) {
            while (ans == 'y' && isValidIn(nrows, nrows, d)) {
                playGame(nrows, nrows, d, player);
                cout << endl;
                cout << "Would you like to play again " << player << "? ";
                cin >> ans;
                cout << endl;
                /// Get new data only if user wants to continue
                if (ans =='y')
                    prompt(nrows, d);
            }
        }
        /// User information was invalid
        else
            cout << "Minefield too small. Goodbye: ";
    }
    cout << "Game is Over.\n";
    
    /// Cleanup
    delete player;
    
    readBin("result");
    
    cout << "Would you like to see some empty minefields "
            "stored in a structure?\n"
            "Hit 'y' for yes: ";
    cin >> ans;
    if (ans == 'y')
        fields();
    
    cout << endl;
    cout << "Goodbye\n";

    return 0;
}

