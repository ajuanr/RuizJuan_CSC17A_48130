//
//  main.cpp
//  Project1
//
//  Created by Juan Ruiz on 9/26/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <iostream>

// numbers of column for board
const int NCOLS = 9;

int nMines(int =1);
void clearArea(int[][NCOLS], int);
void setMines(int[][NCOLS], int, int =1);
void printClean(int[][NCOLS], int);
// numbers of mines adjacent to a particular spot
int nAdjacent(int [][NCOLS], int);

using namespace std;

int main(int argc, const char * argv[]) {

    const int nrows = 9;
    // area that will will swpt for mines
    int field[nrows][NCOLS];
    clearArea(field, nrows);
    setMines(field, nrows);
    printClean(field, nrows);
    
    return 0;
}

// returns the number of mines based on the difficulty
int nMines(int n) {
    if (n==1) return 10;
    else if (n==2) return 20;
    else if (n==3) return 35;
    else return 10;
}

// place mines in game area
// higher difficulty = more mines
void setMines(int f[][NCOLS], int size, int diff) {
    // holds how many mines will be used
    int mines = nMines(diff);
    // only set mines one per row
    bool set = false;
    while (mines) {
        for (int i = 0; i != size; ++i) {
            for (int j = 0; j != NCOLS; ++j) {
                // place mines if result of rand() == 0
                if (rand() % 10 == 0){
                    //only place mines if mines are still available
                    // and current position does not have a mines
                    if (mines && !set && f[i][j] == 0) {
                        f[i][j] = 9;
                        --mines;
                        set = true;
                    }
                }
                
            }
            set = false;
        }
    }
}

void clearArea(int f[][NCOLS], int size) {
    for (int i = 0; i != size; ++i) {
        for (int j = 0; j != NCOLS; ++j) {
            f[i][j] = 0;
        }
    }
}

// used to ensure area is set up properly
// not as part of the game
void printClean(int f[][NCOLS], int size) {
    for (int i = 0; i != size; ++i) {
        for (int j = 0; j != NCOLS; ++j) {
            cout << f[i][j] << " ";
        }
        cout << endl;
    }
}