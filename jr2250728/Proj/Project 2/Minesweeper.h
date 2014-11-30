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
    bool isValidIn() const;
    int nMines(Minesweeper::Difficulty) const;
    void setMines();
    void setFlags();
    int nAdjacent(int, int, int = Minesweeper::MINE) const;
    bool isClear(int, int) const;
    void setPerim();
    void showZeros(int, int);
    bool hasWon() const;
    bool cont(int, int);
    void prompt();
    char *userName();
    
public:
    /// Throw this if user enter an invalid size/index
    class badSize{};
    /***************************************************
     *             Constructors / Destructor
     **************************************************/
    Minesweeper(int row, int col):GameBoard(row, col)
                                {clearBoard();}

    /***************************************************
     *             Function Prototypes
     **************************************************/
    void print() const;
    void prntObscr() const;
    void setUp();
    void playGame();
    void clearBoard();
    void saveGame();
    void loadGame();
    int getMines() const { return mines;}
    
    Minesweeper& operator=(const Minesweeper&);
};

#endif /* defined(__Project_2__Minesweeper__) */
