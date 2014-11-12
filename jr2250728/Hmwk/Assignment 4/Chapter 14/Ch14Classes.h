//
//  Ch14Classes.h
//  Chapter14
//
//  Created by Juan Ruiz on 11/9/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#ifndef __Chapter14__Ch14Classes__
#define __Chapter14__Ch14Classes__

/**********************************************
 ********* Chapter 14 - Problem 1 *************
 *********************************************/
// convert integers to their english description
// e.g. 100 = one hundred
class Numbers {
public:
    Numbers(int);
    void print() const;
    //  Static variables. As specified in text
    static char lessThan20 [20][25];
    static char hundred[];
    static char thousand[];
    
private:
    int num;
    
    // utitiliy functions
    int *numArray() const;
};

// static var definitions
char Numbers::lessThan20[20][25]  = {"one", "two", "three", "four", "five",
                                     "six", "seven", "eight", "nine", "ten",
                                     "eleven", "twelve", "thirteen", "fourteen",
                                     "fifteen", "sixteen", "seventeen",
                                     "eighteen", "nineteen"};
char Numbers::hundred[] = {"hundred"};
char Numbers::thousand[] = {"thousand"};

#endif /* defined(__Chapter14__Ch14Classes__) */
