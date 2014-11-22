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
#include <fstream>
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

/**********************************************
 ********** Chapter 15 Problem 9 **************
 *********************************************/
class FileFilter {
public:
    virtual void doFilter(std::ifstream&, std::ofstream&)=0;
private:
    virtual char transform(char)=0;
};
// class encrypts a file
class Encryption:public FileFilter {
public:
    Encryption(int);
    void doFilter(std::ifstream&, std::ofstream&);
private:
    char transform(char);
    int key;
};
// class changes characters in file to uppercase
class Upper:public FileFilter {
public:
    void doFilter(std::ifstream&, std::ofstream&);
private:
    char transform(char);
};

class FileCpy:public FileFilter {
public:
    void doFilter(std::ifstream&, std::ofstream&);
private:
    char transform(char);
};
#endif /* defined(__Chapter_15__Chapter15__) */

/**********************************************
 ********** Chapter 15 Problem 12 **************
 *********************************************/
