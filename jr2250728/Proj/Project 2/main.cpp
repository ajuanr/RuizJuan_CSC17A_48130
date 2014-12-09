/*
 * Ruiz, Juan - Project 1 - 48130
 *
 * Project allows user to play Minesweeper
 * 
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
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
    
    try {
        m->setUp();
    }
    
    catch (Minesweeper::badSize) {
        cout << "Size was invalid\n";
    }
    catch (const char* s) {
        cout << s << endl;
    }
    
    return 0;
}

