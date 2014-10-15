/*
 * Ruiz, Juan - Project 1 - 48130
 * 
 * Project runs a game of minesweeper
 * 
 */

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
    DIFFICULTY d;   // determines how many mines
    int nMines;     // number of mines

};

MineField* create(int, int);
void destroy(MineField *);
void printFld(MineField *);
void prntObscr(MineField *);
int nMines(MineField::DIFFICULTY);
void setMines(MineField *,  MineField::DIFFICULTY);
void setFlags(MineField *);
int mAdjacent(MineField *, int, int);
bool isClear(MineField *, int, int);
void clrArea(MineField *, int, int);

void showZeros(MineField *, int, int);

void select(MineField *, int, int);
void setUpGame();
void prompt(int&, int&);

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
    select(mf, 3, 5);
    //setFlags(mf);
    prntObscr(mf);
    int row = 0;
    int col = 9;
    if( !isClear(mf, row,col)) {
        if (mf->data[row][col] == MINE)
            cout << "You Lose\n";
        else
            cout << mf->data[row][col] ;
    }
    else

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
void printFld(MineField* mf) {   
    for (int row = 0; row != mf->rows; ++row){
        for (int col = 0; col != mf->cols; ++col)
            cout << mf->data[row][col] << " ";
        cout << endl;
    }
    cout << endl;
}

// print the minefield obscured
void prntObscr(MineField* mf) {
    for (int i = 0; i != mf->cols; ++i){
        if (i==0)
            cout << "  "; // blank space to align number with column
        cout << i << " ";
    }
    cout << endl;
    for (int row = 0; row != mf->rows; ++row){
        for (int col = 0; col != mf->cols; ++col){
            if(col == 0) cout << row << " "; // output row number
            if (mf->data[row][col] == 0 || mf->data[row][col] == 9)
                cout << "* ";
            else if (mf->data[row][col] == -1 )
                cout << 0 << " ";
            else
                cout << mf->data[row][col] << " ";
        }
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
    // the number of adjacent
    int nAd=0;
    // not on first or last row or first or last column
    // most of the searches take place in this area
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
    const int CLEAR = -1;
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

void select(MineField * mf, int row, int col) {
    if (mf->data[row][col] == 9) {
        cout << "You lose\n";
        setFlags(mf);
        printFld(mf);
    }
    else if (isClear(mf, row, col) ){
        showZeros(mf, row, col); // show cleared area
        prntObscr(mf);
    }
    else {
        mf->data[row][col] == mAdjacent(mf, row, col);
        prntObscr(mf);
    }
}