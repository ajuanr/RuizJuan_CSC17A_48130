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
void gameBoard::create(int rows, int cols) {
    /// dinamically create a Minesweeper
    this->rows=rows;
    this->cols = cols;
    
    /// Create the 2D game Minesweeper
    data = new int *[rows];
    
    /// Create each row
    for (int row = 0; row != rows; ++row)
        data[row] = new int [cols];
}