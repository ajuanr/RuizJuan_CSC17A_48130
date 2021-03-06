//
//  Ch14Classes.cpp
//  Chapter14
//
//  Created by Juan Ruiz on 11/9/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <iostream>
#include <iomanip>
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

NumDays NumDays::operator++(int) {
    ++(this->hours);
    return *this;
}

NumDays& NumDays::operator++() {
    ++(this->hours);
    return *this;
}

NumDays NumDays::operator--(int) {
    --(this->hours);
    return *this;
}

NumDays& NumDays::operator--() {
    --(this->hours);
    return *this;
}

/**********************************************
 ********* Chapter 14 - Problem 10 ************
 *********************************************/
float DivSales::yrlySales = 0;

DivSales::DivSales() {
    // set all elements of the array to zero
    for (int i=0; i != 4; ++i)
        salesFig[i] = 0;
}

// each argument represents the sales for the division
void DivSales::setSales(float q1, float q2, float q3, float q4) {
    salesFig[0] = q1;
    salesFig[1] = q2;
    salesFig[2] = q3;
    salesFig[3] = q4;
    
    // add the sales  from each division to the total yearly sales
    for (int i = 0; i != 4; ++i)
        addSales(salesFig[i]);
}

float DivSales::getDivSales(int index) {
    if (index < 4 && index >= 0 )
        return salesFig[index];
    return salesFig[0];
}

void DivSales::addSales(float sales) {
        yrlySales += sales;
}

void DivSales::print() const {
    cout << setw(5) << salesFig[0];
    for (int i = 1; i != 4; ++i) {
        cout << " | " << setw(5) << salesFig[i];
    }
    cout << endl;
}
/**********************************************
 ********* Chapter 14 - Problem 13 ************
 *********************************************/
///// Class FeetInches
FeetInches::FeetInches(int ft, int inch) {
    feet = ft;
    inches = inch;
    simplify();
}

void FeetInches::simplify() {
    if (inches >=12 ) {
        feet+= inches/12;
        inches %= 12;
    }
    else if (inches < 0 ) {
        feet-= (inches *-1)/12+1;
        inches = 12 - (inches * -1) % 12;
    }
}

FeetInches FeetInches::operator*(const FeetInches &rhs) {
    FeetInches temp;
    temp.setFeet(this->feet * rhs.feet);
    temp.setInches(this->inches * rhs.inches);
    temp.simplify();
    
    return temp;
}

////// Class RoomDimension
RoomDimension::RoomDimension() {
    length.setFeet(0);
    length.setInches(0);
    width.setFeet(0);
    width.setInches(0);
}

RoomDimension::RoomDimension(int lF, int lI, int wF, int wI) {
    length.setFeet(lF);
    length.setInches(lI);
    width.setFeet(wF);
    width.setInches(wI);
}

////// Class RoomCarpet
RoomCarpet::RoomCarpet() {
    cout << "Enter the length of the room in feet ";
    int length;
    cin >> length;
    cout << "Enter the width of the room in feet: ";
    int width;
    cin >> width;
    
    RoomDimension temp(length, 0, width, 0);
    area = temp;
    cout << "Enter the cost of the carpet: ";
    cin >> cost;
}

float RoomCarpet::totalCost() {
    FeetInches temp = area.getArea();
    return cost * temp.getFeet();
}

/**********************************************
 ********* Chapter 14 - Problem 15 ************
 *********************************************/
FuelGauge::FuelGauge(int g) {
    if ( g < 0 ) gallons = 0;
    else if ( g > capacity ) gallons = capacity; // max capacity of fuel tank
    else gallons = g;
}

void FuelGauge::fill(int g) {
    if (g < 0 ) ; // do nothing
    else{
        if ( g - capacity > 0 ) gallons = 15;  // don't overfill gas tank
        else gallons += g;
    }
}

FuelGauge FuelGauge::operator++() {
    this->gallons++;
    return *this;
}

FuelGauge& FuelGauge::operator++(int) {
    this->gallons++;
    return *this;
}

FuelGauge FuelGauge::operator--() {
    this->gallons--;
    return *this;
}

FuelGauge& FuelGauge::operator--(int) {
    this->gallons--;
    return *this;
}

////// Class odometer
Odometer::Odometer(int mi) {
    mileage = mi;
}

Odometer Odometer::operator++() {
    ++(this->mileage);
    return *this;
}