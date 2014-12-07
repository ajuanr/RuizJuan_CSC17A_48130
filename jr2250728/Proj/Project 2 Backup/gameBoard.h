//
//  gameBoard.h
//  Project 2
//
//  Created by Juan on 11/28/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#ifndef Project_2_gameBoard_h
#define Project_2_gameBoard_h

#include "AbsGame.h"

/// Abstract class for games that require an n*m array
/// such as Minesweeper, Tic-Tac-Toe, Battleship
class GameBoard: public AbsGame{
private:
    
protected:
    int **data;
    int rows;
    int cols;
    virtual void create(int, int);

public:
    /// Throw this if user tries to set negative row or column
    class badSize{};
    
    GameBoard(int rows, int cols) {create(rows,cols);clearBoard();}
    virtual ~GameBoard(){destroy();}
    virtual void destroy();
    virtual void setRows(int);
    virtual void setCols(int);
    virtual int getRows() const {return rows;}
    virtual int getCols() const {return cols;}
    virtual void clearBoard();
    virtual void setUp();
    virtual void loadGame();
    virtual void print() const;
    int* operator[](int index) { return data[index];}
    int* operator[](int index) const { return data[index];}
};

#endif
