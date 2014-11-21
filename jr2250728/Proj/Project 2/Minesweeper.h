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
using std::string;
/// This is the structure that holds the minefield
/// as well as the associated flags that occur when
/// a user selects a square
struct MineField {
    /// Determines how many mines to set
    enum Difficulty {EASY, NORMAL, HARD};
    /// Flags representing various square possibilities
    enum Flags {EMPTY=10, MINE, CLEAR, LOSER};
    /// This is the minefield
    short **data;
    /// The total number of rows
    short rows;
    /// The total number of columns
    short cols;
    /// number of mines
    short mines;
};

/***************************************************
 *
 *             Function Prototypes
 *
 **************************************************/
MineField *create(short, short);
void destroy(MineField *);
void prntClr(MineField *);
void prntObscr(MineField *);
MineField::Difficulty shortToDiff(short);
bool isValidIn(short, short, MineField::Difficulty);
short nMines(MineField::Difficulty);
void setMines(MineField *);
void setFlags(MineField *);
short nAdjacent(MineField *, short, short, short = MineField::MINE);
bool isClear(MineField *, short, short);
void clrArea(MineField *, short, short);
void setPerim(MineField *);
void showZeros(MineField *, short, short);
bool hasWon(MineField *);
void fields();
bool cont(MineField *, short, short);
void playGame(short, short, MineField::Difficulty, char*);
void prompt(short&, MineField::Difficulty&);
char *userName();
void writeBin(MineField *, string);
void readBin(string);

#endif /* defined(__Project_2__Minesweeper__) */
