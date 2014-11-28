//
//  gameBoard.h
//  Project 2
//
//  Created by Juan on 11/28/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#ifndef Project_2_gameBoard_h
#define Project_2_gameBoard_h

/// Abstract class for games that require an n*m array
/// such as Minesweeper, Tic-Tac-Toe, Battleship
class GameBoard {
private:
    protected:
    int **data;
    int rows;
    int cols;
protected:
    virtual void create(int, int);
public:
    GameBoard(int rows, int cols) {create(rows,cols);}
    //virtual void clearBoard();
    virtual void setUp()=0;
    
};

#endif
