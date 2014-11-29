//
//  Minesweeper.h
//  Project 2
//
//  Created by Juan Ruiz on 11/21/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#ifndef __Project_2__Minesweeper__
#define __Project_2__Minesweeper__

#include <string>
#include "gameBoard.h"

/// This is the class that holds the Minesweeper
/// as well as the associated flags that occur when
/// a user selects a square
class Minesweeper: public GameBoard {
private:
    /***************************************************
     *                Enumerations
     **************************************************/
    /// Determines how many mines to set
    enum Difficulty {EASY, NORMAL, HARD};
    /// Flags representing various square possibilities
    enum Flags {EMPTY=10, MINE, CLEAR, LOSER};
    
    /***************************************************
     *              Member Variables
     **************************************************/
    /// number of mines
    int mines;
    
    /***************************************************
     *             Utility Function Prototypes
     **************************************************/
    void create(int, int);
    //void destroy();
    Minesweeper::Difficulty intToDiff(int);
    bool isValidIn(int, int) const;
    int nMines(Minesweeper::Difficulty) const;
    void setMines();
    void setFlags();
    int nAdjacent(int, int, int = Minesweeper::MINE) const;
    bool isClear(int, int) const;
    void setPerim();
    void showZeros(int, int);
    bool hasWon() const;
    bool cont(Minesweeper *, int, int);
    void prompt();
    char *userName();
    void readBin(std::string);
    
public:
    /***************************************************
     *             Constructors / Destructor
     **************************************************/
    Minesweeper(int row, int col):GameBoard(row, col)
                                {clearBoard();}
    //~Minesweeper() {destroy();}

    /***************************************************
     *             Function Prototypes
     **************************************************/
    void prntClr() const;
    void prntObscr() const;
    void setUp();
    void playGame(char*);
    void clearBoard();
};

#endif /* defined(__Project_2__Minesweeper__) */
