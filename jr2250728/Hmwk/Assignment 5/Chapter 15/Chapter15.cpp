//
//  Chapter15.cpp
//  Chapter 15
//
//  Created by Juan Ruiz on 11/21/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <string>
#include <fstream>
#include <iostream>
#include "Chapter15.h"

using namespace std;

/**********************************************
 ********** Chapter 15 Problem 1 **************
 *********************************************/
//////////////// Class Employeee
Employee::Employee(string name, string num, string hDate) {
    setName(name);
    setNum(num);
    setHDate(hDate);
}

 void Employee::setName(string n) {
    empName = n;
}

void Employee::setNum(string n) {
    empNum = n;
}

void Employee::setHDate(string n) {
    hireDate = n;
}

void Employee::print() const {
    cout << "Employee Name is: " << empName << endl
         << "Employee number is: " << empName << endl
         << "Employee hire date is: " << hireDate << endl;
}
///////////// Class Production Worker
ProductionWorker::ProductionWorker(string name, string num , string date,
                                   int shft, float rate)
:Employee(name, num,date) {
    changeShift(shft);
    setRate(rate);
}

void ProductionWorker::changeShift(int s) {
    // only two shifts, 1 or 2
    if ( s == 1 ) shift = 1;
    else if ( s==2) shift = 2;
    else shift = 1;
}

void ProductionWorker::setRate(float r) {
    (r>0) ? payRate = r: payRate = 0;
}

void ProductionWorker::print() const {
    cout << "Employee Name is: " << getName() << endl
    << "Employee number is: " << getNum() << endl
    << "Employee hire date is: " << getHDate() << endl
    << "Employee works shift: " << shift << endl
    << "Employee pay rate is : " << payRate << endl;
}

/**********************************************
 ********** Chapter 15 Problem 9 **************
 *********************************************/
Encryption::Encryption(int k) {
    key = k;
}
void Encryption::doFilter(ifstream& in, ofstream& out) {
    char next;
    while (next != in.eof()) {
        cin.get(next); // get the character
        next = transform(next);    // encrypt it
        out << next;    // write it to the output file
    }
}

char Encryption::transform(char c) {
    return c + key;
}