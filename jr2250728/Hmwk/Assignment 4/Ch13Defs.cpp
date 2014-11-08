//
//  Ch13Defs.cpp
//  RuizJuan-Chapter13
//
//  Created by Juan Ruiz on 11/7/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <stdio.h>
#include <iostream>
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
 ***************** Inventory class definitions *****
 **************************************************/
Inventory::Inventory() {
    setCost(0);
    setQuantity(0);
    setItemNumber(0);
}

Inventory::Inventory(int itemNum, float cost, int quant) {
    setCost(cost);
    setQuantity(quant);
    setItemNumber(itemNum);
}

void Inventory::setCost(float c) {
    (c > 0) ? cost=c : cost=0;
}

void Inventory::setItemNumber(int i) {
    (i > 0) ? itemNumber = i : itemNumber = 0;
}

void Inventory::setQuantity(int q) {
    (q > 0) ? quantity = q : quantity = 0;
}

/***************************************************
 ***************** Numbers class definitions *****
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
}

Numbers::~Numbers() {
    cout << "In destructor. Deleting data.\n";
    delete []data;
}

