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

/***************************************************
 **********Chapter 13 Problem 1 ********************
 **************************************************/
class Date{
public:
    Date(int, int, int);
    void print(int =1) const;
private:
    int month;
    int day;
    int year;
    const char* months[12] = {"January", "February", "March", "April", "May",
                              "June", "July", "August", "Setptember",
                              "October", "November", "December"};
    
    // Format: 01/01/2000
    void print1() const;
    // Format: January 01, 2000
    void print2() const;
    // Format 01 January 2000
    void print3() const;
};

/***************************************************
 **********Chapter 13 Problem 6 ********************
 **************************************************/
class InventoryItem {
public:
    InventoryItem();
    InventoryItem(int, float, int);
    void setItemNumber(int);
    void setQuantity(int);
    void setCost(float);
    int getItemNumber() const {return itemNumber;}
    int getQuantity() const {return quantity;}
    float getCost() const {return cost;}
    float getTotalCost() const { return cost * quantity;}
private:
    int itemNumber;
    int quantity;
    float cost;
    float totalCost;
};


/***************************************************
 **********Chapter 13 Problem 11 *******************
 **************************************************/
class Numbers {
public:
    Numbers(int);
    ~Numbers();
    void fill();
    void setNum(int, float);
    float getNum(int) const;;
    float max() const;
    float min() const;
    float avg() const;
private:
    float *data;
    int size;
};

/***************************************************
 **********Chapter 13 Problem 12 *******************
 **************************************************/
class Payroll {
public:
    Payroll():hours(0), payRate(0) {}
    Payroll(int, int);
    void setHours(int);
    void setRate(int);
    int getHours() const {return hours;}
    int getRate() const {return payRate;}
    int pay() const { return hours * payRate;}
private:
    int hours;
    int payRate;
};

/***************************************************
 **********Chapter 13 Problem 15 *******************
 **************************************************/
// requires the InventoryItem class
class CashRegister {
public:
    CashRegister();
    void print() const;
    void buyItem();
private:
    int nItems;
    InventoryItem *inventory;
    
    int findItem(int) const;
};
void fillItems(InventoryItem *, int);
#endif
