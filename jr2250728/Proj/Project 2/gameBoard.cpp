//
//  gameBoard.cpp
//  Project 2
//
//  Created by Juan on 11/28/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <iostream>
#include "gameBoard.h"

/// Function that creates the grid on which game will be played
void GameBoard::create(int row, int col) {
    /// dinamically create a Minesweeper
    rows=row;
    cols = col;
    
    /// Set up the rows
    data = new int *[rows];
    
    /// Create each column
    for (int row = 0; row != rows; ++row)
        data[row] = new int [cols];
}

/// Function resets the GameBoard to initial in order to use it again
void GameBoard::clearBoard() {
    for (int i = 0; i != rows; ++i)
        for (int j = 0; j != cols; ++j)
            data[i][j] = 0;
}

/// Function deallocates memory
void GameBoard::destroy() {
    /// delete each dynamically allocated row
    for (int i = 0; i != rows; ++i)
        delete[] data[i];
    /// delete the dynamically allocated structure
    delete data;
}

void GameBoard::setRows(int row) {
    if ( row <= 0 )
        throw badSize();
    rows = row;
}

void GameBoard::setCols(int col) {
    if (col <= 0 )
        throw badSize();
    cols = col;
}

void GameBoard::print() const {
    for (int i = 0; i != rows; ++i){
        for (int j = 0; j != cols; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}