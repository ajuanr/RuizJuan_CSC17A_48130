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

/// This is the class that holds the minefield
/// as well as the associated flags that occur when
/// a user selects a square
class MineField {
private:
    /***************************************************
     *             Member Variables
     **************************************************/
    /// This is the minefield
    int **data;
    /// The total number of rows
    int rows;
    /// The total number of columns
    int cols;
    /// number of mines
    int mines;
    
    /***************************************************
     *             Utility Function Prototypes
     **************************************************/
    void create(int, int);
    void destroy();
    MineField::Difficulty intToDiff(int);
    bool isValidIn(int, int, MineField::Difficulty) const;
    int nMines(MineField::Difficulty) const;
    void setMines();
    void setFlags();
    int nAdjacent(int, int, int = MineField::MINE) const;
    bool isClear(int, int) const;
    void clrArea(MineField *, int, int);
    void setPerim();
    void showZeros(MineField *, int, int);
    bool hasWon() const;
    void fields();
    bool cont(MineField *, int, int);
    
    void prompt(int&, MineField::Difficulty&);
    char *userName();
    void readBin(std::string);
    
public:
    /***************************************************
     *             Constructors / Destructor
     **************************************************/
    MineField(int row, int col) {create( row, col);}
    ~MineField() {destroy();}
    
    /***************************************************
     *             Enumerations
     **************************************************/
    /// Determines how many mines to set
    enum Difficulty {EASY, NORMAL, HARD};
    /// Flags representing various square possibilities
    enum Flags {EMPTY=10, MINE, CLEAR, LOSER};
    
    /***************************************************
     *             Function Prototypes
     **************************************************/
    void prntClr() const;
    void prntObscr() const;
    void setUp();
    void playGame(int, int, MineField::Difficulty, char*);
};




#endif /* defined(__Project_2__Minesweeper__) */
