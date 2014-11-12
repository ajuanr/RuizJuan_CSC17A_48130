//
//  Ch14Classes.cpp
//  Chapter14
//
//  Created by Juan Ruiz on 11/9/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <iostream>
#include "Ch14Classes.h"

using namespace std;


/**********************************************
 ********* Chapter 14 - Problem 2 *************
 *********************************************/

// static variable
int DayofYear::dPerM[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char* DayofYear::months[12] = {"Junuary", "February", "March", "April",
                               "May", "June", "July", "August", "September",
                                "October", "November", "December"};

// Functions
DayofYear::DayofYear(int d) {
    // validate day selected
    // range from day 1 to last day, 365
    (d > 0 && d < 366 ) ? day = d : day = 1;
}

void DayofYear::print() const {
    int index = 0;
    int dayCpy = day;
    while ( dayCpy > dPerM[index] ) {
        // subtract number of days in the current month from day entered
        dayCpy-= dPerM[index];
        ++index;
    }
    cout << "Day " << day << " is: " << months[index] << " " << dayCpy << endl;
}


/**********************************************
 ********* Chapter 14 - Problem 4 *************
 *********************************************/
NumDays::NumDays(int h) {
    // don't accept negative hours
    (hours >= 0 ) ? hours = h : hours = 0;
}

int NumDays::operator+(const NumDays &rhs) {
    return this->hours + rhs.hours;
}

int NumDays::operator-(const NumDays &rhs) {
    return this->hours - rhs.hours;
}