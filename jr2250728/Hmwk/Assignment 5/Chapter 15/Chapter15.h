//
//  Chapter15.h
//  Chapter 15
//
//  Created by Juan Ruiz on 11/21/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#ifndef __Chapter_15__Chapter15__
#define __Chapter_15__Chapter15__

#include <string>
using std::string;
/**********************************************
 ********** Chapter 15 Problem 1 **************
 *********************************************/
class Employee {
public:
    Employee(string,string, string);
    string getName() const {return empName;}
    string getNum() const {return empNum;}
    string getHDate() const {return hireDate;}
    void setName(string);
    void setNum(string);
    void setHDate(string);
    virtual void print() const;
private:
    string empName;
    string empNum;
    string hireDate;
};

class ProductionWorker:public Employee {
public:
    ProductionWorker(string,string,string, int, float);
    void changeShift(int);
    void setRate(float);
    int getShift() const {return shift;}
    float pay() const {return payRate;}
    void print() const;
private:
    int shift;
    float payRate;
};
#endif /* defined(__Chapter_15__Chapter15__) */
