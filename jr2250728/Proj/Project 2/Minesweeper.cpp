//
//  Minesweeper.cpp
//  Project 2
//
//  Created by Juan Ruiz on 11/21/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
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

void Minesweeper::create(int row, int col) {
    /// dinamically create a Minesweeper
    rows=row;
    cols = col;
    
    /// Set up the rows
    data = new int *[rows];
    
    /// Create each column
    for (int row = 0; row != rows; ++row)
        data[row] = new int [cols];
}

void Minesweeper::setRows(int row) {
    if ( row <= 0 )
        throw badSize();
    rows = row;
}

void Minesweeper::setCols(int col) {
    if (col <= 0 )
        throw badSize();
    cols = col;
}

void Minesweeper::prompt() {
    cout << "Enter the number of rows(1-10)\n"
            "Area will be rowsxrows in size: ";
    int row;
    cin >> row;
    /// invalid sizes
    if (row > 10 || row < 1)
        throw badSize();
    rows = row;
    cols = row;
    int diff;
    cout << "Enter the difficulty\n"
    "0=Easy\t 1=Normal\t 2=Hard\n";
    cin >> diff;
    mines = nMines(intToDiff(diff));
}

/// Function returns true if input was valid
bool Minesweeper::isValidIn() const{
    /// make sure that the number of mines does not exceed
    /// the number of spots available and that mines exist
    return (((rows * cols) > mines) && (mines>0));
}

void Minesweeper::setUp() {
    /// Get the user name
    char *player = userName();
    /// ask user if they want to play
    cout << "Hello " << player
         << ", Would you like to play a game of minesweeper?\n"
            "Hit 'y' if yes\n";
    char ans;
    cin >> ans;
    
    /// play if answer is yes
    if (ans == 'y') {
        cout << "would you like to load a previous game: ";
        char ans2;
        cin >> ans2;
        if ( ans2 == 'y') {
            loadGame();
        }
        else
            /// Get game information from user
            prompt();
        if (isValidIn()) {
            while (ans == 'y' && isValidIn()) {
                playGame();
                cout << endl;
                cin.ignore();
                cout << "Would you like to play again " << player << "? ";
                cin >> ans;
                cout << endl;
                /// Get new data only if user wants to continue
                if (ans =='y') {
                    prompt();
                    clearBoard();
                }
            }
        }
        /// Information was invalid
        else
            throw badSize();
    }
    cout << "Game is Over.\n";
    
    /// Cleanup
    delete player;
    
    cout << endl;
    cout << "Goodbye\n";
}

/// Play a game of minesweeper
/// User inputs how many rows and columns and the dicculty
void Minesweeper::playGame() {

    setMines();
    prntObscr();
    int row, col;
    int turn = 0;
    int initialTime = static_cast<unsigned int>(time(0));
    do {
        int begTime = static_cast<unsigned int>(time(0));
        cout << "Turn: " << turn++ << endl;
        /// Select the row
        do {
            cout << "Enter -1 to save the settings and exit\n";
            cout << "Enter the row " << 0 << "-" << rows-1 << ": ";
            cin >> row;
            /// User wants to save the game
            /// save the game and exit
            if ( row == -1) {
                saveGame();
                return;
            }
            /// check bounds
        } while (row < 0 || row >= rows);
        /// Select the column
        do {
            cout << "Enter the column " << 0 << "-" << cols-1 << ": ";
            cin >> col;
            /// check bounds
        } while (col < 0 || col >= cols);
        
        /// endTime
        int endTime = static_cast<unsigned int>(time(0));
        cout << "Turn took: " << endTime - begTime << " seconds.\n";
        cout << endl;
    } while (cont(row, col) && !hasWon());
    
    /// Prepare to print completed Minesweeper
    if (hasWon()) {
        cout << "You win\n";
        setFlags();
    }
    else{
        cout << "You have, lost\n";
        setFlags();
        data[row][col]= Minesweeper::LOSER;
    }

    int finalTime = static_cast<unsigned int>(time(0));
    cout << "Game was completed in " << finalTime - initialTime << " seconds.\n";
    
    /// Print the complete Minesweeper
    print();
}

/// Function gets the user name as a string converts it to a char array
/// for the 1d dynamic array requirement
char* Minesweeper::userName() {
    cout << "Enter your name: ";
    string in;
    cin >> in;
    
    typedef string::size_type sType;
    sType size = in.size();
    /// make room for '\0'
    char *name = new char[size+1];
    for (sType i = 0; i != size; ++i) {
        *(name+i) = in[i];
    }
    *(name+size+1) = '\0';
    
    return name;
}

/// Function that clears the grid on which game will be played
void Minesweeper::clearBoard() {
    /// Make sure each square is empty
    for (int i = 0; i != rows; ++i)
        for (int j = 0; j != rows; ++j)
            data[i][j] = Minesweeper::EMPTY;
}

/// Function return the Minesweeper::Difficulty type from
/// the int variable
Minesweeper::Difficulty Minesweeper::intToDiff(int choice) {
    switch (choice) {
        case (0):
            return Minesweeper::EASY;
            break;
        case (1):
            return Minesweeper::NORMAL;
            break;
        case (2):
            return Minesweeper::HARD;
        default:
            return Minesweeper::EASY;
            break;
    }
}

/// Functions prints the Minesweeper with all the squares revealed.
/// used mostly after player loses
void Minesweeper::print() const {
    cout << "Here's what the board looked like\n";
    for (int row = 0; row != rows; ++row){
        for (int col = 0; col != cols; ++col) {
            ///
            if ( *(*(data+row) + col) == Minesweeper::LOSER)
                cout << "t  ";
            else if (*(*(data+row) + col) == Minesweeper::MINE)
                cout << "x  ";
            else if (!isClear(row, col))
                cout << nAdjacent(row, col) << "  ";
            else
                cout << "0  ";
        }
        cout << endl;
    }
    cout << endl;
}

/// Function prints the Minesweeper with spaces hidden
void Minesweeper::prntObscr() const{
    /// Print the column index
    for (int i = 0; i != cols; ++i){
        /// Pad initial output of column indicator
        if (i==0)
            cout << "  ";
        cout << setw(3) << i;
    }
    cout << endl;
    for (int row = 0; row != rows; ++row){
        for (int col = 0; col != cols; ++col){
            if(col == 0 && row < 10) cout << row << "  ";
            if (col == 0 && row >= 10) cout << row << " ";
            /// KEEP EMPTY spaces and MINEs hidden
            if (data[row][col] == Minesweeper::EMPTY ||
                data[row][col] == Minesweeper::MINE)
                cout << setw(3) << right  << "* ";
            /// print out the CLEARed area
            else if (data[row][col] == Minesweeper::CLEAR)
                cout << setw(2)<< 0 << " ";
            /// Print out the actual value of the square
            else
                cout << setw(2)<< data[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/// Function returns the number of mines to set based on Difficulty
int Minesweeper::nMines(Minesweeper::Difficulty d) const {
    if (d==Minesweeper::EASY)
        return (rows*cols)/10;
    else if (d==Minesweeper::NORMAL)
        return (rows*cols)/5;
    else
        return (rows*cols)/3;
}

/// Function places mines in grid
void Minesweeper::setMines() {
    int minecpy = mines;
    /// keep looping through Minesweeper until all mines are set
    while (minecpy) {
        for (int i = 0; i != rows; ++i) {
            for (int j = 0; j != cols; ++j) {
                /// place mines if result of rand()%15 == 0
                if ((rand() % 100) % 10 == 0){
                    ///only place mines if mines are still available
                    /// and current space is empty
                    if (minecpy && data[i][j] == Minesweeper::EMPTY) {
                        /// set the mine
                        data[i][j] = Minesweeper::MINE;
                        /// decrement number of mines available
                        --minecpy;
                    }
                }
            }
        }
    }
}

/// Function returns how  many 'flag' elements surround a given square
int Minesweeper::nAdjacent(int row, int col, int FLAG) const{
    int nAd=0;              /// the number of adjacent mines
    
    /// not on first or last row or first or last column
    /// most of the searches take place in this area
    if ( row > 0 && col > 0 && row < rows-1 && col < cols-1) {
        /// search the 3x3 grid surrounding a cell
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (data[i][j] == FLAG)
                    ++nAd;
        }
    }
    /// on the first row, not on first or last column
    else if ( row == 0 && col > 0 && col < cols - 1) {
        for (int i = row; i <= row+1; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (data[i][j] == Minesweeper::MINE)
                    ++nAd;
        }
    }
    /// on the last row, not on first or last column
    else if ( row == rows-1 && col > 0 && col < cols - 1) {
        for (int i = row-1; i <= row; ++i) {
            for (int j = col-1; j <= col+1; ++j)
                if (data[i][j] == Minesweeper::MINE)
                    ++nAd;
        }
    }
    /// on the first column, not on first or last row
    /// search to the right
    else if ( col == 0 && row > 0 && row < rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col; j <= col+1; ++j)
                if (data[i][j] == Minesweeper::MINE)
                    ++nAd;
        }
    }
    /// on the last column, not on first or last row
    /// search to the left
    else if ( col == cols-1 && row > 0 && row < rows - 1) {
        for (int i = row-1; i <= row+1; ++i) {
            for (int j = col-1; j <= col; ++j)
                if (data[i][j] == Minesweeper::MINE)
                    ++nAd;
        }
    }
    /// top left corner
    else if (row == 0 && col == 0) {
        if (data[row][col+1] == Minesweeper::MINE) ++nAd;
        if (data[row+1][col] == Minesweeper::MINE) ++nAd;
        if (data[row+1][col+1] == Minesweeper::MINE) ++nAd;
    }
    /// top right corner
    else if (row == 0 && col == cols-1) {
        if (data[row][col-1] == Minesweeper::MINE) ++nAd;
        if (data[row+1][col] == Minesweeper::MINE) ++nAd;
        if (data[row+1][col-1] == Minesweeper::MINE) ++nAd;
    }
    /// bottom left corner
    else if (row == rows-1 && col == 0) {
        if (data[row-1][col] == Minesweeper::MINE) ++nAd;
        if (data[row-1][col+1] == Minesweeper::MINE) ++nAd;
        if (data[row][col+1] == Minesweeper::MINE) ++nAd;
    }
    /// bottom right corner
    else if (row == rows-1 && col == cols-1) {
        if (data[row-1][col-1] == Minesweeper::MINE) ++nAd;
        if (data[row-1][col] == Minesweeper::MINE) ++nAd;
        if (data[row][col-1] == Minesweeper::MINE) ++nAd;
    }
    /// return number of mines from appropriate if statement
    return nAd;
}

/// Function returns true if
/// there are 0 landmines adjacent to selected square
bool Minesweeper::isClear(int row, int col) const {
    if (nAdjacent(row, col))
        return false;            /// nAdjacent returned 1 or more
    return true;                 /// nAdjacent returned 0
}

/// Clear an area whose values are CLEAR
/// i.e 0 adjacent mines
void Minesweeper::showZeros(int row, int col) {
    /// check bounds
    if ( row >= rows || row < 0 || col >= cols || col < 0)
        return;
    if (isClear(row, col) && data[row][col] != Minesweeper::CLEAR){
        data[row][col] = Minesweeper::CLEAR;
        /// go up one row
        showZeros(row+1, col);
        /// go down one row
        showZeros(row-1, col);
        /// go right one col
        showZeros(row, col+1);
        /// go left one col
        showZeros(row, col-1);
    }
    /// space was not clear or already shown
    else
        return;
}

/// Function shows how many mines are adjacent to selected square
/// for the entire Minesweeper
void Minesweeper::setFlags() {
    for (int i = 0; i != rows; ++i)
        for (int j = 0; j != cols; ++j)
            /// don't look for adjacent mines in areas where
            /// mine is already located
            if (data[i][j] != Minesweeper::MINE)
                data[i][j] = nAdjacent(i, j);
}

/// Function reveals what is underneath the square that the user has selected
/// and whether to continue based on what is revealed
/// i.e selecting a mine means you lost, game over
bool Minesweeper::cont(int row, int col) {
    /// check if user selected a losing square
    if (data[row][col] == Minesweeper::MINE)
        return false;
    
    /// Square is a zero, clear the surrounding area if necessary
    else if (isClear(row, col) ){
        showZeros(row, col); /// show cleared area
        setPerim();
        prntObscr();
        return true;
    }
    /// Square had adjacent mine
    /// reveal the number to the user
    else {
        data[row][col] = nAdjacent(row, col);
        prntObscr();
        return true;
    }
}

/// Function checks whether the player has won
/// if there are no EMPTY spaces left the game is won
bool Minesweeper::hasWon() const {
    for (int i = 0; i != rows; ++i)
        for (int j = 0; j != cols; ++j)
            /// if there are empty spaces player has not won
            if (data[i][j] == Minesweeper::EMPTY)
                return false;
    /// there were no empty spaces left. Player has won
    return true;
}

/// Function finds the perimeter of the cleared areas
void Minesweeper::setPerim() {
    for (int row = 0; row != rows; ++row ) {
        /// avoid searching at left and right edge of array
        for (int col = 0; col != cols; ++col) {
            /// when you're not on the bounds of the array
            if (row > 0 && row < rows-1
                && col > 0 &&  col < cols-1){
                if (data[row][col] == Minesweeper::CLEAR) {
                    /// check that the previous number has mines adjacent
                    if (data[row][col-1] != Minesweeper::CLEAR)
                        data[row][col-1] = nAdjacent(row, col-1);
                    /// check if the next number has mines adjacent
                    if (data[row][col+1] != Minesweeper::CLEAR)
                        data[row][col+1] = nAdjacent(row, col+1);
                    if (data[row-1][col] != Minesweeper::CLEAR)
                        data[row-1][col] = nAdjacent(row-1, col);
                    /// check if the next number has mines adjacent
                    if (data[row+1][col] != Minesweeper::CLEAR)
                        data[row+1][col] = nAdjacent(row+1, col);
                    /// check the adjacent corners
                    if (data[row-1][col-1] != Minesweeper::CLEAR)
                        data[row-1][col-1] = nAdjacent(row-1, col-1);
                    if (data[row-1][col+1] != Minesweeper::CLEAR)
                        data[row-1][col+1] = nAdjacent(row-1, col+1);
                    if (data[row+1][col-1] != Minesweeper::CLEAR)
                        data[row+1][col-1] = nAdjacent(row+1, col-1);
                    if (data[row+1][col+1] != Minesweeper::CLEAR)
                        data[row+1][col+1] = nAdjacent(row+1, col+1);
                }
            }
        }
    }
}

void Minesweeper::saveGame() {
    fstream saveFile("gameSave", ios::out | ios::binary);
    saveFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    saveFile.close();
}

/// Function prints the data variable from the Minesweeper structure
/// writen to a binary file
void Minesweeper::loadGame() {
    fstream saveFile("gameSave", ios::in | ios::binary);
    if (!saveFile.is_open())
        throw "Error file failed to open\n";
    /// Create space to hold the file read
    //Minesweeper *result = new Minesweeper(10,10);
    saveFile.read(reinterpret_cast<char*>(this), sizeof(*this));
    //print();
    saveFile.close();
    
    //return result;
}

Minesweeper& Minesweeper::operator=(const Minesweeper &rhs) {
    create(rhs.getRows(), rhs.getCols());
    
    for (int i = 0; i != rhs.getRows(); ++i) {
        for (int j = 0; j != rhs.getCols(); ++j)
            data[i][j] = rhs[i][j];
    }
    return *this;
}
