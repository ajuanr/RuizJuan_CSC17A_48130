//
//  Ch13Defs.cpp
//  RuizJuan-Chapter13
//
//  Created by Juan Ruiz on 11/7/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Ch13Prototypes.h"

using namespace std;

Date::Date(int m, int d, int y) {
    (m < 13 && m > 0) ? month = m: month=1;
    (d < 32 && d > 0) ? day = d: day=1;
    (y < 2050 && y > 1950 ) ? year = y: year=1950;
}

void Date::print1() const {
    cout << month << "/" << day << "/" << year << endl;
}

void Date::print2() const {
    cout << months[month-1] << " " << day << ", " << year << endl;
}

void Date::print3() const {
    cout << day << " " << months[month-1] << " " << year << endl;
}

void Date::print(int n) const {
    switch (n) {
        case (1): print1(); break;
        case (2): print2(); break;
        case (3): print3(); break;
        default: print1(); break;
    }
    cout << endl;
}

/***************************************************
 ***************** InventoryItem class definitions *****
 **************************************************/
InventoryItem::InventoryItem() {
    setCost(0);
    setQuantity(0);
    setItemNumber(0);
}

InventoryItem::InventoryItem(int itemNum, float cost, int quant) {
    setCost(cost);
    setQuantity(quant);
    setItemNumber(itemNum);
}

void InventoryItem::setCost(float c) {
    (c > 0) ? cost=c : cost=0;
}

void InventoryItem::setItemNumber(int i) {
    (i > 0) ? itemNumber = i : itemNumber = 0;
}

void InventoryItem::setQuantity(int q) {
    (q > 0) ? quantity = q : quantity = 0;
}

/***************************************************
 ***************** Numbers class definitions *******
 **************************************************/
Numbers::Numbers(int n) {
    if (n > 0) {
        data = new float[n];
        size = n;
    }
    else {
        size=1;
        data = new float[1];
    }
    // fill the array
    fill();
}

Numbers::~Numbers() {
    cout << "In destructor. Deleting data.\n";
    delete []data;
}

// fill array with values from 10-99
void Numbers::fill() {
    for (int i = 0; i != size; ++i) {
        data[i] = rand() % 90 + 10;
    }
}

void Numbers::setNum(int index, float val) {
    // only set value if it falls within the array
    if (index >=0 && index < size)
        data[index] = val;
}

float Numbers::getNum(int index) const {
    // only set value if it falls within the array
    if (index >=0 && index < size)
        return data[index];
    return -1;
}

float Numbers::max() const {
    float max = data[0];
    for (int i = 0; i != size; ++i)
        if (data[i] > max)
            max = data[i];
    return max;
}

float Numbers::min() const {
    float min = data[0];
    for (int i = 0; i != size; ++i)
        if (data[i] > min)
            min = data[i];
    return min;
}

float Numbers::avg() const {
    float sum = 0.0;
    int count=0;
    while (count++ != size) {
        sum += data[count];
    }
    return sum / count;
}

/***************************************************
 ***************** PayRoll class definitions *******
 **************************************************/
Payroll::Payroll(int hours, int rate) {
    setHours(hours);
    setRate(rate);
}

void Payroll::setHours(int h) {
    // do not accept hours worked over 60
    (h < 61 && h >=0) ? hours = h : hours=0;
}

void Payroll::setRate(int rate) {
    (rate > 0 ) ? payRate = rate : rate = 0;
}

/***************************************************
 ************ CashRegister class definitions *******
 **************************************************/
CashRegister::CashRegister() {
    // number of items available for sale
    nItems = 5;
    
    inventory = new InventoryItem[nItems];
    
    fillItems(this->inventory, nItems);
    
}

void CashRegister::buyItem() {
    cout << "select an item from the following items\n";
    print();
    cout << "Item #: ";
    int itemNum;
    cin >> itemNum;
    // -1 means failed to find item
    int itemIndex = findItem(itemNum);
    if ( itemIndex != -1 ) {
        // how many will be purchased
        cout << "How many will you buy: ";
        int qty;
        cin >> qty;
        float subtotal = inventory[itemIndex].getTotalCost() * qty;
        int tax = subtotal * 0.06;
        int total = subtotal+tax;
        // update the quantity
        int newQty = inventory[itemIndex].getQuantity()-qty;
        inventory[itemIndex].setQuantity(newQty);
        // Print out subtotal, tax, and total
        cout << setw(10) << "Subtotal:" << subtotal
             << setw(11) << "\nTax:" << tax
             << setw(11) << "\nTotal:" << total << endl;
        
    }
    else
        cout << "Item not found.\n";
    
}

// print a list of the the item available
void CashRegister::print() const {
    for (int i =0; i != nItems; ++i) {
        cout << setw(18) << left
             << "Item number: " << inventory[i].getItemNumber()
             << setw(19) << "\ncost: " << inventory[i].getCost()
             << setw(18) << "\nNumber available: " << inventory[i].getQuantity()
             << "\n\n";
    }
    cout << endl;
}

int CashRegister::findItem(int itmNum) const {
    for (int i = 0; i != nItems; ++i) {
        if (itmNum == inventory[i].getItemNumber())
            return i;
    }
    // item was not found
    return -1;
}

// fill the cash register with inventory
void fillItems(InventoryItem *inventory, int size) {
    for (int i=0; i != size; ++i ) {
        // give inventory a five digit identifier
        int itemNum = rand() % 10000 + 100000;
        // set the cost of the items between $1 and $100
        float itemCost = rand() % 100 + 1;
        // add 30 percent profit to each item
        itemCost += (itemCost *0.30);
        // the number of units available
        int nUnit = rand() % 20 + 1;
        inventory[i].setItemNumber(itemNum);
        inventory[i].setCost(itemCost);
        inventory[i].setQuantity(nUnit);
    }
}

