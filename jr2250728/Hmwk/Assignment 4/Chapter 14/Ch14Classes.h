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
 ********* Chapter 14 - Problem 2 *************
 *********************************************/
class DayofYear {
public:
    DayofYear(int);
    void print() const;
    static int dPerM[12];
    static const char* months[12];
private:
    int day;
};


/**********************************************
 ********* Chapter 14 - Problem 4 *************
 *********************************************/
// 8hrs = 1 work day
class NumDays {
    
};


#endif /* defined(__Chapter14__Ch14Classes__) */
