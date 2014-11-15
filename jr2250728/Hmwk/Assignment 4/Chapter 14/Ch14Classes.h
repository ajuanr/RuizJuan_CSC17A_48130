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
public:
    NumDays(int);
    float getDays() {return hours / 8.0;}
    int operator+(const NumDays&);
    int operator-(const NumDays&);
    NumDays operator++(int);            // postfix operator
    NumDays& operator++();              // prefix operator
    NumDays operator--(int);            // postfix operator
    NumDays& operator--();              // prefix operator
private:
    int hours;
};

/**********************************************
 ********* Chapter 14 - Problem 10 ************
 *********************************************/
class DivSales {
public:
    static float yrlySales;
    static void addSales(float);
    
    DivSales();
    
    void setSales(float, float, float, float);
    float getDivSales(int);
    
    
    
private:
    float salesFig[4];    // four divisions in company
};

#endif /* defined(__Chapter14__Ch14Classes__) */
