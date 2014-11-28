//
//  gameBoard.cpp
//  Project 2
//
//  Created by Juan on 11/28/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <stdio.h>
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

void GameBoard::clearBoard() {
    for (int i = 0; i != rows; ++i)
        for (int j = 0; j != cols; ++j)
            data[i][j] = 0;
}