//
//  Minesweeper.cpp
//  Project 2
//
//  Created by Juan Ruiz on 11/21/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include "Minesweeper.h"

using namespace std;

/***************************************************************
 *
 *              Function definitions
 *
 **************************************************************/

void MineField::prompt(int &rows, MineField::Difficulty &d) {
    cout << "Enter the number of rows\n"
    "Minefield will be NxN in size: ";
    cin >> rows;
    
    int diff;
    cout << "Enter the difficulty\n"
    "0=Easy\t 1=Normal\t 2=Hard\n";
    cin >> diff;
    d = intToDiff(diff);
}

/// Function returns true if input was valid
bool MineField::isValidIn(int rows, int cols, MineField::Difficulty diff) const{
    /// make sure that the number of mines does not exceed
    /// the number of spots available
    return (rows * cols) > nMines(diff);
    
}

/// Play a game of minesweeper
/// User inputs how many rows and columns and the dicculty
void MineField::playGame(int nrows, int ncols, MineField::Difficulty diff, char *p) {
    srand(static_cast<unsigned int>(time(0)));
    MineField *mf = new MineField(nrows, ncols);
    mf->mines=nMines(diff);
    setMines(mf);
    prntObscr(mf);
    int row, col;
    do {
        /// Select the row
        do {
            cout << "Enter the row: ";
            cin >> row;
            /// check bounds
        } while (row < 0 || row >= mf->rows);
        do {
            cout << "Enter the column: ";
            cin >> col;
            /// check bounds
        } while (col < 0 || col >= mf->cols);
        cout << endl;
    } while (cont(mf, row, col) && !hasWon(mf));
    
    /// Prepare to print completed minefield
    if (hasWon(mf)) {
        cout << p << "You win\n";
        setFlags(mf);
    }
    else{
        cout << p << " you have lost\n";
        setFlags(mf);
        mf->data[row][col]= MineField::LOSER;
    }
    /// Print the complete minefield
    prntClr(mf);
    
    /// write result to binary file
    writeBin(mf, "result");
    /// deallocate the game area
    delete mf;
}

/// Function gets the user name as a string converts it to a char array
/// for the 1d dynamic array requirement
char *MineField::userName() {
    cout << "Enter your name: ";
    string in;
    cin >> in;
    
    int size = in.size();
    /// make room for '\0'
    char *name = new char[size+1];
    for (int i = 0; i != size; ++i) {
        *(name+i) = in[i];
    }
    *(name+size+1) = '\0';
    
    return name;
}

/// Function that creates the grid on which game will be played
void MineField::create(int rows, int cols) {
    /// dinamically create a minefield
    this->rows=rows;
    this->cols = cols;
    
    /// Create the 2D game minefield
    this->data = new int *[rows];
    
    /// Create each row
    for (int row = 0; row != rows; ++row)
        this->data[row] = new int [cols];
    
    /// Make sure each square is empty
    for (int i = 0; i != rows; ++i)
        for (int j = 0; j != rows; ++j)
            this->data[i][j] = MineField::EMPTY;
}

/// Function return the MineField::Difficulty type from
/// the int variable
MineField::Difficulty MineField::intToDiff(int choice) {
    switch (choice) {
        case (0):
            return MineField::Difficulty::EASY;
            break;
        case (1):
            return MineField::Difficulty::NORMAL;
            break;
        case (2):
            return MineField::Difficulty::HARD;
        default:
            return MineField::Difficulty::EASY;
            break;
    }
}

/// Function deallocates memory
void MineField::destroy(MineField *mf) {
    /// delete each dynamically allocated row
    for (int i = 0; i != mf->rows; ++i)
        delete[] mf->data[i];
    /// delete the dynamically allocated structure
    delete mf;
}

/// Functions prints the minefield with all the squares revealed.
/// used mostly after player loses
void MineField::prntClr() const {
    for (int row = 0; row != rows; ++row){
        for (int col = 0; col != cols; ++col) {
            ///
            if ( *(*(data+row) + col) == MineField::LOSER)
                cout << "T  ";
            else if (*(*(data+row) + col) == MineField::MINE)
                cout << "x  ";
            else if (!isClear(this, row, col))
                cout << nAdjacent(this, row, col) << "  ";
            else
                cout << "0  ";
        }
        cout << endl;
    }
    cout << endl;
}

/// Function prints the minefield with spaces hidden
void MineField::prntObscr(MineField* mf) {
    /// Print the column index
    for (int i = 0; i != mf->cols; ++i){
        /// Pad initial output of column indicator
        if (i==0)
            cout << "  ";
        cout << setw(3) << i;
    }
    cout << endl;
    for (int row = 0; row != mf->rows; ++row){
        for (int col = 0; col != mf->cols; ++col){
            if(col == 0 && row < 10) cout << row << "  ";
            if (col == 0 && row >= 10) cout << row << " ";
            /// KEEP EMPTY spaces and MINEs hidden
            if (mf->data[row][col] == MineField::EMPTY ||
                mf->data[row][col] == MineField::MINE)
                cout << setw(3) << right  << "* ";
            /// print out the CLEARed area
            else if (mf->data[row][col] == MineField::CLEAR)
                cout << setw(2)<< 0 << " ";
            /// Print out the actual value of the square
            else
                cout << setw(2)<< mf->data[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/// Function returns the number of mines to set based on Difficulty
int MineField::nMines(MineField::Difficulty d) const {
    if (d==MineField::EASY)
        return 15;
    else if (d==MineField::NORMAL)
        return 30;
    else
        return 45;
}

/// Function places mines in grid
void MineField::setMines(MineField *mf) {
    /// holds how many mines will be used
    int mines = mf->mines;
    
    /// keep looping through minefield until all mines are set
    while (mines) {
        for (int i = 0; i != mf->rows; ++i) {
            for (int j = 0; j != mf->cols; ++j) {
                /// place mines if result of rand()%15 == 0
                if ((rand() % 100) % 10 == 0){
                    ///only place mines if mines are still available
                    /// and current is empty
                    if (mines && mf->data[i][j] == MineField::EMPTY) {
                        /// set the mine
                        mf->data[i][j] = MineField::MINE;
                        --mines;
                    }
                }
            }
        }
    }
}

/// Function returns how  many 'flag' elements surround a given square
int MineField::nAdjacent(MineField *mf, int row, int col, int FLAG) {
    int nAd=0;              /// the number of adjacent mines
    
    /// not on first or last row or first or last column
    /// most of the searches take place in this area
    if ( row > 0 && col > 0 && row < mf->rows-1 && col < mf->cols-1) {
        /// search the 3x3 grid surrounding a cell
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (mf->data[i][j] == FLAG)
                    ++nAd;
        }
    }
    /// on the first row, not on first or last column
    else if ( row == 0 && col > 0 && col < mf->cols - 1) {
        for (int i = row; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// on the last row, not on first or last column
    else if ( row == mf->rows-1 && col > 0 && col < mf->cols - 1) {
        for (int i = row-1; i <= row; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// on the first column, not on first or last row
    /// search to the right
    else if ( col == 0 && row > 0 && row < mf->rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col; j <= col+1; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// on the last column, not on first or last row
    /// search to the left
    else if ( col == mf->cols-1 && row > 0 && row < mf->rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col; ++j)
                if (mf->data[i][j] == MineField::MINE)
                    ++nAd;
        }
    }
    /// top left corner
    else if (row == 0 && col == 0) {
        if (mf->data[row][col+1] == MineField::MINE) ++nAd;
        if (mf->data[row+1][col] == MineField::MINE) ++nAd;
        if (mf->data[row+1][col+1] == MineField::MINE) ++nAd;
    }
    /// top right corner
    else if (row == 0 && col == mf->cols-1) {
        if (mf->data[row][col-1] == MineField::MINE) ++nAd;
        if (mf->data[row+1][col] == MineField::MINE) ++nAd;
        if (mf->data[row+1][col-1] == MineField::MINE) ++nAd;
    }
    /// bottom left corner
    else if (row == mf->rows-1 && col == 0) {
        if (mf->data[row-1][col] == MineField::MINE) ++nAd;
        if (mf->data[row-1][col+1] == MineField::MINE) ++nAd;
        if (mf->data[row][col+1] == MineField::MINE) ++nAd;
    }
    /// bottom right corner
    else if (row == mf->rows-1 && col == mf->cols-1) {
        if (mf->data[row-1][col-1] == MineField::MINE) ++nAd;
        if (mf->data[row-1][col] == MineField::MINE) ++nAd;
        if (mf->data[row][col-1] == MineField::MINE) ++nAd;
    }
    /// return number of mines from appropriate if statement
    return nAd;
}

/// Function is true if there 0 landmines adjacent to
/// selected square
bool MineField::isClear(int row, int col) const {
    if (nAdjacent(this, row, col))
        return false;            /// there was at least one mine adjacent
    return true;                 /// area was clear
}

/// Clear an area whose values are clear
/// i.e 0 adjacent  mines
void MineField::showZeros(MineField *mf, int row, int col) {
    /// check bounds
    if ( row >= mf->rows || row < 0 || col >= mf->cols || col < 0)
        return;
    if (isClear(mf, row, col) && mf->data[row][col] != MineField::CLEAR){
        mf->data[row][col] = MineField::CLEAR;
        /// go up one row
        showZeros(mf, row+1, col);
        /// go down one row
        showZeros(mf, row-1, col);
        /// go right one col
        showZeros(mf, row, col+1);
        /// go left one col
        showZeros(mf, row, col-1);
    }
    /// space was not clear or already shown
    else
        return;
}

/// Function shows how many mines are adjacent to selected square
/// for the entire minefield
void MineField::setFlags(MineField *mf) {
    for (int i = 0; i != mf->rows; ++i)
        for (int j = 0; j != mf->cols; ++j)
            /// don't look for adjacent mines in areas where
            /// mine is already located
            if (mf->data[i][j] != MineField::MINE)
                mf->data[i][j] = nAdjacent(mf, i, j);
}

/// Function reveals what is underneath the square that the user has selected
/// and whether to continue based on what is revealed
/// i.e selecting a mine means you lost, game over
bool MineField::cont(MineField * mf, int row, int col) {
    /// check if user selected a losing square
    if (mf->data[row][col] == MineField::MINE)
        return false;
    
    /// Square is a zero, clear the surrounding area if necessary
    else if (isClear(mf, row, col) ){
        showZeros(mf, row, col); /// show cleared area
        setPerim();
        prntObscr(mf);
        return true;
    }
    /// Square had adjacent mine
    /// reveal the number to the user
    else {
        mf->data[row][col] = nAdjacent(mf, row, col);
        prntObscr(mf);
        return true;
    }
}

/// Function checks whether the player has won
bool MineField::hasWon(MineField *mf) {
    for (int i = 0; i != mf->rows; ++i)
        for (int j = 0; j != mf->cols; ++j)
            /// if there are empty spaces player has not won
            if (mf->data[i][j] == MineField::EMPTY)
                return false;
    /// there were no empty spaces left. Player has won
    return true;
}

/// Function find the perimeter of the cleared areas
void MineField::setPerim() {
    for (int row = 0; row != rows; ++row ) {
        /// avoid search at left and right edge of array
        for (int col = 0; col != cols; ++col) {
            /// when you're not on the bounds of the array
            if (row > 0 && row < rows-1
                && col > 0 &&  col < cols-1)
                if (data[row][col] == MineField::CLEAR) {
                    /// check that the previous number has mines adjacent
                    if (data[row][col-1] != MineField::CLEAR)
                        data[row][col-1] = nAdjacent(this, row, col-1);
                    /// check if the next number has mines adjacent
                    if (data[row][col+1] != MineField::CLEAR)
                        data[row][col+1] = nAdjacent(this,row, col+1);
                    if (data[row-1][col] != MineField::CLEAR)
                        data[row-1][col] = nAdjacent(this, row-1, col);
                    /// check if the next number has mines adjacent
                    if (data[row+1][col] != MineField::CLEAR)
                        data[row+1][col] = nAdjacent(this,row+1, col);
                    /// check the adjacent corners
                    if (data[row+1][col-1] != MineField::CLEAR)
                        data[row-1][col-1] = nAdjacent(this,row-1, col-1);
                    if (data[row-1][col+1] != MineField::CLEAR)
                        data[row-1][col+1] = nAdjacent(this,row-1, col+1);
                    if (data[row+1][col-1] != MineField::CLEAR)
                        data[row+1][col-1] = nAdjacent(this,row+1, col-1);
                    if (data[row+1][col+1] != MineField::CLEAR)
                        data[row+1][col+1] = nAdjacent(this,row+1, col+1);
                }
        }
    }
}

/// Function writes the minefield structure to a binary file
void MineField::writeBin(MineField *mf, string fileName) {
    /// Write the result to a binary file
    fstream out(fileName.c_str(), ios::out | ios::binary);    /// open the file
    out.write(reinterpret_cast<char *>(&mf),sizeof(*mf)); /// write to the file
    out.close();
}

/// Function prints the data variable from the Minefield structure
/// writen to a binary file
void MineField::readBin(string fileName) {
    /// Ask user if they want to see the result of the last game
    char response;
    cout << "Would you like to see the result of the last game as "
    "read from a binary file?\n"
    "Hit 'y' if yes: ";
    cin >> response;
    if (response == 'y') {
        cout << "\nResult of your last game:\n";
        /// Create space to hold the file read
        MineField *result;
        fstream in(fileName.c_str(), ios::in | ios::binary);
        in.read(reinterpret_cast<char *>(&result), sizeof(*result));
        prntClr(result);
        in.close();
    }
    
}

/// This function creates an array of the Minefield structure
/// as part of the requirments to be able to write to and read
/// from an array of structures
//void MineField::fields() {
//    cout << "How many mine fields do you want to see: ";
//    int n;
//    cin >> n;
//    
//    MineField **mf = new MineField*[n];
//    const int row = 10;
//    const int col = 10;
//    /// create the fields
//    for (int i = 0; i != n; ++i) {
//        /// Create each field
//        mf[i] = create(row, col);
//        /// get number of mines
//        mf[i]->mines = nMines(MineField::EASY);
//        /// set the mines
//        setMines(*(mf+i));
//        /// set the flags
//        setFlags(*(mf+i));
//        /// print the field
//        prntClr(*(mf+i));
//        cout << endl;
//    }
//    cout << endl;
//    
//    /// deallocate memory
//    for (int i = 0; i != n; ++i) {
//        destroy(*(mf+i));
//    }
//    delete []mf;
//}
