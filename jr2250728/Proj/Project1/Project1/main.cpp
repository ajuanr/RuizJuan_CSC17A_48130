//
//  main.cpp
//  Project1
//
//  Created by Juan Ruiz on 9/26/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <iostream>
#include <cstdlib>

// flag representing a mine
const int MINE = 9;
const int CLEAR = 8;

struct mineFld {
    enum DIFFICULTY {EASY, NORMAL, HARD};
    int **data;
    int rows;
    int cols;
    DIFFICULTY d;   // determenines how many mines
    int nMines;     // number of mines

};

mineFld* create(int, int);
void destroy(mineFld *);
void printFld(mineFld*);
int nMines(mineFld::DIFFICULTY);
void setMines(mineFld *,  mineFld::DIFFICULTY);
void setFlags(mineFld *);
int nAdjacent(mineFld *, int, int);

// functions to walk the perimeter
void mvLeft(mineFld*, int, int &);
void mvRight(mineFld*, int, int &);
void mvUp(mineFld*, int &, int);
void mvDown(mineFld*, int &, int);
void walkPerim(mineFld*, int, int);
/*
int nMines(int =1);
void clearArea(int[][NCOLS], int);
void setMines(int[][NCOLS], int, int =1);
void printClean(int[][NCOLS], int);
// numbers of mines adjacent to a particular spot
int nAdjacent(int [][NCOLS], int, int, int);
void walkPeri(int (*)[NCOLS], int, int, int);
*/
using namespace std;

int main(int argc, const char * argv[]) {

    const int nrows = 9;
    const int ncols = 9;
    //srand(time(0));
    mineFld *mf = create(nrows, ncols);
    setMines(mf, mineFld::DIFFICULTY::EASY);
    setFlags(mf);
    int col = 7;
    int row = 0;
        printFld(mf);
    walkPerim(mf, row, col);
    printFld(mf);
    destroy(mf);
    cout << col << endl;
    // area that will will swpt for mines
    /*
    int field[nrows][NCOLS];
    clearArea(field, nrows);
    setMines(field, nrows);
    
    //printClean(field, nrows);
    for (int i = 0; i != nrows; ++i)
        for(int j = 0; j != NCOLS; ++j)
            if (field[i][j] !=MINE)
            field[i][j] = nAdjacent(field, i, j, nrows);
    printClean(field, nrows);
    walkPeri(field, 3, 4, nrows);
    printClean(field, nrows);
    */
    return 0;
}

// set up the rows*cols minefield
mineFld* create(int rows, int cols) {
    // create a new minefield
    mineFld *out = new mineFld;
    out->rows=rows;
    out->cols = cols;
    out->data = new int*[rows];
    
    for (int row = 0; row != rows; ++row)
        out->data[row] = new int [cols];
    
    for (int i = 0; i != rows; ++i)
        for (int j = 0; j != rows; ++j)
            out->data[i][j] = 0;
    return out;
}

// deallocate memory
void destroy(mineFld *mf) {
    // delete each dynamically allocated row
    for (int i = 0; i != mf->rows; ++i)
        delete[] mf->data[i];
    // delete the dynamically allocated structure
    delete mf;
}


// print the minefield
void printFld(mineFld* m) {
    for (int row = 0; row != m->rows; ++row){
        for (int col = 0; col != m->cols; ++col)
            cout << m->data[row][col] << " ";
        cout << endl;
    }
    cout << endl;
}

// returns the number of mines based on the difficulty
int nMines(mineFld::DIFFICULTY d) {
    if (d==mineFld::DIFFICULTY::EASY) return 10;
    else if (d==mineFld::DIFFICULTY::NORMAL) return 20;
    else if (d==mineFld::DIFFICULTY::HARD) return 35;
    else return 10;
}

// place mines in game area
// higher difficulty = more mines
void setMines(mineFld *mf,  mineFld::DIFFICULTY diff) {
    // holds how many mines will be used
    int mines = nMines(diff);
    // only set mines one per row
    bool set = false;
    while (mines) {
        for (int i = 0; i != mf->rows; ++i) {
            for (int j = 0; j != mf->cols; ++j) {
                // place mines if result of rand() == 0
                if (rand() % 15 == 0){
                    //only place mines if mines are still available
                    // and current position does not have a mines
                    if (mines && !set && mf->data[i][j] == 0) {
                        mf->data[i][j] = 9;
                        --mines;
                        set = true;
                    }
                }
            }
            set = false;
        }
    }
}

int nAdjacent(mineFld *mf, int row, int col) {
    // the number of adjacel
    int nAd=0;
    // not on first or last row or first or last column
    // most of the searhes take place in this area
    if ( row > 0 && col > 0 && row < mf->rows-1 && col < mf->cols-1) {
        // search the 3x3 grid surrounding a cell
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (mf->data[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the first row, not on first or last column
    else if ( row == 0 && col > 0 && col < mf->cols - 1) {
        for (int i = row; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                // 9 is reserved for landmines
                if (mf->data[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the last row, not on first or last column
    else if ( row == mf->rows-1 && col > 0 && col < mf->cols - 1) {
        for (int i = row-1; i <= row; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                // 9 is reserved for landmines
                if (mf->data[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the first column, not on first or last row
    // search to the right
    else if ( col == 0 && row > 0 && row < mf->rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col; j <= col+1; ++j)
                // 9 is reserved for landmines
                if (mf->data[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the last column, not on first or last row
    // search to the left
    else if ( col == mf->cols-1 && row > 0 && row < mf->rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col; ++j)
                // 9 is reserved for landmines
                if (mf->data[i][j] == 9)
                    ++nAd;
        }
    }
    // top left corner
    else if (row == 0 && col == 0) {
        if (mf->data[row][col+1] == 9) ++nAd;
        if (mf->data[row+1][col] == 9) ++nAd;
        if (mf->data[row+1][col+1] == 9) ++nAd;
    }
    // top right corner
    else if (row == 0 && col == mf->cols-1) {
        if (mf->data[row][col-1] == 9) ++nAd;
        if (mf->data[row+1][col] == 9) ++nAd;
        if (mf->data[row+1][col-1] == 9) ++nAd;
    }
    // bottom left corner
    else if (row == mf->rows-1 && col == 0) {
        if (mf->data[row-1][col] == 9) ++nAd;
        if (mf->data[row-1][col+1] == 9) ++nAd;
        if (mf->data[row][col+1] == 9) ++nAd;
    }
    // bottom right corner
    else if (row == mf->rows-1 && col == mf->cols-1) {
        if (mf->data[row-1][col-1] == 9) ++nAd;
        if (mf->data[row-1][col] == 9) ++nAd;
        if (mf->data[row][col-1] == 9) ++nAd;
    }
    // return number of landmines from appropriate if statement
    return nAd;
}

// set the flags for each space siginifying the number of surrounding
// land mines
void setFlags(mineFld *mf) {
    for (int i = 0; i != mf->rows; ++i)
        for (int j = 0; j != mf->cols; ++j)
            // don't look for adjacent landmines in areas where
            // landmine is already located
            if (mf->data[i][j] != 9)
                mf->data[i][j] = nAdjacent(mf, i, j);
}

void walkPerim(mineFld* mf, int row, int col) {
    int rowCpy = row;
    int colCpy = col;
    cout << rowCpy << ", " << colCpy << endl;
    do {
        mvLeft(mf, rowCpy, colCpy);
        cout << rowCpy << ", " << colCpy << endl;
        mvDown(mf, rowCpy, colCpy);
        cout << rowCpy << ", " << colCpy << endl;
        mvUp(mf, rowCpy, colCpy);
        cout << rowCpy << ", " << colCpy << endl;
        mvRight(mf, rowCpy, colCpy);
        cout << rowCpy << ", " << colCpy << endl;
    } while (rowCpy != row && colCpy != col);
    cout << rowCpy << ", " << colCpy << endl;
}

void mvLeft(mineFld *mf, int row, int &col) {
    cout << "Entering left:\n";
    while ( col > 0 &&  mf->data[row][col-1] == 0
           && (mf->data[row-1][col] || row==0)) {
        mf->data[row][col--] = CLEAR;
    }
    if (mf->data[row][col] == 0)
        mf->data[row][col] = CLEAR;
}

void mvRight(mineFld *mf, int row, int &col) {
    cout << "Entering right:\n";
    while ( col < mf->cols-1&& mf->data[row][col+1] == 0 &&
           (mf->data[row+1][col] || row == mf->rows-1) ){
        cout << col << endl;
        mf->data[row][col++] = CLEAR;
    }
    if (mf->data[row][col] == 0)
        mf->data[row][col] = CLEAR;
}

void mvUp(mineFld *mf, int &row, int col) {
    cout << "Entering up: " << endl;
    while ( row > 0 &&  mf->data[row-1][col] == 0 &&
           (mf->data[row][col+1] || row == mf->cols-1)) {
        mf->data[row--][col] = CLEAR;
    }
    if (mf->data[row][col] == 0)
        mf->data[row][col] = CLEAR;
}

void mvDown(mineFld *mf, int &row, int col) {
    cout << "Entering down\n";
    cout << col << endl;
    while ( row < mf->rows && mf->data[row+1][col] == 0 &&
           (mf->data[row][col-1] || col == 0 )) {
        mf->data[row++][col] = CLEAR;
        
    }
    if (mf->data[row][col] == 0)
        mf->data[row][col] = CLEAR;

}

/*
// returns the number of mines based on the difficulty
int nMines(int n) {
    if (n==1) return 9;
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
                if (rand() % 15 == 0){
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


// return the numbers of adjacent landmines to
// a given cell;
int nAdjacent(int a[][NCOLS], int row, int col, int rows) {
    // the number of adjacel
    int nAd=0;
    // not on first or last row or first or last column
    // most of the searhes take place in this area
    if ( row > 0 && col > 0 && row < rows-1 && col < NCOLS-1) {
        // search the 3x3 grid surrounding a cell
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (a[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the first row, not on first or last column
    else if ( row == 0 && col > 0 && col < NCOLS - 1) {
        for (int i = row; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                // 9 is reserved for landmines
                if (a[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the last row, not on first or last column
    else if ( row == rows-1 && col > 0 && col < NCOLS - 1) {
        for (int i = row-1; i <= row; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                // 9 is reserved for landmines
                if (a[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the first column, not on first or last row
    // search to the right
    else if ( col == 0 && row > 0 && row < rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col; j <= col+1; ++j)
                // 9 is reserved for landmines
                if (a[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the last column, not on first or last row
    // search to the left
    else if ( col == NCOLS-1 && row > 0 && row < rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col; ++j)
                // 9 is reserved for landmines
                if (a[i][j] == 9)
                    ++nAd;
        }
    }
    // top left corner
    else if (row == 0 && col == 0) {
        if (a[row][col+1] == 9) ++nAd;
        if (a[row+1][col] == 9) ++nAd;
        if (a[row+1][col+1] == 9) ++nAd;
    }
    // top right corner
    else if (row == 0 && col == NCOLS-1) {
        if (a[row][col-1] == 9) ++nAd;
        if (a[row+1][col] == 9) ++nAd;
        if (a[row+1][col-1] == 9) ++nAd;
    }
    // bottom left corner
    else if (row == rows-1 && col == 0) {
        if (a[row-1][col] == 9) ++nAd;
        if (a[row-1][col+1] == 9) ++nAd;
        if (a[row][col+1] == 9) ++nAd;
    }
    // bottom right corner
    else if (row == rows-1 && col == NCOLS-1) {
        if (a[row-1][col-1] == 9) ++nAd;
        if (a[row-1][col] == 9) ++nAd;
        if (a[row][col-1] == 9) ++nAd;
    }
    // return number of landmines from appropriate if statement
    return nAd;
}

// if users selects an area that is completely clear of mines
// clear that entire area
void walkPeri(int (*a)[NCOLS], int row, int col, int rows) {
    int i = row;
    int j = col;
        // try to move left
    do {
        if (row > 0) {
            while (a[i][j-1]==0 && i>0) {
                --j;
                a[i][j] = 7;}
        }
        // try to move right
        else if (row < rows) {
            while (a[i][j+1]==0 && j<rows) {
                ++j;
                a[i][j] = 7;}
            }
            // moving up
        else if (col > 0) {
                while (a[i-1][j]==0 && i>0) {
                    --i;
                    a[i][j] = 7;}
                }
        // moving to down
        else {
            while (a[i+1][j]==0 && i<rows) {
                ++j;
                a[i][j] = 7;
            }
        
        }
    } while (i != row && j != col);
}
*/