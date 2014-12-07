//
//  AbsGame.h
//  Project 2
//
//  Created by Juan on 12/7/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#ifndef Project_2_AbsGame_h
#define Project_2_AbsGame_h

class AbsGame {
    virtual void setRows(int)=0;
    virtual void setCols(int)=0;
    virtual int getRows() const =0;
    virtual int getCols() const =0;
    virtual void setUp()=0;
    virtual void print() const = 0;
};

#endif
