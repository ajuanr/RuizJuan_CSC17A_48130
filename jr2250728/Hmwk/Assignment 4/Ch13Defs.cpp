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
    (y < 2050 && y > 1950 ) ? year = d: year=1950;
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
    
}