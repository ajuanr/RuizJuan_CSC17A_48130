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

/**********************************************
 ********* Chapter 14 - Problem 13 ************
 *********************************************/
class FeetInches{
public:
    FeetInches():feet(0), inches(0){}
    FeetInches(int, int);
    void simplify();
    void setFeet(int n) { feet = n; }
    void setInches(int n) { inches = n; }
    int getFeet() const { return feet; }
    int getInches() const { return inches; }
    
    FeetInches operator*(const FeetInches&);
private:
    int feet;
    int inches;
};

class RoomDimension {
public:
    RoomDimension();
    RoomDimension(int, int, int, int);
    FeetInches getArea() { return length*width; }
private:
    FeetInches length;
    FeetInches width;
};

class RoomCarpet {
public:
    RoomCarpet();
    float totalCost();
private:
    RoomDimension area;
    float cost;
};

#endif /* defined(__Chapter14__Ch14Classes__) */
