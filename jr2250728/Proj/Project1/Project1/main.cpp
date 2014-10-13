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
// flag representing a spot that has been cleared
const int CLEAR = 8;

enum DIFFICULTY {EASY, NORMAL, HARD};

struct MineField {
    enum DIFFICULTY {EASY, NORMAL, HARD};
    int **data;
    int rows;
    int cols;
    DIFFICULTY d;   // determenines how many mines
    int nMines;     // number of mines

};

MineField* create(int, int);
void destroy(MineField *);
void printFld(MineField*);
int nMines(MineField::DIFFICULTY);
void setMines(MineField *,  MineField::DIFFICULTY);
void setFlags(MineField *);
int mAdjacent(MineField *, int, int);
bool isClear(MineField *, int, int);
void clrArea(MineField *, int, int);

void showZeros(MineField *, int, int);

void setUpGame();
void prompt(int&, int&);

// functions to walk the perimeter
void mvLeft(MineField*, int, int &);
void mvRight(MineField*, int, int &);
void mvUp(MineField*, int &, int);
void mvDown(MineField*, int &, int);
void walkPerim(MineField*, int, int);
/*
int nMines(int =1);
void clearArea(int[][NCOLS], int);
void setMines(int[][NCOLS], int, int =1);
void printClean(int[][NCOLS], int);
// numbers of mines adjacent to a particular spot
int mAdjacent(int [][NCOLS], int, int, int);
void walkPeri(int (*)[NCOLS], int, int, int);
*/
using namespace std;

int main(int argc, const char * argv[]) {
    setUpGame();
    
    // area that will will swept for mines
    /*
    int field[nrows][NCOLS];
    clearArea(field, nrows);
    setMines(field, nrows);
    
    //printClean(field, nrows);
    for (int i = 0; i != nrows; ++i)
        for(int j = 0; j != NCOLS; ++j)
            if (field[i][j] !=MINE)
            field[i][j] = mAdjacent(field, i, j, nrows);
    printClean(field, nrows);
    walkPeri(field, 3, 4, nrows);
    printClean(field, nrows);
    */
    return 0;
}

void setUpGame() {
    const int nrows = 10;
    const int ncols = 10;
    //srand(time(0));
    MineField *mf = create(nrows, ncols);
    setMines(mf, MineField::EASY);
    setFlags(mf);
    int row = 0;
    int col = 4;
    if( !isClear(mf, row,col)) {
        if (mf->data[row][col] == MINE)
            cout << "You Lose\n";
        else
            cout << mf->data[row][col] ;
    }
    else
        showZeros(mf, row, col);
    showZeros(mf, row, col);
    printFld(mf);

    destroy(mf);                // deallocate
}

// set up the rows*cols minefield
MineField* create(int rows, int cols) {
    // create a new minefield
    MineField *out = new MineField;
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
void destroy(MineField *mf) {
    // delete each dynamically allocated row
    for (int i = 0; i != mf->rows; ++i)
        delete[] mf->data[i];
    // delete the dynamically allocated structure
    delete mf;
}


// print the minefield
void printFld(MineField* m) {
    for (int row = 0; row != m->rows; ++row){
        for (int col = 0; col != m->cols; ++col)
            cout << m->data[row][col] << " ";
        cout << endl;
    }
    cout << endl;
}

// returns the number of mines to set based on the difficulty
int nMines(MineField::DIFFICULTY d) {
    if (d==MineField::EASY) return 10;
    else if (d==MineField::NORMAL) return 20;
    else if (d==MineField::HARD) return 35;
    else return 10;
}

// place mines in game area
// higher difficulty = more mines
void setMines(MineField *mf,  MineField::DIFFICULTY diff) {
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

// returns how many mines surrounding a given square
int mAdjacent(MineField *mf, int row, int col) {
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
                // 9 is reserved for mines
                if (mf->data[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the last row, not on first or last column
    else if ( row == mf->rows-1 && col > 0 && col < mf->cols - 1) {
        for (int i = row-1; i <= row; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                // 9 is reserved for mines
                if (mf->data[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the first column, not on first or last row
    // search to the right
    else if ( col == 0 && row > 0 && row < mf->rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col; j <= col+1; ++j)
                // 9 is reserved for mines
                if (mf->data[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the last column, not on first or last row
    // search to the left
    else if ( col == mf->cols-1 && row > 0 && row < mf->rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col; ++j)
                // 9 is reserved for mines
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
    // return number of mines from appropriate if statement
    return nAd;
}

// if there are no mines surrounding a square it is clear
bool isClear(MineField * mf, int row, int col) {
    if (mAdjacent(mf, row, col)) 
        return false;            // there was at least one mine adjacent
    return true;                 // area was clear
}

void showZeros(MineField *mf, int row, int col) {
    const int CLEAR = 8;
    // check bounds
    if ( row >= mf->rows || row < 0 || col >= mf->cols || col < 0)
        return;
        if (isClear(mf, row, col) && mf->data[row][col] != CLEAR){
            mf->data[row][col] = CLEAR;
            showZeros(mf, row+1, col); // go up one row
            showZeros(mf, row-1, col); // go down one row
            showZeros(mf, row, col+1); // go right one col
            showZeros(mf, row, col-1); // go left one col
        }
        // space was not clear or already shown
        else
            return;
}

// set the flag for each space signifying the number of adjacent
// land mines
void setFlags(MineField *mf) {
    for (int i = 0; i != mf->rows; ++i)
        for (int j = 0; j != mf->cols; ++j)
            // don't look for adjacent mines in areas where
            // mine is already located
            if (mf->data[i][j] != 9)
                mf->data[i][j] = mAdjacent(mf, i, j);
}


void clrArea(MineField *mf, int row, int col) {
    // use to create a (down-up)*(right-left) grid
    // in which to clear an area
    int up=row, down=row, left=col, right=col;
    /*
    cout << "Up: " << up << "\nDown: " << down
    << "\nLeft: " << left << "\nRight: " << right
    << endl << endl;
    */
    // check up
    while (up > 0 && mf->data[up-1][col] == 0) {
        --up;
    }
    
    // check down
    while (down < mf->rows-1 && mf->data[down+1][col] == 0) {
        ++down;
    }
    
    // check to the left
    while ( left > 0 && mf->data[row][left-1] == 0) {
        --left;
    }
    // check to the right
    while ( right < mf->cols-1 && mf->data[row][right+1] == 0) {
        ++right;
    }
    
    cout << "Up: " << up << "\nDown: " << down
    << "\nLeft: " << left << "\nRight: " << right
    << endl;
}

/*
void walkPerim(MineField* mf, int row, int col) {
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

void mvLeft(MineField *mf, int row, int &col) {
    cout << "Entering left:\n";
    while ( col > 0 &&  mf->data[row][col-1] == 0
           && (mf->data[row-1][col] || row==0)) {
        mf->data[row][col--] = CLEAR;
    }
    if (mf->data[row][col] == 0)
        mf->data[row][col] = CLEAR;
}

void mvRight(MineField *mf, int row, int &col) {
    cout << "Entering right:\n";
    while ( col < mf->cols-1&& mf->data[row][col+1] == 0 &&
           (mf->data[row+1][col] || row == mf->rows-1) ){
        cout << col << endl;
        mf->data[row][col++] = CLEAR;
    }
    if (mf->data[row][col] == 0)
        mf->data[row][col] = CLEAR;
}

void mvUp(MineField *mf, int &row, int col) {
    cout << "Entering up: " << endl;
    while ( row > 0 &&  mf->data[row-1][col] == 0 &&
           (mf->data[row][col+1] || row == mf->cols-1)) {
        mf->data[row--][col] = CLEAR;
    }
    if (mf->data[row][col] == 0)
        mf->data[row][col] = CLEAR;
}

void mvDown(MineField *mf, int &row, int col) {
    cout << "Entering down\n";
    cout << col << endl;
    while ( row < mf->rows && mf->data[row+1][col] == 0 &&
           (mf->data[row][col-1] || col == 0 )) {
        mf->data[row++][col] = CLEAR;
        
    }
    if (mf->data[row][col] == 0)
        mf->data[row][col] = CLEAR;

}
*/


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


// return the numbers of adjacent mines to
// a given cell;
int mAdjacent(int a[][NCOLS], int row, int col, int rows) {
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
                // 9 is reserved for mines
                if (a[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the last row, not on first or last column
    else if ( row == rows-1 && col > 0 && col < NCOLS - 1) {
        for (int i = row-1; i <= row; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                // 9 is reserved for mines
                if (a[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the first column, not on first or last row
    // search to the right
    else if ( col == 0 && row > 0 && row < rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col; j <= col+1; ++j)
                // 9 is reserved for mines
                if (a[i][j] == MINE)
                    ++nAd;
        }
    }
    // on the last column, not on first or last row
    // search to the left
    else if ( col == NCOLS-1 && row > 0 && row < rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col; ++j)
                // 9 is reserved for mines
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
    // return number of mines from appropriate if statement
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