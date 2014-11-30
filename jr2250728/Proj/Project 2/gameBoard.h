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
    void create(int, int);

public:
    GameBoard(int rows, int cols) {create(rows,cols);clearBoard();}
    virtual ~GameBoard(){destroy();}
    void destroy();
    int getRows() const {return rows;}
    int getCols() const {return cols;}
    virtual void clearBoard();
    virtual void setUp()=0;
    virtual void loadGame()=0;
    virtual void playGame()=0;
    virtual void print() const;
    int* operator[](int index) { return data[index];}
    int* operator[](int index) const { return data[index];}
};

#endif
