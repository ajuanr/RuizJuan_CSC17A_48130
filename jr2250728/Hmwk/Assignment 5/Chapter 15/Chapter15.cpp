//
//  Chapter15.cpp
//  Chapter 15
//
//  Created by Juan Ruiz on 11/21/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <string>
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
///////////// Class Production Worker
ProductionWorker::ProductionWorker(string name, string num , string date,
                                   int shft, float rate)
:Employee(name, num,date) {
    shift = shft;
    payRate = rate;
}

