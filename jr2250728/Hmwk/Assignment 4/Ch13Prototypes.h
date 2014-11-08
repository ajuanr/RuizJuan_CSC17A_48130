//
//  Problems from Chapter 13
//  6th edition
//
//  Ch13Prototypes.h
//  RuizJuan-Chapter13
//
//  Created by Juan Ruiz on 11/7/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#ifndef RuizJuan_Chapter13_Ch13Prototypes_h
#define RuizJuan_Chapter13_Ch13Prototypes_h

// Chapter 13 Problem
class Date{
public:
    Date(int, int, int);
private:
    int month;
    int day;
    int year;
    
    // Format: 01/01/2000
    void print1() const;
    // Format: January 01, 2000
    void print2() const;
    // Format 01 January 2000
    void print3() const;
};

#endif
